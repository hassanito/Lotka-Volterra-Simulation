#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    double ex = 0;
    double ey = 0;
    double x0 = 1; // starting value of x
    double y0 = 1;
    double alpha = 5.2-ex;
    double alpha0 =5.2;
    double gamma0 =2.1;
    double beta = 3.4;
    double gamma = 2.1 -ey;
    double delta = 1.4;

    double time_start = 0;
    double t_finish = 25;

    double step_h = 0.02;
    //dx/dt =alpha *x  - beta*x*y
    //dy/dy = delta *x*y - gamma * y



private slots:
    void on_pushButton_clicked();



    void on_alpha_textEdited(const QString &arg1);

    void on_horizontalSlider_sliderMoved(int position);

    void on_horizontalSlider_2_sliderMoved(int position);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
