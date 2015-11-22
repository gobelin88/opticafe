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

INCLUDEPATH += C:\Users\gobelin\Documents\GitHub\dependences\eigen311


SOURCES += main.cpp\
        mainwindow.cpp\
        system.cpp\
        parser\parser.cpp \
        parser\error.cpp \
        parser\functions.cpp \
        parser\variablelist.cpp \
        qcustomplot.cpp \
    newtonsolver.cpp


HEADERS  += mainwindow.h \
            system.h\
            parser\parser.h \
            parser\constants.h \
            parser\error.h \
            parser\functions.h \
            parser\variablelist.h \
            lmfunctor.h \
            qcustomplot.h \
    newtonsolver.h

FORMS    += mainwindow.ui
