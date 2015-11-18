#-------------------------------------------------
#
# Project created by QtCreator 2015-11-10T13:23:00
#
#-------------------------------------------------

QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Fit
TEMPLATE = app
CONFIG += c++11

INCLUDEPATH += ./levmar
LIBS += .\lapack\lib\VC11\blas.lib
LIBS += .\lapack\lib\VC11\f2c.lib
LIBS += .\lapack\lib\VC11\lapack.lib
LIBS += .\levmar\levmar-2.6_bin_vc11\Release\levmar.lib

SOURCES += main.cpp\
        mainwindow.cpp\
        system.cpp\
        parser\parser.cpp \
            parser\error.cpp \
            parser\functions.cpp \
            parser\variablelist.cpp \
            plot\qcustomplot.cpp

HEADERS  += mainwindow.h \
            system.h\
            parser\parser.h \
            parser\constants.h \
            parser\error.h \
            parser\functions.h \
            parser\variablelist.h \
            plot\qcustomplot.h
FORMS    += mainwindow.ui
