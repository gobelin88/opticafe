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
    scrollarea=new QScrollArea();
    scrollarea->setWidget(viewerImage);
    scrollarea->setWindowTitle("2D Convergence");

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
    connect(ui->pb_calculate_func,SIGNAL(clicked()),this,SLOT(slot_2D_f_func()));
    connect(ui->pb_save_conv_setting,SIGNAL(clicked()),this,SLOT(slot_save_conv_setting()));
    connect(ui->pb_load_conv_setting,SIGNAL(clicked()),this,SLOT(slot_load_conv_setting()));

    connect(viewerImage,SIGNAL(pick(double,double)),this,SLOT(pick(double,double)));
    connect(&worker,SIGNAL(sig_image(QImage)),viewerImage,SLOT(setImage(QImage)));
    connect(sys,SIGNAL(progress(int)),ui->progressBar,SLOT(setValue(int)));

    connect(&worker,SIGNAL(sig_solve()),this,SLOT(slot_solve_over()));

    setStyle(this,"./style.qss");
    setStyle(sys,"./style.qss");
    setStyle(scrollarea,"./style.qss");
}

void MainWindow::setStyle(QWidget * widget,QString filename)
{
    QFile file(filename);
    if(file.open(QIODevice::Text | QIODevice::ReadOnly))
    {
        widget->setStyleSheet(QString(file.readAll()));
        file.close();
    }
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
    if(worker.system_use.load())return;

    QString system_str=ui->te_script->toPlainText();

    if(sys->load_system(system_str))
    {
        sys->show();
        sys->setSolveMode(getAlgo());
        worker.solveSystem(sys);

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
    if(worker.system_use.load())return;

    QString system_str=ui->te_script->toPlainText();


    if(sys->load_system(system_str))
    {
        scrollarea->show();
        sys->setSolveMode(getAlgo());

        if(ui->cb_param1->currentIndex()==ui->cb_param2->currentIndex())
        {
            QMessageBox::information(this,"Bad Id for parametres",QString("p%1 == p%2").arg(ui->cb_param1->currentIndex()).arg(ui->cb_param2->currentIndex()));
            return;
        }
        if(ui->cb_param1->currentIndex()>ui->cb_param2->currentIndex())
        {
            int index=ui->cb_param1->currentIndex();
            ui->cb_param1->setCurrentIndex(ui->cb_param2->currentIndex());
            ui->cb_param2->setCurrentIndex(index);
        }
        if(!sys->selectId1(ui->cb_param1->currentIndex()))
        {
            QMessageBox::information(this,"Bad Id for parametre 1",QString("p%1 is not defined in the system").arg(ui->cb_param1->currentIndex()));
            return;
        }
        if(!sys->selectId2(ui->cb_param2->currentIndex()))
        {
            QMessageBox::information(this,"Bad Id for parametre 2",QString("p%1 is not defined in the system").arg(ui->cb_param2->currentIndex()));
            return;
        }

        ui->progressBar->setRange(0,ui->sb_Width->value()-1);

        Box box(ui->sb_p0_min->value(),
                ui->sb_p0_max->value(),
                ui->sb_p1_min->value(),
                ui->sb_p1_max->value(),
                ui->sb_Width->value(),
                ui->sb_Height->value());

        viewerImage->setBox(box);

//        QImage img=System::toImage(sys->solve_2D_p0p1(box,
//                                   (ColorMode)ui->cb__color_mode->currentIndex()),
//                                   (ScaleColorMode)ui->cb_scale_color_mode->currentIndex());

        worker.calcImage(sys,box,(ColorMode)ui->cb__color_mode->currentIndex(),
                          (ScaleColorMode)ui->cb_scale_color_mode->currentIndex(),
                         ui->sb_gamma->value());

    }
}

void MainWindow::slot_2D_f_func()
{
    if(worker.system_use.load())return;

    QString system_str=ui->te_script->toPlainText();


    if(sys->load_system(system_str))
    {
        scrollarea->show();
        sys->setSolveMode(getAlgo());

        if(ui->cb_param1->currentIndex()==ui->cb_param2->currentIndex())
        {
            QMessageBox::information(this,"Bad Id for parametres",QString("p%1 == p%2").arg(ui->cb_param1->currentIndex()).arg(ui->cb_param2->currentIndex()));
            return;
        }
        if(ui->cb_param1->currentIndex()>ui->cb_param2->currentIndex())
        {
            int index=ui->cb_param1->currentIndex();
            ui->cb_param1->setCurrentIndex(ui->cb_param2->currentIndex());
            ui->cb_param2->setCurrentIndex(index);
        }
        if(!sys->selectId1(ui->cb_param1->currentIndex()))
        {
            QMessageBox::information(this,"Bad Id for parametre 1",QString("p%1 is not defined in the system").arg(ui->cb_param1->currentIndex()));
            return;
        }
        if(!sys->selectId2(ui->cb_param2->currentIndex()))
        {
            QMessageBox::information(this,"Bad Id for parametre 2",QString("p%1 is not defined in the system").arg(ui->cb_param2->currentIndex()));
            return;
        }

        ui->progressBar->setRange(0,ui->sb_Width->value()-1);

        Box box(ui->sb_p0_min->value(),
                ui->sb_p0_max->value(),
                ui->sb_p1_min->value(),
                ui->sb_p1_max->value(),
                ui->sb_Width->value(),
                ui->sb_Height->value());

        viewerImage->setBox(box);

//        QImage img=System::toImage(sys->solve_2D_p0p1(box,
//                                   (ColorMode)ui->cb__color_mode->currentIndex()),
//                                   (ScaleColorMode)ui->cb_scale_color_mode->currentIndex());

        worker.calcImageFunc(sys,box,(ColorMode)ui->cb__color_mode->currentIndex(),
                          (ScaleColorMode)ui->cb_scale_color_mode->currentIndex(),
                             ui->sb_gamma->value());

    }
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::slot_save_conv_setting()
{
    QString filename=QFileDialog::getSaveFileName(this,"Save Convergence Setting","","(*.txt)");

    if(!filename.isEmpty())
    {
        QFile file(filename);

        if(file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QTextStream ts(&file);

            ts<<"Param1;"<<ui->cb_param1->currentIndex()<<"\n";
            ts<<"Param2;"<<ui->cb_param2->currentIndex()<<"\n";
            ts<<"Param1_min;"<<ui->sb_p0_min->value()<<"\n";
            ts<<"Param2_min;"<<ui->sb_p1_min->value()<<"\n";
            ts<<"Param1_max;"<<ui->sb_p0_max->value()<<"\n";
            ts<<"Param2_max;"<<ui->sb_p1_max->value()<<"\n";
            ts<<"Param1_res;"<<ui->sb_Height->value()<<"\n";
            ts<<"Param2_res;"<<ui->sb_Width->value()<<"\n";
            ts<<"color_rule;"<<ui->cb__color_mode->currentIndex()<<"\n";
            ts<<"color_scale;"<<ui->cb_scale_color_mode->currentIndex()<<"\n";

            file.close();
        }

    }
}

void MainWindow::ignore(QTextStream & ts, char c)
{
    char car=0;
    while( (car!=c) && !ts.atEnd() )
    {
        ts>>car;
    }
}

void MainWindow::slot_load_conv_setting(QString filename)
{
    if(!filename.isEmpty())
    {
        QFile file(filename);

        if(file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QTextStream ts(&file);

            double tmpd=0.0;
            int tmp=0;

            ignore(ts,';');ts>>tmp;ui->cb_param1->setCurrentIndex(tmp);
            ignore(ts,';');ts>>tmp;ui->cb_param2->setCurrentIndex(tmp);
            ignore(ts,';');ts>>tmpd;ui->sb_p0_min->setValue(tmpd);
            ignore(ts,';');ts>>tmpd;ui->sb_p1_min->setValue(tmpd);
            ignore(ts,';');ts>>tmpd;ui->sb_p0_max->setValue(tmpd);
            ignore(ts,';');ts>>tmpd;ui->sb_p1_max->setValue(tmpd);
            ignore(ts,';');ts>>tmp;ui->sb_Height->setValue(tmp);
            ignore(ts,';');ts>>tmp;ui->sb_Width->setValue(tmp);
            ignore(ts,';');ts>>tmp;ui->cb__color_mode->setCurrentIndex(tmp);
            ignore(ts,';');ts>>tmp;ui->cb_scale_color_mode->setCurrentIndex(tmp);

            file.close();
        }
    }
}

void MainWindow::slot_load_conv_setting()
{
    QString filename=QFileDialog::getOpenFileName(this,"Open Convergence Setting","","(*.txt)");
    slot_load_conv_setting(filename);
}

void MainWindow::pick(double p0,double p1)
{
    if(worker.system_use.load())return;

    sys->setSolveMode(getAlgo());
    sys->set_p_init(p0,p1);
    worker.solveSystem(sys);
}

void MainWindow::slot_solve_over()
{
    sys->eval(sys->results.p_hat);
    sys->plot();

    //Path Image
    viewerImage->setPath(sys->results.p_list);
    viewerImage->update();
}
