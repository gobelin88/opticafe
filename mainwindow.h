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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void slot_run_script();
    void slot_load_script();
    void slot_save_script();
    void slot_direct_save_script();
    void slot_text_changed();
    void slot_save_image();
    void pick(double p0,double p1);
    void slot_2D_f();

    void slot_load_conv_setting();
    void slot_save_conv_setting();

private:
    SolveMode getAlgo();
    Ui::MainWindow *ui;
    Parser parser;

    QString current_filename;
    bool textChanged;

    QActionGroup * algo_group;

    ImageViewer * viewerImage;

    System * sys;
};

#endif // MAINWINDOW_H
