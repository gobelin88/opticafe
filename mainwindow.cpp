#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    textChanged=false;
    current_filename="./scripts/default.txt";

    ui->setupUi(this);



    for(int i=0;i<NBColorMode;i++){ui->cb__color_mode->addItem(ColorMode_str[i]);}
    for(int i=0;i<NBScaleColorMode;i++){ui->cb_scale_color_mode->addItem(ScaleColorMode_str[i]);}

    //Menu
    algo_group=new QActionGroup(NULL);
    QMenu * menu=new QMenu;
    for(int i=0;i<NBSolveMode;i++)
    {
        QAction * new_action=new QAction(QString(SolveMode_str[i]),this);
        new_action->setShortcut(QString("Ctrl+F%1").arg(i+1));
        new_action->setCheckable(true);
        menu->addAction(new_action);
        algo_group->addAction(new_action);
    }
    ui->actionAlgorithms->setMenu(menu);

    QList<QAction*> list=algo_group->actions();
    list[0]->setChecked(true);

    //Display
    viewerImage=new ImageViewer();
    ui->scrollArea->setWidget(viewerImage);

    //System
    sys=new System(&parser);
    ui->tabSystem->addTab(sys->getParamHandler(),QString("Parameters"));

    connect(ui->actionMinimize,SIGNAL(triggered()),this,SLOT(slot_run_script()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(slot_direct_save_script()));
    connect(ui->actionSaveUnder,SIGNAL(triggered()),this,SLOT(slot_save_script()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(slot_load_script()));
    connect(ui->te_script,SIGNAL(textChanged()),this,SLOT(slot_text_changed()));
    connect(ui->actionQuit,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(ui->pb_calculate,SIGNAL(clicked()),this,SLOT(slot_2D_f()));
    connect(ui->pbSaveImage,SIGNAL(clicked()),this,SLOT(slot_save_image()));
    connect(ui->pb_save_conv_setting,SIGNAL(clicked()),this,SLOT(slot_save_conv_setting()));
    connect(ui->pb_load_conv_setting,SIGNAL(clicked()),this,SLOT(slot_load_conv_setting()));

    connect(viewerImage,SIGNAL(pick(double,double)),this,SLOT(pick(double,double)));
}

SolveMode MainWindow::getAlgo()
{
    QList<QAction*> list=algo_group->actions();
    for(int i=0;i<list.size();i++)
    {
        if(list[i]->isChecked())return (SolveMode)i;
    }
    return (SolveMode)0;
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

    if(sys->load_system(system_str))
    {
        sys->show();
        sys->setSolveMode(getAlgo());
        sys->solve();
        sys->eval();
        sys->plot();
    }
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


    if(sys->load_system(system_str))
    {

        sys->setSolveMode(getAlgo());

        ui->progressBar->setRange(0,ui->sb_Width->value()-1);
        sys->setProgressBar(ui->progressBar);

        Box box(ui->sb_p0_min->value(),
                ui->sb_p0_max->value(),
                ui->sb_p1_min->value(),
                ui->sb_p1_max->value(),
                ui->sb_Width->value(),
                ui->sb_Height->value());

        viewerImage->setBox(box);

        QImage img=System::toImage(sys->solve_2D_p0p1(box,
                                   (ColorMode)ui->cb__color_mode->currentIndex()),
                                   (ScaleColorMode)ui->cb_scale_color_mode->currentIndex());


        viewerImage->setImage(img);
        viewerImage->update();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slot_save_image()
{
    QFileInfo info(current_filename);
    QString where=info.path()+QString("/image_")+QString(QString(SolveMode_str[getAlgo()]));

    QString filename=QFileDialog::getSaveFileName(this,"Save Script",where,"(*.png)");

    if(!filename.isEmpty())
    {
        viewerImage->getImage().save(filename);
    }
}

void MainWindow::slot_load_conv_setting()
{
    QString filename=QFileDialog::getSaveFileName(this,"Save Convergence Setting","","(*.txt)");

    if(!filename.isEmpty())
    {

    }
}

void MainWindow::slot_save_conv_setting()
{
    QString filename=QFileDialog::getOpenFileName(this,"Open Convergence Setting","","(*.txt)");

    if(!filename.isEmpty())
    {

    }
}

void MainWindow::pick(double p0,double p1)
{
    std::cout<<"pick "<<p0<<" "<<p1<<std::endl;
    //sys->set

    sys->set_p_init(p0,p1);
    sys->solve();
    viewerImage->setPath(sys->results.p_list);
    viewerImage->update();
}
