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
    output_1d=new Viewer1D();
    output_2d=new Viewer2D();
    output_3d=new Viewer3D();

    tab_plots=new QTabWidget();
    tab_plots->addTab(output_1d,"Plot 1D");
    tab_plots->addTab(output_2d,"Plot 2D");
    tab_plots->addTab(output_3d,"Plot 3D");
    tab_plots->setWindowTitle("2D/3D Plots");

    //System
    sys=new System();
    ui->tabSystem->addTab(sys->getParamHandler(),QString("Parameters"));

    qRegisterMetaType< std::vector<double> >("std::vector<double>");
    qRegisterMetaType< std::vector<std::vector<double>> >("std::vector<std::vector<double>>");
    qRegisterMetaType< std::vector<std::vector<std::vector<double>>> >("std::vector<std::vector<std::vector<double>>");

    connect(ui->actionMinimize,SIGNAL(triggered()),this,SLOT(slot_run_script()));
    connect(ui->actionSave,SIGNAL(triggered()),this,SLOT(slot_direct_save_script()));
    connect(ui->actionSaveUnder,SIGNAL(triggered()),this,SLOT(slot_save_script()));
    connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(slot_load_script()));
    connect(ui->te_script,SIGNAL(textChanged()),this,SLOT(slot_text_changed()));
    connect(ui->actionQuit,SIGNAL(triggered(bool)),this,SLOT(close()));
    connect(ui->pb_calculate_conv,SIGNAL(clicked()),this,SLOT(slot_conv()));
    connect(ui->pb_calculate_func,SIGNAL(clicked()),this,SLOT(slot_func()));
    connect(ui->pb_save_conv_setting,SIGNAL(clicked()),this,SLOT(slot_save_conv_setting()));
    connect(ui->pb_load_conv_setting,SIGNAL(clicked()),this,SLOT(slot_load_conv_setting()));
    connect(ui->sb_gamma,SIGNAL(valueChanged(double)),output_2d,SLOT(slot_set_gamma(double)));
    connect(ui->cb_scale_color_mode,SIGNAL(currentIndexChanged(int)),output_2d,SLOT(slot_set_color_mode(int)));
    connect(ui->sb_gamma,SIGNAL(valueChanged(double)),output_3d,SLOT(slot_set_gamma(double)));
    connect(ui->cb_scale_color_mode,SIGNAL(currentIndexChanged(int)),output_3d,SLOT(slot_set_color_mode(int)));
    connect(ui->sb_cut,SIGNAL(valueChanged(double)),output_3d,SLOT(slot_set_cut(double)));

    connect(ui->rb_1D,SIGNAL(clicked()),this,SLOT(update_button_names_1d()));
    connect(ui->rb_2D,SIGNAL(clicked()),this,SLOT(update_button_names_2d()));
    connect(ui->rb_3D,SIGNAL(clicked()),this,SLOT(update_button_names_3d()));

    connect(output_2d,SIGNAL(pick(double,double)),this,SLOT(pick(double,double)));
    connect(sys,SIGNAL(progress(int)),ui->progressBar,SLOT(setValue(int)));
    connect(ui->a_tiles,SIGNAL(triggered()),ui->mdiArea,SLOT(tileSubWindows()));
    connect(ui->cb_param1,SIGNAL(currentIndexChanged(int)),this,SLOT(id1_changed(int)));
    connect(ui->cb_param2,SIGNAL(currentIndexChanged(int)),this,SLOT(id2_changed(int)));
    connect(ui->cb_param3,SIGNAL(currentIndexChanged(int)),this,SLOT(id3_changed(int)));
    connect(&worker,SIGNAL(sig_solve()),this,SLOT(slot_solve_over()));

    connect(&worker,SIGNAL(sig_output_1d(std::vector<double>)),output_1d,SLOT(slot_set_data(std::vector<double>)));
    connect(&worker,SIGNAL(sig_output_2d(std::vector<std::vector<double>>)),output_2d,SLOT(slot_set_data(std::vector<std::vector<double>>)));
    connect(&worker,SIGNAL(sig_output_3d(std::vector<std::vector<std::vector<double>>>)),output_3d,SLOT(slot_set_data(std::vector<std::vector<std::vector<double>>>)));

    setStyle(this,"./style.qss");
    setStyle(sys,"./style.qss");
    setStyle(output_2d,"./style.qss");
    setStyle(output_3d,"./style.qss");


    ui->mdiArea->addSubWindow(sys,Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint);
    ui->mdiArea->addSubWindow(tab_plots,Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint);
    ui->mdiArea->addSubWindow(ui->tabSystem,Qt::CustomizeWindowHint | Qt::WindowMinMaxButtonsHint);

    id1_changed(ui->cb_param1->currentIndex());
    id2_changed(ui->cb_param2->currentIndex());
    id3_changed(ui->cb_param3->currentIndex());

    QTimer::singleShot(500, ui->mdiArea, SLOT(tileSubWindows()));
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

void MainWindow::slot_conv()
{
    if(ui->rb_1D->isChecked()){slot_conv_1d();tab_plots->setCurrentIndex(0);}
    else if(ui->rb_2D->isChecked()){slot_conv_2d();tab_plots->setCurrentIndex(1);}
    else if(ui->rb_3D->isChecked()){slot_conv_3d();tab_plots->setCurrentIndex(2);}
}

void MainWindow::slot_func()
{
    if(ui->rb_1D->isChecked()){slot_func_1d();tab_plots->setCurrentIndex(0);}
    else if(ui->rb_2D->isChecked()){slot_func_2d();tab_plots->setCurrentIndex(1);}
    else if(ui->rb_3D->isChecked()){slot_func_3d();tab_plots->setCurrentIndex(2);}
}

void MainWindow::slot_conv_1d()
{
    if(worker.system_use.load())return;

    QString system_str=ui->te_script->toPlainText();


    if(sys->load_system(system_str))
    {
        sys->setSolveMode(getAlgo());

        if(!sys->selectId1(ui->cb_param1->currentIndex()))
        {
            QMessageBox::information(this,"Bad Id for parametre 1",QString("p%1 is not defined in the system").arg(ui->cb_param1->currentIndex()));
            return;
        }

        ui->progressBar->setRange(0,ui->sb_p0_res->value()-1);

        Box box(ui->sb_p0_min->value(),
                ui->sb_p0_max->value(),
                ui->sb_p0_res->value(),
                ui->sb_p1_min->value(),
                ui->sb_p1_max->value(),
                ui->sb_p1_res->value(),
                ui->sb_p2_min->value(),
                ui->sb_p2_max->value(),
                ui->sb_p2_res->value());

        output_1d->setBox(box);

        //        QImage img=System::toImage(sys->solve_2D_p0p1(box,
        //                                   (ColorMode)ui->cb__color_mode->currentIndex()),
        //                                   (ScaleColorMode)ui->cb_scale_color_mode->currentIndex());

        worker.calc(sys,box,(ColorMode)ui->cb__color_mode->currentIndex(),
                    (ScaleColorMode)ui->cb_scale_color_mode->currentIndex(),
                    ui->sb_gamma->value(),WorkerThread::IMAGE_1D_CONV);

    }
}

void MainWindow::slot_func_1d()
{
    if(worker.system_use.load())return;

    QString system_str=ui->te_script->toPlainText();


    if(sys->load_system(system_str))
    {
        sys->setSolveMode(getAlgo());

        if(!sys->selectId1(ui->cb_param1->currentIndex()))
        {
            QMessageBox::information(this,"Bad Id for parametre 1",QString("p%1 is not defined in the system").arg(ui->cb_param1->currentIndex()));
            return;
        }

        ui->progressBar->setRange(0,ui->sb_p0_res->value()-1);

        Box box(ui->sb_p0_min->value(),
                ui->sb_p0_max->value(),
                ui->sb_p0_res->value(),
                ui->sb_p1_min->value(),
                ui->sb_p1_max->value(),
                ui->sb_p1_res->value(),
                ui->sb_p2_min->value(),
                ui->sb_p2_max->value(),
                ui->sb_p2_res->value());

        output_1d->setBox(box);

        //        QImage img=System::toImage(sys->solve_2D_p0p1(box,
        //                                   (ColorMode)ui->cb__color_mode->currentIndex()),
        //                                   (ScaleColorMode)ui->cb_scale_color_mode->currentIndex());

        worker.calc(sys,box,(ColorMode)ui->cb__color_mode->currentIndex(),
                    (ScaleColorMode)ui->cb_scale_color_mode->currentIndex(),
                    ui->sb_gamma->value(),WorkerThread::IMAGE_1D_FUNC);

    }
}

void MainWindow::slot_conv_2d()
{
    if(worker.system_use.load())return;

    QString system_str=ui->te_script->toPlainText();


    if(sys->load_system(system_str))
    {
        sys->setSolveMode(getAlgo());

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

        ui->progressBar->setRange(0,ui->sb_p0_res->value()-1);

        Box box(ui->sb_p0_min->value(),
                ui->sb_p0_max->value(),
                ui->sb_p0_res->value(),
                ui->sb_p1_min->value(),
                ui->sb_p1_max->value(),
                ui->sb_p1_res->value(),
                ui->sb_p2_min->value(),
                ui->sb_p2_max->value(),
                ui->sb_p2_res->value());

        output_2d->setBox(box);

        //        QImage img=System::toImage(sys->solve_2D_p0p1(box,
        //                                   (ColorMode)ui->cb__color_mode->currentIndex()),
        //                                   (ScaleColorMode)ui->cb_scale_color_mode->currentIndex());

        worker.calc(sys,box,(ColorMode)ui->cb__color_mode->currentIndex(),
                    (ScaleColorMode)ui->cb_scale_color_mode->currentIndex(),
                    ui->sb_gamma->value(),WorkerThread::IMAGE_2D_CONV);

    }
}

void MainWindow::slot_conv_3d()
{
    if(worker.system_use.load())return;

    QString system_str=ui->te_script->toPlainText();


    if(sys->load_system(system_str))
    {
        sys->setSolveMode(getAlgo());

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
        if(!sys->selectId3(ui->cb_param3->currentIndex()))
        {
            QMessageBox::information(this,"Bad Id for parametre 3",QString("p%1 is not defined in the system").arg(ui->cb_param3->currentIndex()));
            return;
        }

        ui->progressBar->setRange(0,ui->sb_p0_res->value()-1);

        Box box(ui->sb_p0_min->value(),
                ui->sb_p0_max->value(),
                ui->sb_p0_res->value(),
                ui->sb_p1_min->value(),
                ui->sb_p1_max->value(),
                ui->sb_p1_res->value(),
                ui->sb_p2_min->value(),
                ui->sb_p2_max->value(),
                ui->sb_p2_res->value());

        output_2d->setBox(box);

        //        QImage img=System::toImage(sys->solve_2D_p0p1(box,
        //                                   (ColorMode)ui->cb__color_mode->currentIndex()),
        //                                   (ScaleColorMode)ui->cb_scale_color_mode->currentIndex());

        worker.calc(sys,box,(ColorMode)ui->cb__color_mode->currentIndex(),
                    (ScaleColorMode)ui->cb_scale_color_mode->currentIndex(),
                    ui->sb_gamma->value(),WorkerThread::IMAGE_3D_CONV);

    }
}

void MainWindow::slot_func_2d()
{
    if(worker.system_use.load())return;

    QString system_str=ui->te_script->toPlainText();


    if(sys->load_system(system_str))
    {
        sys->setSolveMode(getAlgo());

        if(ui->cb_param1->currentIndex()==ui->cb_param2->currentIndex())
        {
            QMessageBox::information(this,"Bad Id for parametres",QString("p%1 == p%2").arg(ui->cb_param1->currentIndex()).arg(ui->cb_param2->currentIndex()));
            return;
        }
        //        if(ui->cb_param1->currentIndex()>ui->cb_param2->currentIndex())
        //        {
        //            int index=ui->cb_param1->currentIndex();
        //            ui->cb_param1->setCurrentIndex(ui->cb_param2->currentIndex());
        //            ui->cb_param2->setCurrentIndex(index);
        //        }
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

        ui->progressBar->setRange(0,ui->sb_p0_res->value()-1);

        Box box(ui->sb_p0_min->value(),
                ui->sb_p0_max->value(),
                ui->sb_p0_res->value(),
                ui->sb_p1_min->value(),
                ui->sb_p1_max->value(),
                ui->sb_p1_res->value(),
                ui->sb_p2_min->value(),
                ui->sb_p2_max->value(),
                ui->sb_p2_res->value());

        output_3d->setBox(box);

        //        QImage img=System::toImage(sys->solve_2D_p0p1(box,
        //                                   (ColorMode)ui->cb__color_mode->currentIndex()),
        //                                   (ScaleColorMode)ui->cb_scale_color_mode->currentIndex());

        worker.calc(sys,box,(ColorMode)ui->cb__color_mode->currentIndex(),
                    (ScaleColorMode)ui->cb_scale_color_mode->currentIndex(),
                    ui->sb_gamma->value(),WorkerThread::IMAGE_2D_FUNC);

    }
}

void MainWindow::slot_func_3d()
{
    if(worker.system_use.load())return;

    QString system_str=ui->te_script->toPlainText();


    if(sys->load_system(system_str))
    {
        sys->setSolveMode(getAlgo());

        if(ui->cb_param1->currentIndex()==ui->cb_param2->currentIndex())
        {
            QMessageBox::information(this,"Bad Id for parametres",QString("p%1 == p%2").arg(ui->cb_param1->currentIndex()).arg(ui->cb_param2->currentIndex()));
            return;
        }
        //        if(ui->cb_param1->currentIndex()>ui->cb_param2->currentIndex())
        //        {
        //            int index=ui->cb_param1->currentIndex();
        //            ui->cb_param1->setCurrentIndex(ui->cb_param2->currentIndex());
        //            ui->cb_param2->setCurrentIndex(index);
        //        }
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
        if(!sys->selectId3(ui->cb_param3->currentIndex()))
        {
            QMessageBox::information(this,"Bad Id for parametre 3",QString("p%1 is not defined in the system").arg(ui->cb_param3->currentIndex()));
            return;
        }


        ui->progressBar->setRange(0,ui->sb_p0_res->value()-1);

        Box box(ui->sb_p0_min->value(),
                ui->sb_p0_max->value(),
                ui->sb_p0_res->value(),
                ui->sb_p1_min->value(),
                ui->sb_p1_max->value(),
                ui->sb_p1_res->value(),
                ui->sb_p2_min->value(),
                ui->sb_p2_max->value(),
                ui->sb_p2_res->value());

        output_3d->setBox(box);

        //        QImage img=System::toImage(sys->solve_2D_p0p1(box,
        //                                   (ColorMode)ui->cb__color_mode->currentIndex()),
        //                                   (ScaleColorMode)ui->cb_scale_color_mode->currentIndex());

        worker.calc(sys,box,(ColorMode)ui->cb__color_mode->currentIndex(),
                    (ScaleColorMode)ui->cb_scale_color_mode->currentIndex(),
                    ui->sb_gamma->value(),WorkerThread::IMAGE_3D_FUNC);

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
            ts<<"Param3;"<<ui->cb_param3->currentIndex()<<"\n";

            ts<<"Param1_min;"<<ui->sb_p0_min->value()<<"\n";
            ts<<"Param2_min;"<<ui->sb_p1_min->value()<<"\n";
            ts<<"Param3_min;"<<ui->sb_p2_min->value()<<"\n";

            ts<<"Param1_max;"<<ui->sb_p0_max->value()<<"\n";
            ts<<"Param2_max;"<<ui->sb_p1_max->value()<<"\n";
            ts<<"Param3_max;"<<ui->sb_p2_max->value()<<"\n";

            ts<<"Param1_res;"<<ui->sb_p0_res->value()<<"\n";
            ts<<"Param2_res;"<<ui->sb_p1_res->value()<<"\n";
            ts<<"Param3_res;"<<ui->sb_p2_res->value()<<"\n";

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
            ignore(ts,';');ts>>tmp;ui->cb_param3->setCurrentIndex(tmp);

            ignore(ts,';');ts>>tmpd;ui->sb_p0_min->setValue(tmpd);
            ignore(ts,';');ts>>tmpd;ui->sb_p1_min->setValue(tmpd);
            ignore(ts,';');ts>>tmpd;ui->sb_p2_min->setValue(tmpd);

            ignore(ts,';');ts>>tmpd;ui->sb_p0_max->setValue(tmpd);
            ignore(ts,';');ts>>tmpd;ui->sb_p1_max->setValue(tmpd);
            ignore(ts,';');ts>>tmpd;ui->sb_p2_max->setValue(tmpd);

            ignore(ts,';');ts>>tmp;ui->sb_p0_res->setValue(tmp);
            ignore(ts,';');ts>>tmp;ui->sb_p1_res->setValue(tmp);
            ignore(ts,';');ts>>tmp;ui->sb_p2_res->setValue(tmp);

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

    std::cout<<p0<<" "<<p1<<std::endl;
    sys->selectId1(ui->cb_param1->currentIndex());
    sys->selectId2(ui->cb_param2->currentIndex());

    sys->setSolveMode(getAlgo());
    sys->set_p_init(p0,p1);
    worker.solveSystem(sys);
}

void MainWindow::slot_solve_over()
{
    sys->eval(sys->results.p_hat);
    sys->plot();

    //Path Image
    output_2d->setPath(sys->results.p_list,ui->cb_param1->currentIndex(),ui->cb_param2->currentIndex());
    output_2d->update();

    output_1d->setPath(sys->results.p_list,ui->cb_param1->currentIndex());
    output_1d->update();
}

void MainWindow::update_button_names_1d()
{
    ui->pb_calculate_func->setText(QString("Evaluate Y=f(p%1)").arg(sys->results.id1));
    ui->pb_calculate_conv->setText(QString("Convergence P=f(p%1)").arg(sys->results.id1));
    ui->rb_2D->setChecked(false);
    ui->rb_3D->setChecked(false);

    ui->sb_p0_min->setEnabled(true);ui->sb_p0_max->setEnabled(true);ui->sb_p0_res->setEnabled(true);
    ui->sb_p1_min->setEnabled(false);ui->sb_p1_max->setEnabled(false);ui->sb_p1_res->setEnabled(false);
    ui->sb_p2_min->setEnabled(false);ui->sb_p2_max->setEnabled(false);ui->sb_p2_res->setEnabled(false);
}

void MainWindow::update_button_names_2d()
{
    ui->pb_calculate_func->setText(QString("Evaluate Y=f(p%1,p%2)").arg(sys->results.id1).arg(sys->results.id2));
    ui->pb_calculate_conv->setText(QString("Convergence P=f(p%1,p%2)").arg(sys->results.id1).arg(sys->results.id2));
    ui->rb_1D->setChecked(false);
    ui->rb_3D->setChecked(false);

    ui->sb_p0_min->setEnabled(true);ui->sb_p0_max->setEnabled(true);ui->sb_p0_res->setEnabled(true);
    ui->sb_p1_min->setEnabled(true);ui->sb_p1_max->setEnabled(true);ui->sb_p1_res->setEnabled(true);
    ui->sb_p2_min->setEnabled(false);ui->sb_p2_max->setEnabled(false);ui->sb_p2_res->setEnabled(false);
}

void MainWindow::update_button_names_3d()
{
    ui->pb_calculate_func->setText(QString("Evaluate Y=f(p%1,p%2,p%3)").arg(sys->results.id1).arg(sys->results.id2).arg(sys->results.id3));
    ui->pb_calculate_conv->setText(QString("Convergence P=f(p%1,p%2,p%3)").arg(sys->results.id1).arg(sys->results.id2).arg(sys->results.id3));
    ui->rb_1D->setChecked(false);
    ui->rb_2D->setChecked(false);

    ui->sb_p0_min->setEnabled(true);ui->sb_p0_max->setEnabled(true);ui->sb_p0_res->setEnabled(true);
    ui->sb_p1_min->setEnabled(true);ui->sb_p1_max->setEnabled(true);ui->sb_p1_res->setEnabled(true);
    ui->sb_p2_min->setEnabled(true);ui->sb_p2_max->setEnabled(true);ui->sb_p2_res->setEnabled(true);
}

void MainWindow::id1_changed(int id)
{
    sys->results.id1=id;
    if(ui->rb_1D->isChecked())update_button_names_1d();
    if(ui->rb_2D->isChecked())update_button_names_2d();
    if(ui->rb_3D->isChecked())update_button_names_3d();
}

void MainWindow::id2_changed(int id)
{
    sys->results.id2=id;
    if(ui->rb_1D->isChecked())update_button_names_1d();
    if(ui->rb_2D->isChecked())update_button_names_2d();
    if(ui->rb_3D->isChecked())update_button_names_3d();
}

void MainWindow::id3_changed(int id)
{
    sys->results.id3=id;
    if(ui->rb_1D->isChecked())update_button_names_1d();
    if(ui->rb_2D->isChecked())update_button_names_2d();
    if(ui->rb_3D->isChecked())update_button_names_3d();
}
