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
QT+=opengl

QMAKE_CXXFLAGS += -bigobj

LIBS+= -lGlU32 -lOpenGL32

INCLUDEPATH += .\eigen327

RESOURCES = style.qrc

SOURCES += main.cpp\
        mainwindow.cpp\
        system.cpp\
        qcustomplot.cpp \
        2d_viewer.cpp \
        3d_viewer.cpp \
    1d_viewer.cpp


HEADERS  += mainwindow.h \
            system.h\
            lmfunctor.h \
            qcustomplot.h \
            exprtk\exprtk.hpp \
            newtonsolver.h \
            parameters.h \
            2d_viewer.h \
            3d_viewer.h \
            box.h \
            DrawableInterface.h \
    1d_viewer.h

FORMS    += mainwindow.ui
