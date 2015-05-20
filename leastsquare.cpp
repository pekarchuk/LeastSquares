#include "leastsquare.h"
#include "ui_leastsquare.h"

LeastSquare::LeastSquare(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LeastSquare)
{
    ui->setupUi(this);
}

LeastSquare::~LeastSquare()
{
    delete ui;
}

void LeastSquare::GetData()
{
    QString xdata = ui->X_data->toPlainText();
    QString ydata = ui->Y_data->toPlainText();
    QString delim = ui->Delimiter->text();
    if (delim.isEmpty())
    {
        delim = "\n";
    }
    QStringList xdata_l = xdata.split(delim);
    QStringList ydata_l = ydata.split(delim);
    for (auto c = xdata_l.begin(); c!= xdata_l.end(); ++c)
    {
        x_values.push_back((*c).toDouble());
    }
    for (auto c = ydata_l.begin(); c != ydata_l.end(); ++c)
    {
        y_values.push_back((*c).toDouble());
    }
}

void LeastSquare::PlotQuadr(QCustomPlot *customPlot)
{
    QString label1 = ui->XLabel->text();
    QString label2 = ui->YLabel->text();
    QString size_point = ui->size_point->text();
    if (size_point.isEmpty())
    {
        size_point = "8";
    }

    customPlot->addGraph();
    customPlot->graph(0)->setPen(QPen(Qt::black));
    customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);
    customPlot->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssDisc, size_point.toInt()));
    customPlot->graph(0)->setData(x_values, y_values);

    customPlot->addGraph();
    customPlot->graph(1)->setPen(QPen(Qt::cyan));
    customPlot->graph(1)->setLineStyle(QCPGraph::lsLine);
    customPlot->graph(1)->setData(x_values, y_apprx);

    customPlot->xAxis2->setVisible(true);
    customPlot->xAxis2->setTickLabels(false);
    customPlot->yAxis2->setVisible(true);
    customPlot->yAxis2->setTickLabels(false);
    connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
    connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));
    customPlot->xAxis->setLabel(label1);
    customPlot->yAxis->setLabel(label2);
    customPlot->graph(0)->rescaleAxes();
    customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
}

void LeastSquare::CalculateFit()
{
    double a, b;
    double sumx = 0;
    double sumy = 0;
    double sumxsq = 0;
    double sumxy = 0;
    int size = x_values.size();
    for (int i = 0; i != size; ++i)
    {
        sumx += x_values[i];
        sumy += y_values[i];
        sumxsq += x_values[i] * x_values[i];
        sumxy += x_values[i] * y_values[i];
    }
    a = (size*sumxy - sumx*sumy) / (size*sumxsq - (sumx * sumx));
    b = (sumy - a*sumx) / size;
    for (auto i = x_values.cbegin(); i != x_values.cend(); ++i)
    {
        y_apprx.push_back(a*(*i) + b);
    }
    QString result = QString("f(x) = ax + b = %1x + %2").arg(a).arg(b);
    ui->result->setText(result);
}

void LeastSquare::on_Plot_clicked()
{
    GetData();
    CalculateFit();
    PlotQuadr(ui->customPlot);
}

void LeastSquare::on_Quit_clicked()
{
    qApp->quit();
}
