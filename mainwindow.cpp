#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->action_levmar,SIGNAL(triggered()),this,SLOT(slot_run_script()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(slot_direct_save_script()));
    connect(ui->actionSaveUnder,SIGNAL(triggered()),this,SLOT(slot_save_script()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(slot_load_script()));
    connect(ui->te_script,SIGNAL(textChanged()),this,SLOT(slot_text_changed()));
    connect(ui->actionQuit,SIGNAL(triggered(bool)),this,SLOT(close()));

    connect(ui->pb_calculate,SIGNAL(clicked()),this,SLOT(slot_2D_f()));

    textChanged=false;
    current_filename="./scripts/default.txt";


    for(int i=0;i<NBColorMode;i++)
    {
        ui->cb__color_mode->addItem(ColorMode_str[i]);
    }

    for(int i=0;i<NBScaleColorMode;i++)
    {
        ui->cb_scale_color_mode->addItem(ScaleColorMode_str[i]);
    }
}

void MainWindow::slot_text_changed()
{
    if(textChanged==false)
    {
        this->textChanged=true;
        this->setWindowTitle(current_filename+QString("*"));
    }
}

void MainWindow::slot_run_script()
{
    QString system_str=ui->te_script->toPlainText();
    System * sys=new System(&parser,system_str);

    sys->show();

    sys->solve();
    sys->eval();
    sys->plot();
}

void MainWindow::slot_save_script()
{
    QString filename=QFileDialog::getSaveFileName(this,"Save Script",current_filename,"*.txt");

    if(!filename.isEmpty())
    {
        QFile file(filename);

        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            this->current_filename=filename;
            this->setWindowTitle(current_filename);
            textChanged=false;

            file.write(ui->te_script->toPlainText().toLocal8Bit());
            file.close();
        }
    }
}

void MainWindow::slot_direct_save_script()
{
    if(!current_filename.isEmpty())
    {
        QFile file(current_filename);

        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            this->setWindowTitle(current_filename);
            textChanged=false;

            file.write(ui->te_script->toPlainText().toLocal8Bit());
            file.close();
        }
    }
}

void MainWindow::slot_load_script()
{
    QString filename=QFileDialog::getOpenFileName(this,"Load Script",current_filename,"*.txt");

    if(!filename.isEmpty())
    {
        QFile file(filename);

        if(file.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            this->current_filename=filename;
            this->setWindowTitle(current_filename);
            textChanged=false;

            ui->te_script->setText(file.readAll());
            file.close();
        }
    }
}

void MainWindow::slot_2D_f()
{
    QString system_str=ui->te_script->toPlainText();
    System * sys=new System(&parser,system_str);

    ui->progressBar->setRange(0,ui->sb_Width->value()-1);
    sys->setProgressBar(ui->progressBar);

    QImage img=System::toImage(sys->solve_2D_p0p1(ui->sb_p0_min->value(),
                                                  ui->sb_p0_max->value(),
                                                  ui->sb_p1_min->value(),
                                                  ui->sb_p1_max->value(),
                                                  ui->sb_Width->value(),
                                                  ui->sb_Height->value(),
                                                  (ColorMode)ui->cb__color_mode->currentIndex()),
                                                  (ScaleColorMode)ui->cb_scale_color_mode->currentIndex());


    ui->label->setPixmap(QPixmap::fromImage(img));
}

MainWindow::~MainWindow()
{
    delete ui;
}
