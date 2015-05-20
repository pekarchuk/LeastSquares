#ifndef LEASTSQUARE_H
#define LEASTSQUARE_H

#include <QMainWindow>
#include <QVector>
#include <QString>
#include <QDebug>
#include "qcustomplot.h"

namespace Ui {
class LeastSquare;
}

class LeastSquare : public QMainWindow
{
    Q_OBJECT

public:
    explicit LeastSquare(QWidget *parent = 0);
    ~LeastSquare();

    void PlotQuadr(QCustomPlot *customPlot);
    void GetData();
    void CalculateFit();

private slots:
    void on_Plot_clicked();
    void on_Quit_clicked();

private:
    Ui::LeastSquare *ui;
    QVector<double> x_values;
    QVector<double> y_values;
    QVector<double> y_apprx;
};

#endif // LEASTSQUARE_H
