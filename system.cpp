#include "system.h"

void System::init()
{
    id_active=0;
    handler=new ParamHandler;

    expr_str.clear();
    progress_bar=NULL;
    progress_bar=NULL;
    results.reset();


    memset(P,0,sizeof(double)*9);
    memset(X,0,sizeof(double)*9);
}

System::System()
{
    init();
}

System::System(QString script)
{
    init();
    load_system(script);
}

int System::getNB(char c,QString script)
{
    int cpt=0;
    for(int i=0;i<10;i++)
    {
        if(script.contains(QString(c)+QString::number(i)))
        {
            cpt=i+1;
        }
    }
    return cpt;
}

bool System::compile()
{
    for(int i=0;i<nb_y;i++)
    {
        expr[i].register_symbol_table(symbol_table);
        bool ok=parser.compile(expr_str[i].toStdString(),expr[i]);

        if(!ok)return false;
    }
    return true;
}

bool System::load_system(QString script)
{
    expr_str.clear();
    symbol_table.clear();
    symbol_table.add_constants();

    nb_x=getNB('x',script);
    nb_y=getNB('y',script);
    nb_p=getNB('p',script);

    expr.resize(nb_y);
    expr_str.resize(nb_y);
    p0.resize(nb_p);p0.setZero();

    for(int i=0;i<nb_p;i++){symbol_table.add_variable(getCharName('p',i).toStdString(),P[i]);}
    for(int i=0;i<nb_x;i++){symbol_table.add_variable(getCharName('x',i).toStdString(),X[i]);}

    QStringList lines=script.split('\n',QString::SkipEmptyParts);

    load_null_data();//Si pas de data yn=0 xn=0

    for(int i=0;i<lines.size();i++)
    {
        QStringList args=lines[i].split('=');

        if(args.size()==2 && !args[1].isEmpty())
        {
            if(args[0].contains('y'))
            {
                args[0].remove(0,1);
                int id=args[0].toInt();
                expr_str[id]=args[1].toLocal8Bit();
            }
            else if(args[0].contains("data"))
            {
                if(!load_data(args[1]))return false;
            }
            else if(args[0].contains("p_init"))
            {
                if(!load_p_init(args[1]))return false;
            }
            else
            {
                QMessageBox::critical(this,"Syntax Error",QString("Syntax error line %1 : %2").arg(i).arg(lines[i]));
                return false;
            }
        }
        else
        {
            QMessageBox::critical(this,"Syntax Error",QString("Syntax error line %1 : %2").arg(i).arg(lines[i]));
            return false;
        }
    }

    return compile();
}

bool System::load_p_init(QString script)
{
    QStringList p_init_str=script.split(",",QString::SkipEmptyParts);

    if(p_init_str.size()==nb_p)
    {
        for(int i=0;i<nb_p;i++)
        {
            p0[i]=p_init_str[i].toDouble();
        }
    }
    else
    {
        QMessageBox::critical(this,"Error",QString("Wrong dimension for p_init %1 : expected %2").arg(p_init_str.size()).arg(nb_p));
        return false;
    }
    return true;
}

void System::load_null_data()
{
    data.x.clear();
    data.y.clear();
    VectorXd yp(nb_y),xp(nb_x);
    data.x.push_back(xp);
    data.y.push_back(yp);
}

bool System::load_data(QString filename)
{
    data.x.clear();
    data.y.clear();

    QFile file(filename);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QStringList content=QString(file.readAll()).split('\n',QString::SkipEmptyParts);

        for(int i=0;i<content.size();i++)
        {
            QStringList line=content[i].split(";",QString::SkipEmptyParts);

            if(line.size()==nb_y+nb_x)
            {
                VectorXd yp(nb_y),xp(nb_x);
                for(int i=0;i<nb_x;i++)
                {
                    xp[i]=line[i].toDouble();
                }
                data.x.push_back(xp);
                for(int i=0;i<nb_y;i++)
                {
                    yp[i]=line[i+nb_x].toDouble();
                }
                data.y.push_back(yp);
            }
            else
            {
                QMessageBox::critical(this,"Error",QString("Wrong colums numbers in data file  %1 : expected %2").arg(line.size()).arg(nb_x+nb_y));
                return false;
            }
        }
        file.close();
    }
    else
    {
        QMessageBox::critical(this,"Error",QString("Failed to open data file: %1 ").arg(filename.toLocal8Bit().data()));
        return false;
    }
    return true;
}



void System::set_p_init(double _p0,double _p1)
{
    p0[results.id1]=_p0;
    p0[results.id2]=_p1;
}

void System::set_p_init(double _p0,double _p1,double _p2)
{
    p0[results.id1]=_p0;
    p0[results.id2]=_p1;
    p0[results.id3]=_p2;
}

void System::set_p_init(VectorXd p_init)
{
    p0=p_init;
}

double System::getColorModeValue(ColorMode mode)
{
    double value=0.0;

    if(MODE_ARG==mode)value=atan2(results.p_hat[0],results.p_hat[1]);
    else if(MODE_IT==mode)value=(int)results.it_performed;
    else if(MODE_MODULE==mode)value=results.p_hat.norm();
    else if(MODE_Y0==mode)value=results.p_hat[0];
    else if(MODE_Y1==mode)value=results.p_hat[1];
    else{value=0;}

    return value;
}

std::vector<double> System::solve_1D_p0(Box box, ColorMode mode)
{
    std::vector<double> map1D(box.p0_res,0.0);

    for(int i=0;i<box.p0_res;i++)
    {
        p0[results.id1]=box.getP0(i);

        //std::cout<<i<<" "<<j<<" "<<results.id1<<" "<<results.id2<<" "<<p0[results.id1]<<" "<<p0[results.id2]<<std::endl;

        solve();
        map1D[i]=getColorModeValue(mode);

        emit progress(i);
    }
    return map1D;
}

std::vector< std::vector<double> > System::solve_2D_p0p1(Box box, ColorMode mode)
{
    std::vector<std::vector<double>> map2D(box.p0_res,std::vector<double>(box.p1_res,0.0));

    for(int i=0;i<box.p0_res;i++)
    {
        for(int j=0;j<box.p1_res;j++)
        {
            p0[results.id1]=box.getP0(i);
            p0[results.id2]=box.getP1(j);

            //std::cout<<i<<" "<<j<<" "<<results.id1<<" "<<results.id2<<" "<<p0[results.id1]<<" "<<p0[results.id2]<<std::endl;

            solve();
            map2D[i][j]=getColorModeValue(mode);
        }
        emit progress(i);
    }
    return map2D;
}

std::vector< std::vector< std::vector<double> > > System::solve_3D_p0p1p2(Box box, ColorMode mode)
{
    std::vector< std::vector< std::vector<double> > > map3D(box.p0_res,std::vector<std::vector<double>>(box.p1_res,std::vector<double>(box.p2_res,0.0)));

    for(int i=0;i<box.p0_res;i++)
    {
        for(int j=0;j<box.p1_res;j++)
        {
            for(int k=0;k<box.p2_res;k++)
            {
                p0[results.id1]=box.getP0(i);
                p0[results.id2]=box.getP1(j);
                p0[results.id3]=box.getP2(k);

                solve();
                map3D[i][j][k]=getColorModeValue(mode);
            }
        }

        emit progress(i);
    }

    return map3D;
}

std::vector<double> System::eval_1D_p0(Box box, ColorMode mode)
{
    std::vector<double> map1D(box.p0_res,0.0);

    for(int i=0;i<box.p0_res;i++)
    {
        p0[results.id1]=box.getP0(i);

        results.p_hat=evalErr(p0);
        map1D[i]=getColorModeValue(mode);

        emit progress(i);
    }
    return map1D;
}

std::vector< std::vector<double> > System::eval_2D_p0p1(Box box, ColorMode mode)
{
    std::vector<std::vector<double>> map2D(box.p0_res,std::vector<double>(box.p1_res,0.0));

    for(int i=0;i<box.p0_res;i++)
    {
        for(int j=0;j<box.p1_res;j++)
        {
            p0[results.id1]=box.getP0(i);
            p0[results.id2]=box.getP1(j);

            results.p_hat=evalErr(p0);
            map2D[i][j]=getColorModeValue(mode);
        }
        emit progress(i);
    }
    return map2D;
}

std::vector< std::vector< std::vector<double> > > System::eval_3D_p0p1p2(Box box, ColorMode mode)
{
    std::vector< std::vector< std::vector<double> > > map3D(box.p0_res,std::vector<std::vector<double>>(box.p1_res,std::vector<double>(box.p2_res,0.0)));

    for(int i=0;i<box.p0_res;i++)
    {
        for(int j=0;j<box.p1_res;j++)
        {
            for(int k=0;k<box.p2_res;k++)
            {
                p0[results.id1]=box.getP0(i);
                p0[results.id2]=box.getP1(j);
                p0[results.id3]=box.getP2(k);

                results.p_hat=evalErr(p0);
                map3D[i][j][k]=getColorModeValue(mode);
            }
        }

        emit progress(i);
    }

    return map3D;
}


void System::solve()
{
    results.reset();

    QElapsedTimer timer;
    timer.start();

    if(solve_mode==MODE_LEVMAR)solve_Levmar();
    else if(solve_mode==MODE_DOGLEG)solve_Dogleg();
    else if(solve_mode==MODE_GAUSS_NEWTON)solve_Gauss_Newton();
    else
    {
        solve_Levmar();
    }

    results.time_elapsed=timer.elapsed();
    results.computeCor();
}

void System::solve_Levmar()
{
    y_serialized=serialize(data.y);

    std::vector<VectorXd> p_list;
    SystemFunctor functor(this,&p_list);
    Eigen::NumericalDiff<SystemFunctor> numdiff (functor,handler->sb_delta->value()) ;
    Eigen::LevenbergMarquardt< Eigen::NumericalDiff<SystemFunctor>> solver(numdiff);
    solver.parameters.maxfev=handler->sb_it_max->value();
    solver.parameters.gtol=handler->sb_dp_min->value();
    solver.parameters.ftol=handler->sb_df_min->value();
    solver.parameters.factor=handler->sb_levmar_lambda->value();
    results.p_hat=p0;
    solver.minimize(results.p_hat);

    //Results
    results.p_list=*functor.p_list;
    results.it_performed=solver.iter;
    results.err_final=solver.fnorm;
    results.cov_hat=(solver.fjac.transpose()*solver.fjac).inverse();
}

void System::solve_Dogleg()
{
    y_serialized=serialize(data.y);

    std::vector<VectorXd> p_list;
    SystemFunctor functor(this,&p_list);
    Eigen::NumericalDiff<SystemFunctor> numdiff (functor,handler->sb_delta->value()) ;
    Eigen::HybridNonLinearSolver< Eigen::NumericalDiff<SystemFunctor>> solver(numdiff);
    solver.parameters.maxfev=handler->sb_it_max->value();
    solver.parameters.xtol=handler->sb_dp_min->value();
    solver.parameters.factor=handler->sb_dogleg_lambda->value();
    results.p_hat=p0;
    solver.solve(results.p_hat);

    //Results
    results.p_list=*functor.p_list;
    results.it_performed=solver.iter;
    results.err_final=solver.fnorm;
    results.cov_hat=(solver.fjac.transpose()*solver.fjac).inverse();
}

void System::solve_Gauss_Newton()
{
    y_serialized=serialize(data.y);

    std::vector<VectorXd> p_list;
    SystemFunctor functor(this,&p_list);
    Eigen::NumericalDiff<SystemFunctor> numdiff (functor) ;
    NewtonSolver< Eigen::NumericalDiff<SystemFunctor> > solver(numdiff);
    solver.parameters.maxfev=handler->sb_it_max->value();
    solver.parameters.gtol=handler->sb_dp_min->value();
    solver.parameters.ftol=handler->sb_df_min->value();
    solver.parameters.factor=handler->sb_newton_lambda->value();
    results.p_hat=p0;

    solver.minimize(results.p_hat);

    //Results
    results.p_list=*functor.p_list;
    results.it_performed=solver.iter;
    results.err_final=solver.fnorm;
    results.cov_hat=(solver.fjac.transpose()*solver.fjac).inverse();
}

VectorXd System::get_y(VectorXd p)
{
    VectorXd Yij(data.y.size()*nb_y);
    Yij.setZero();

    unsigned int id=0;
    for(unsigned int i=0;i<data.x.size();i++)
    {
        VectorXd yi=eval(data.x[i],p);
        for(int j=0;j<yi.rows();j++)
        {
            Yij[id++]=yi[j];
        }
    }

    return Yij;
}

VectorXd System::eval(VectorXd p)
{
    model.x.clear();
    model.y.clear();

    for(unsigned int i=0;i<data.x.size();i++)
    {
        VectorXd yi=eval(data.x[i],p);

        model.x.push_back(data.x[i]);
        model.y.push_back(yi);
    }

    return serialize(model.y);
}

VectorXd System::evalErr(VectorXd p)
{
    model.x.clear();
    model.y.clear();

    for(unsigned int i=0;i<data.x.size();i++)
    {
        VectorXd yi=eval(data.x[i],p);

        model.x.push_back(data.x[i]);
        model.y.push_back(yi);
    }

    return serialize(model.y)-serialize(data.y);
}

VectorXd System::eval(VectorXd x,VectorXd p)
{
    VectorXd y(nb_y);
    y.setZero();

    if(x.rows()==nb_x && p.rows()==nb_p)
    {
        for(int i=0;i<nb_p;i++){P[i]=p[i];}
        for(int i=0;i<nb_x;i++){X[i]=x[i];}
        for(int i=0;i<nb_y;i++){y[i]=expr[i].value();}
    }
    else
    {
        std::cout<<"Erreur"<<std::endl;
    }

    return y;
}

VectorXd System::eval_atX0(VectorXd p)
{
    VectorXd y(nb_y);
    y.setZero();

    if(p.rows()==nb_p)
    {
        for(int i=0;i<nb_p;i++){P[i]=p[i];}
        for(int i=0;i<nb_x;i++){X[i]=0.0;}
        for(int i=0;i<nb_y;i++){y[i]=expr[i].value();}
    }
    else
    {
        std::cout<<"Erreur"<<std::endl;
    }

    return y;
}

/*void System::levmar_func(double *p, double *hx, int m, int n, void *adata)
{
    System * sys=(System*)adata;

    sys->p_hat=VectorXd(p,p+sys->nb_p);

    VectorXd y_vec=sys->get_y(sys->p_hat);

    memcpy(hx,y_vec.data(),y_vec.size()*sizeof(double));
}*/

VectorXd System::serialize(const std::vector<VectorXd> & v)
{
    VectorXd v_serilized(v[0].rows()*v.size());
    unsigned int id=0;
    for(unsigned int i=0;i<v.size();i++)
    {
        for(int j=0;j<v[0].rows();j++)
        {
            v_serilized[id++]=v[i][j];
        }
    }
    return v_serilized;
}

QByteArray System::getCharName(char var,int var_id)
{
    QByteArray v(2,0);
    v[0]=var;
    v[1]=var_id+'0';
    return v;
}

QVector<double> System::extract(std::vector<VectorXd> v,int id)
{
    QVector<double> v_out(v.size());
    for(unsigned int i=0;i<v.size();i++)
    {
        v_out[i]=v[i][id];
    }
    return v_out;
}

void System::clearPlots()
{
    id_active=this->currentIndex();
    for(unsigned int i=0;i<plots.size();i++)
    {
        delete plots[i];
    }
    plots.clear();
}

void System::plot()
{

    this->setWindowTitle(QString("System Results for %1 minimisation").arg(SolveMode_str[(int)solve_mode]));

    clearPlots();

    QTextEdit * widget_results=new QTextEdit(this);
    QString p_str,cov_str,cor_str,levmar_str;
    for(int i=0;i<results.p_hat.rows();i++)
    {
        p_str+=QString("p[%1]=%2\n").arg(i).arg(results.p_hat[i]);
    }

    cov_str=QString("Cov(p,p)=\n");
    for(int i=0;i<results.p_hat.rows();i++)
    {
        for(int j=0;j<results.p_hat.rows();j++)
        {
            cov_str+=QString("%1  ").arg(results.cov_hat(i,j),8,'f',3,' ');
        }
        cov_str+=QString("\n");
    }

    cor_str=QString("Cor(p,p)=\n");
    for(int i=0;i<results.p_hat.rows();i++)
    {
        for(int j=0;j<results.p_hat.rows();j++)
        {
            cor_str+=QString("%1  ").arg(results.cor_hat(i,j),8,'f',3,' ');
        }
        cor_str+=QString("\n");
    }

    levmar_str=QString("Algorithme=\n");
    levmar_str+=QString("   -->Iterations= %1\n").arg(results.it_performed);
    levmar_str+=QString("   -->Residu= %1\n").arg(results.err_final);
    levmar_str+=QString("   -->Time spent = %1\n").arg(results.time_elapsed);

    widget_results->append(p_str);
    widget_results->append(cor_str);
    widget_results->append(cov_str);
    widget_results->append(levmar_str);

    addTab(widget_results,"Results");
    plots.push_back(widget_results);

    for(int j=0;j<nb_x;j++)
    {
        for(int i=0;i<nb_y;i++)
        {
            QCustomPlot * new_plot=new QCustomPlot(this);

            new_plot->addGraph();
            QPen pen_data(QColor(0,0,255));
            pen_data.setStyle(Qt::SolidLine);
            new_plot->graph()->setBrush(QBrush(QColor(0,0,255,32)));
            new_plot->graph()->setPen(pen_data);
            new_plot->graph()->setName("Data");
            new_plot->graph()->setData(extract(data.x,j), extract(data.y,i));
            new_plot->graph()->setLineStyle(QCPGraph::lsLine);
            new_plot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlus, 10));
            new_plot->rescaleAxes();
            //new_plot->setInteractions(QCP::iRangeDrag);
            new_plot->legend->setVisible(true);
            new_plot->legend->setFont(QFont("Helvetica", 9));

            new_plot->addGraph();
            QPen pen_model(QColor(255,1,0));
            pen_model.setStyle(Qt::SolidLine);
            new_plot->graph()->setPen(pen_model);
            new_plot->graph()->setName(QString("Model rms=%1").arg(getRMS(i)));
            new_plot->graph()->setData(extract(model.x,j), extract(model.y,i));
            new_plot->graph()->setLineStyle(QCPGraph::lsLine);
            new_plot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlus, 10));
            new_plot->rescaleAxes();
            //new_plot->setInteractions(QCP::iRangeDrag);
            new_plot->legend->setVisible(true);
            new_plot->legend->setFont(QFont("Helvetica", 9));

            addTab(new_plot,QString("y%1 = f(x%2)").arg(i).arg(j));
            plots.push_back(new_plot);
        }
    }

    QCustomPlot * new_plot_all=new QCustomPlot(this);
    for(int j=0;j<nb_x;j++)
    {
        for(int i=0;i<nb_y;i++)
        {
            new_plot_all->addGraph();
            int c= new_plot_all->graphCount();
            QPen pen_model(QColor(color_tab[c][0]*128,color_tab[c][1]*128,color_tab[c][2]*128));
            pen_model.setStyle(Qt::SolidLine);
            new_plot_all->graph()->setPen(pen_model);
            new_plot_all->graph()->setName(QString("Model(y%2,x%3) rms=%1").arg(getRMS(i)).arg(i).arg(j));
            new_plot_all->graph()->setData(extract(model.x,j), extract(model.y,i));
            new_plot_all->graph()->setLineStyle(QCPGraph::lsLine);
            new_plot_all->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssPlus, 10));
            new_plot_all->rescaleAxes();
            //new_plot->setInteractions(QCP::iRangeDrag);
            new_plot_all->legend->setVisible(true);
            new_plot_all->legend->setFont(QFont("Helvetica", 9));
        }
    }

    if(nb_x>0)
    {
        addTab(new_plot_all,QString("All Fit"));
        plots.push_back(new_plot_all);
    }

    this->setCurrentIndex(id_active);
}

double System::getRMS(int id)
{
    double sum=0.0,cpt=0;
    for(unsigned int i=0;i<data.x.size();i++)
    {
        sum+= (data.y[i][id]-model.y[i][id])*(data.y[i][id]-model.y[i][id]);
        cpt++;
    }
    return sqrt(sum/cpt);
}
