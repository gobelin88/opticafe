#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QFile>
#include <QFileDialog>
#include <QMenu>
#include <QAction>
#include <QActionGroup>
#include <QTextStream>
#include <iostream>
#include "parser/parser.h"
#include "system.h"
#include "parameters.h"
#include "image_viewer.h"

namespace Ui {
class MainWindow;
}

class WorkerThread : public QThread
{
    Q_OBJECT
public:

    enum WhatToDo
    {
        IMAGE_FUNC,
        IMAGE,
        SOLVE
    };

    WorkerThread()
    {
        system_use.store(0);
    }

    void calcImageFunc(System * sys,Box box,ColorMode color_mode,ScaleColorMode scale_color_mode)
    {
        this->sys=sys;
        this->box=box;
        this->color_mode=color_mode;
        this->scale_color_mode=scale_color_mode;

        what=IMAGE_FUNC;
        start();
    }

    void calcImage(System * sys,Box box,ColorMode color_mode,ScaleColorMode scale_color_mode)
    {
        this->sys=sys;
        this->box=box;
        this->color_mode=color_mode;
        this->scale_color_mode=scale_color_mode;

        what=IMAGE;
        start();
    }

    void solveSystem(System * sys)
    {
        this->sys=sys;

        what=SOLVE;
        start();
    }

    void run()
    {
        system_use.store(1);

        if(what==IMAGE_FUNC)
        {
            emit sig_image(System::toImage(sys->eval_2D_p0p1(box,color_mode),scale_color_mode));
        }
        else if(what==IMAGE)
        {
            emit sig_image(System::toImage(sys->solve_2D_p0p1(box,color_mode),scale_color_mode));
        }
        else if (what==SOLVE)
        {
            sys->solve();
            emit sig_solve();
        }
        system_use.store(0);
    }

    QAtomicInt system_use;

signals:
    void sig_image(QImage image);
    void sig_solve();

private:
    System * sys;
    Box box;
    ColorMode color_mode;
    ScaleColorMode scale_color_mode;
    WhatToDo what;
};


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setStyle(QWidget * widget,QString filename);

public slots:
    void slot_run_script();
    void slot_load_script();
    void slot_save_script();
    void slot_direct_save_script();
    void slot_text_changed();
    void pick(double p0,double p1);
    void slot_2D_f();
    void slot_2D_f_func();

    void slot_load_conv_setting(QString filename);
    void slot_load_conv_setting();
    void slot_save_conv_setting();

    void slot_solve_over();

private:
    void ignore(QTextStream & ts, char c);
    SolveMode getAlgo();
    Ui::MainWindow *ui;
    Parser parser;

    QString current_filename;
    bool textChanged;

    QActionGroup * algo_group;

    ImageViewer * viewerImage;

    System * sys;

    WorkerThread worker;

    QScrollArea * scrollarea;
};

#endif // MAINWINDOW_H
