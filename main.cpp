#include "leastsquare.h"
#include <QApplication>
#include <cmath>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LeastSquare w;
    w.show();

    return a.exec();
}
