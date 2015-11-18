#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStringList>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <iostream>
#include "parser/parser.h"
#include "system.h"

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

    void slot_2D_f();

private:
    Ui::MainWindow *ui;
    Parser parser;

    QString current_filename;
    bool textChanged;
};

#endif // MAINWINDOW_H
