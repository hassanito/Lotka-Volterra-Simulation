    #include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <string>
#include <iostream>
using namespace std;
/*
    By Hassan ELhajj
    And Elsa Messara
    January 2019
*/

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}


double fx(double x, double y,double alpha,double beta) { return (alpha* x -beta * x * y); }

// Predator
double fy(double x, double y,double gamma,double delta) { return (-gamma * y + delta * x * y); }

// Runge-Kutta function
void runge_kutta(double *x, double *y, double h,double alpha,double gamma,double beta,double delta, double(*fx)(double, double,double,double),double(*fy)(double, double,double,double)) {
    double dx1, dx2, dx3, dx4, dy1, dy2, dy3, dy4;

    dx1 = fx(*x, *y,alpha,beta);
    dy1 = fy(*x, *y,gamma,delta);
    dx2 = fx(*x + (h / 2.0) * dx1, *y + (h / 2.0) * dy1,alpha,beta);
    dy2 = fy(*x + (h / 2.0) * dx1, *y + (h / 2.0) * dy1,gamma,delta);
    dx3 = fx(*x + (h / 2.0) * dx2, *y + (h / 2.0) * dy2,alpha,beta);
    dy3 = fy(*x + (h / 2.0) * dx2, *y + (h / 2.0) * dy2,gamma,delta);
    dx4 = fx(*x + h * dx3, *y + h * dy3,alpha,beta);
    dy4 = fy(*x + h * dx3, *y + h * dy3,gamma,delta);

    *x += h * (dx1 + 2.0 * dx2 + 2.0 * dx3 + dx4) / 6.0;
    *y += h * (dy1 + 2.0 * dy2 + 2.0 * dy3 + dy4) / 6.0;

}


void MainWindow::on_pushButton_clicked()
{

      alpha = ui->alpha->text().toDouble();
      beta = ui->beta->text().toDouble();
      gamma = ui->gamma->text().toDouble();
      delta = ui->delta->text().toDouble();
      //ex = ui->ex->text().toDouble();
      //ey = ui->ey->text().toDouble();
      x0 = ui->x0->text().toDouble();
      y0 = ui->y0->text().toDouble();
      alpha = alpha0 -ex;
      gamma = gamma0 +ey;


      cout<<"these are your values : "<<endl;
      cout<<" alpha = "<<alpha<<endl;
      cout<<" beta = "<<beta <<endl;
      cout<<" gamma = "<<gamma<<endl;
      cout<<" delta = "<<delta<<endl;
      cout<<"x0 = "<<x0<<endl;
      cout<<"y0 = "<<y0<<endl;
      cout<<"ex = "<<ex<<endl;
      cout<<"ey = "<<ey<<endl;



        ui->customPlot->addGraph();

        double x, y;
        double i = time_start;
        x = x0;
        y = y0;





        vector<double> x_axis;
        vector<double> y_axis;
        vector<double> z_axis;

        QVector<double> xo(501), yo(501); // initialize with entries 0..100
        QVector<double> zo(501);
        do {
           // cout << i << " " << x << " " << y << endl;


            x_axis.push_back(i);

            y_axis.push_back(x);
            z_axis.push_back(y);

            runge_kutta(&x, &y, step_h,alpha,gamma,beta,delta, fx, fy);


            i += step_h;

        } while (i <= t_finish);



        for (int i=0; i<500; ++i)
        {

          xo[i] = x_axis[i]; // x goes from -1 to 1
          yo[i] = y_axis[i]; // let's plot a quadratic function
          zo[i] = z_axis[i];
          cout<<"xo = "<<xo[i]<<endl;
          cout<<"yo = "<<yo[i]<<endl;
        }
        // create graph and assign data to it:


        ui->customPlot->graph(0)->setPen(QPen(Qt::blue)); // line color blue for first graph - la proie

        ui->customPlot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20))); // first graph will be filled with translucent blue
        ui->customPlot->addGraph();
        ui->customPlot->graph(0)->setName("prey");

        ui->customPlot->graph(1)->setPen(QPen(Qt::red));
        ui->customPlot->graph(1)->setName("proie");
        // line color red for second graph
        // generate some points of data (y0 for first, y1 for second graph):

        // configure right and top axis to show ticks but no labels:
        // (see QCPAxisRect::setupFullAxesBox for a quicker method to do this)
        ui->customPlot->xAxis2->setVisible(true);
        ui->customPlot->xAxis2->setTickLabels(false);
        ui->customPlot->yAxis2->setVisible(true);
        ui->customPlot->yAxis2->setTickLabels(false);
        // make left and bottom axes always transfer their ranges to right and top axes:
        connect(ui->customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->xAxis2, SLOT(setRange(QCPRange)));
        connect(ui->customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->customPlot->yAxis2, SLOT(setRange(QCPRange)));
        // pass data points to graphs:
        ui->customPlot->graph(0)->setData(xo, yo);
        ui->customPlot->graph(1)->setData(xo,zo);
        // let the ranges scale themselves so graph 0 fits perfectly in the visible area:
        ui->customPlot->graph(0)->rescaleAxes();
        // same thing for graph 1, but only enlarge ranges (in case graph 1 is smaller than graph 0):
        ui->customPlot->graph(1)->rescaleAxes(true);
        // Note: we could have also just called ui->customPlot->rescaleAxes(); instead
        // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
        ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        ui->customPlot->replot();










}

void MainWindow::on_alpha_textEdited(const QString &arg1)
{
    on_pushButton_clicked();
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
    ex = alpha0*position/100.0;
    ui->alpha_tes->setNum(alpha0);
    ui->peche_x->setNum(ex);
    on_pushButton_clicked();
}


void MainWindow::on_horizontalSlider_2_sliderMoved(int position)
{
    ey =gamma0* (position)/25.0;
    ui->peche_y_label->setNum(ey);
    ui->peche_y->setNum(ey);
    on_pushButton_clicked();
}
