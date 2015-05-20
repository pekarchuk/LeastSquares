#-------------------------------------------------
#
# Project created by QtCreator 2015-05-17T23:08:23
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = LeastSquare
TEMPLATE = app


SOURCES += main.cpp\
        leastsquare.cpp \
    qcustomplot.cpp

HEADERS  += leastsquare.h \
    qcustomplot.h

FORMS    += leastsquare.ui

CONFIG += c++11

QMAKE_CXXFLAGS += -std=c++11
