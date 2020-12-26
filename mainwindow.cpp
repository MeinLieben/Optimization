#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "paint.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , validator(0.001, 1.0, 3, this)
    , validatorArea(-99, 99, 1, this)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    validator.setNotation( QDoubleValidator::StandardNotation );
    validatorArea.setNotation( QDoubleValidator::StandardNotation );

    groupMethod.addButton(this->ui->gradientButton, 1);
    groupMethod.addButton(this->ui->stochasticButton, 0);
    ui->gradientButton->click();

    groupFunction.addButton(this->ui->f1, 1);
    groupFunction.addButton(this->ui->f2, 2);
    groupFunction.addButton(this->ui->f3, 3);
    ui->f1->click();

    groupStop.addButton(this->ui->stopGrad, 1);
    groupStop.addButton(this->ui->stopDiffElem, 2);
    groupStop.addButton(this->ui->stopDiffFun, 3);
    ui->stopGrad->click();

    this->ui->x_max->setValidator(&validatorArea);
    this->ui->x_min->setValidator(&validatorArea);
    this->ui->y_min->setValidator(&validatorArea);
    this->ui->y_max->setValidator(&validatorArea);
}

MainWindow::~MainWindow()
{
    delete ui;
}





void MainWindow::on_epsilonEdit_editingFinished()
{
    this->ui->epsilonEdit->setValidator( &validator );
    if(!this->ui->epsilonEdit->hasAcceptableInput()){
        this->ui->epsilonEdit->clear();
        this->ui->epsilonEdit->insert("0,1");
        QMessageBox::warning(this, "Некорректное значение!", "Введите значение от 0,01 до 1");
    }
    this->ui->epsilonEdit->setValidator( 0 );

}

double f1(std::vector<double> x) {
    return (x[0] - 1) * (x[0] - 1) + (x[1] - 2) * (x[1] - 2);
}

std::vector<double> gradf1(std::vector<double> x) {
    return { 2 * (x[0] - 1), 2 * (x[1] - 2) };
}

double f2(std::vector<double> x) {
    return (1 - x[0]) * (1 - x[0]) + 100*(x[1] - x[0]*x[0]) * (x[1] - x[0]*x[0]);
}

std::vector<double> gradf2(std::vector<double> x) {
    return { 2 * (x[0] - 1) - 400 * x[0] * (x[1] - x[0] * x[0]), 200 * (x[1] - x[0] * x[0]) };
}

double f3(std::vector<double> x) {
    return (x[0] + 2*x[1] - 7) * (x[0] + 2*x[1] - 7) + (2*x[0] + x[1] - 5)*(2*x[0] + x[1] - 5);
}

std::vector<double> gradf3(std::vector<double> x) {
    return { 2 * (x[0] + 2*x[1] - 7) + 4*(2*x[0] + x[1] - 5), 4 * (x[0] + 2*x[1] - 7) + 2 * (2*x[0] + x[1] - 5) };
}

void MainWindow::on_accept_clicked()
{
    std::function<double(std::vector<double>)> f;
    std::function<std::vector<double>(std::vector<double>)> gradf;
    switch (this->groupFunction.checkedId()) {
        case 2: f = f2; gradf = gradf2;
        break;
        case 3: f = f3; gradf = gradf3;
        break;
        default: f = f1; gradf = gradf1;
    }

    stopCriterion::State state;
    switch (this->groupStop.checkedId()){
        case 2: state = stopCriterion::State::diffElem;
        break;
        case 3: state = stopCriterion::State::relDiffFun;
        break;
        default: state = stopCriterion::State::grad;
    }
    QLocale german(QLocale::German);
    Area a({ui->x_min->text().toDouble(), ui->y_min->text().toDouble()}, {ui->x_max->text().toDouble(), ui->y_max->text().toDouble()});
    Paint* dialog = new Paint(this->groupMethod.checkedId(), german.toDouble(ui->epsilonEdit->text()), a, f, gradf, state);
    dialog->show();
    this->close();
}
