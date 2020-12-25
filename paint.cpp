#include "paint.h"
#include "ui_paint.h"

const int xSize = 600;
const int ySize = 410;

Paint::Paint(const bool method, const double epsilon, const Area& area, const std::function<double(std::vector<double>)>& f, const std::function<std::vector<double>(std::vector<double>)>& gradf, const stopCriterion::State& state, QWidget *parent) :
    QDialog(parent),
    f(f),
    gradf(gradf),
    state(state),
    xmin(area.geta()[0]),
    xmax(area.getb()[0]),
    ymin(area.geta()[1]),
    ymax(area.getb()[1]),
    ui(new Ui::Paint)
{
    ui->setupUi(this);

    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePressEvent(QMouseEvent*)));
    setMouseTracking(true);

    if(method) opt = new GradientOptimizing(epsilon);
    else opt = new StochasticOptimizing(epsilon);
    ui->customPlot->xAxis->setRange(xmin, xmax);
    ui->customPlot->yAxis->setRange(ymin, ymax);
    QCPColorMap *colorMap = new QCPColorMap(ui->customPlot->xAxis, ui->customPlot->yAxis);

    colorMap->data()->setSize(xSize, ySize);
    colorMap->data()->setRange(QCPRange(xmin, xmax), QCPRange(ymin, ymax));
    for (int x = 0; x < xSize; ++x)
      for (int y = 0; y < ySize; ++y){
          colorMap->data()->setCell(x, y, this->f({xmin + x * (xmax - xmin) / xSize, ymin + y * (ymax - ymin) / ySize}));
      }
    colorMap->setGradient(QCPColorGradient::gpPolar);
    colorMap->rescaleDataRange(true);
    ui->customPlot->replot();
}



void Paint::mousePressEvent(QMouseEvent* event){
    std::vector<std::vector<double>> result = opt->optimize({xmin + event->x() * (xmax - xmin) / xSize, ymax - event->y() * (ymax - ymin) / ySize}, f, Area({xmin, ymin}, {xmax, ymax}), gradf, state);
    QVector<double> x(result.size()), y(result.size()), t(result.size());
    QCPCurve *newCurve = new QCPCurve(ui->customPlot->xAxis, ui->customPlot->yAxis);
    newCurve->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, 5));
    newCurve->setPen(QPen(QColor(255, 255, 255)));

    for(size_t i = 0; i < result.size(); ++i){
        x[i] = result[i][0];
        y[i] = result[i][1];
        t[i] = i;
        std::cout << "(x, y) = ("<< result[i][0] << ", " << result[i][1] << "), f(x, y) = " << f(result[i]) << "\n";
    }
    newCurve->setData(t, x, y);
    ui->customPlot->replot();
    delete newCurve;
}

Paint::~Paint()
{
    delete ui;
}


void Paint::on_changeParam_clicked()
{
    MainWindow* window = new MainWindow();
    window->show();
    this->close();
}
