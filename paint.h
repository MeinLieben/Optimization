#ifndef PAINT_H
#define PAINT_H

#include <QDialog>
#include "mainwindow.h"
#include "qcustomplot.h"

namespace Ui {
class Paint;
}

class Paint : public QDialog
{
    Q_OBJECT

public:
    Optimizing* opt;
    std::function<double(std::vector<double>)> f;
    std::function<std::vector<double>(std::vector<double>)> gradf;
    stopCriterion::State state;
    double xmin;
    double xmax;
    double ymin;
    double ymax;
    explicit Paint(const bool method, const double epsilon, const Area& area, const std::function<double(std::vector<double>)>& f, const std::function<std::vector<double>(std::vector<double>)>& gradf, const stopCriterion::State& state,  QWidget *parent = nullptr);
    ~Paint();

private slots:
    void mousePressEvent(QMouseEvent* event);

    void on_changeParam_clicked();

private:
    Ui::Paint *ui;

};


#endif // PAINT_H
