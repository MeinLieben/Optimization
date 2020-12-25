#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QValidator>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QButtonGroup>
#include "optimizing.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:


    void on_epsilonEdit_editingFinished();

    void on_accept_clicked();

private:
    QDoubleValidator validator;
    QDoubleValidator validatorArea;
    QVBoxLayout methodBox;
    QButtonGroup groupMethod;
    QButtonGroup groupFunction;
    QButtonGroup groupStop;
public:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
