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
#include "exprtk/exprtk.hpp"
#include "system.h"
#include "parameters.h"
#include "1d_viewer.h"
#include "2d_viewer.h"
#include "3d_viewer.h"

namespace Ui {
class MainWindow;
}

class WorkerThread : public QThread
{
    Q_OBJECT
public:

    enum WhatToDo
    {
        IMAGE_3D_FUNC,
        IMAGE_3D_CONV,
        IMAGE_2D_FUNC,
        IMAGE_2D_CONV,
        IMAGE_1D_FUNC,
        IMAGE_1D_CONV,
        SOLVE
    };

    WorkerThread()
    {
        system_use.store(0);
    }

    void calc(System * sys,Box box,ColorMode color_mode,WhatToDo what_to_do)
    {
        this->sys=sys;
        this->box=box;
        this->color_mode=color_mode;

        what=what_to_do;
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

        if(what==IMAGE_1D_CONV)
        {
            std::cout<<"IMAGE_1D_CONV"<<std::endl;
            emit sig_output_1d(sys->solve_1D_p0(box,color_mode),box);
        }
        else if(what==IMAGE_1D_FUNC)
        {
            std::cout<<"IMAGE_1D_FUNC"<<std::endl;
            emit sig_output_1d(sys->eval_1D_p0(box,color_mode),box);
        }
        else if(what==IMAGE_2D_CONV)
        {
            std::cout<<"IMAGE_2D_CONV"<<std::endl;
            emit sig_output_2d(sys->solve_2D_p0p1(box,color_mode),box);
        }
        else if(what==IMAGE_3D_CONV)
        {
            std::cout<<"IMAGE_3D_CONV"<<std::endl;
            emit sig_output_3d(sys->solve_3D_p0p1p2(box,color_mode),box);
        }
        else if(what==IMAGE_2D_FUNC)
        {
            std::cout<<"IMAGE_2D_FUNC"<<std::endl;
            emit sig_output_2d(sys->eval_2D_p0p1(box,color_mode),box);
        }
        else if(what==IMAGE_3D_FUNC)
        {
            std::cout<<"IMAGE_3D_FUNC"<<std::endl;
            emit sig_output_3d(sys->eval_3D_p0p1p2(box,color_mode),box);
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
    void sig_output_1d(std::vector<double> data,Box box);
    void sig_output_2d(std::vector< std::vector<double> > data,Box box);
    void sig_output_3d(std::vector< std::vector< std::vector<double> > > data,Box box);
    void sig_solve();

private:
    System * sys;
    Box box;
    ColorMode color_mode;
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

    void slot_conv();
    void slot_func();
    void slot_conv_1d();
    void slot_func_1d();
    void slot_conv_2d();
    void slot_func_2d();
    void slot_conv_3d();
    void slot_func_3d();

    void slot_load_conv_setting(QString filename);
    void slot_load_conv_setting();
    void slot_save_conv_setting();

    void slot_solve_over();

    void id1_changed(int id);
    void id2_changed(int id);
    void id3_changed(int id);
    void update_button_names_1d();
    void update_button_names_2d();
    void update_button_names_3d();

private:
    void ignore(QTextStream & ts, char c);
    SolveMode getAlgo();
    Ui::MainWindow *ui;


    QString current_filename;
    bool textChanged;

    QActionGroup * algo_group;



    System * sys;

    WorkerThread worker;

    QTabWidget * tab_plots;

    Viewer1D * output_1d;
    Viewer2D * output_2d;
    Viewer3D * output_3d;
};

#endif // MAINWINDOW_H
