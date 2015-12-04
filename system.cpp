#include "system.h"

void System::init(Parser * parser)
{
    id_active=0;
    id1=0;
    id2=1;
    handler=new ParamHandler;

    this->ptr_parser=parser;
    eq_list.clear();
    progress_bar=NULL;
    progress_bar=NULL;
    results.reset();
}

System::System(Parser * parser)
{
    init(parser);
}

System::System(Parser * parser,int nb_p,int nb_x,int nb_y)
{
    init(parser);

    this->nb_p=nb_p;
    this->nb_x=nb_x;
    this->nb_y=nb_y;
    eq_list.resize(nb_y);
    p0.resize(nb_p);
}

System::System(Parser * parser,QString script)
{
    init(parser);
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

bool System::load_system(QString script)
{
    eq_list.clear();

    nb_x=getNB('x',script);
    nb_y=getNB('y',script);
    nb_p=getNB('p',script);

    eq_list.resize(nb_y);
    p0.resize(nb_p);

    ptr_parser->getVarList().clear();
    for(int i=0;i<nb_p;i++){ptr_parser->getVarList().add(getCharName('p',i),0.0);}
    for(int i=0;i<nb_x;i++){ptr_parser->getVarList().add(getCharName('x',i),0.0);}

//    std::cout<<"nb_x="<<nb_x<<std::endl;
//    std::cout<<"nb_y="<<nb_y<<std::endl;
//    std::cout<<"nb_p="<<nb_p<<std::endl;

    QStringList lines=script.split('\n',QString::SkipEmptyParts);

    if((lines.size()-2)==nb_y)
    {
        for(int i=0;i<lines.size();i++)
        {
            QStringList args=lines[i].split('=');

            if(args.size()==2)
            {
                if(args[0].contains('y'))
                {
                    args[0].remove(0,1);
                    int id=args[0].toInt();
                    eq_list[id]=args[1].toLocal8Bit();
                    std::cout<<args[1].toLocal8Bit().data()<<std::endl;
                }
                else if(args[0].contains("data"))
                {
                    load_data(args[1]);
                }
                else if(args[0].contains("p_init"))
                {
                    load_p_init(args[1]);
                }

            }
            else
            {
                QMessageBox::critical(this,"Syntax Error",QString("Line %1").arg(i));
                return false;
            }
        }
    }
    else
    {
        QMessageBox::critical(this,"Structure Error",QString("The number of equation does'nt match the number of outputs"));
        return false;
    }
    return true;
}

void System::load_p_init(QString script)
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
        std::cout<<"Erreur :  La dimension de p_init est incohérente"<<std::endl;
    }

}

void System::load_data(QString filename)
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
                std::cout<<"Erreur : La dimension des lignes ne correspond pas au systeme"<<line.size()<<" "<<nb_x+nb_y<<std::endl;
            }
        }

        std::cout<<"data x="<<data.x.size()<<" y="<<data.y.size()<<std::endl;

        file.close();
    }
    else
    {
        std::cout<<"Erreur : Impossible d'ouvrir le fichier "<<filename.toLocal8Bit().data()<<std::endl;
    }
}

void System::set_p_init(double _p0,double _p1)
{
    p0[id1]=_p0;
    p0[id2]=_p1;
}

void System::set_p_init(VectorXd p_init)
{
    p0=p_init;
}

std::vector< std::vector<double> > System::solve_2D_p0p1(Box box, ColorMode mode)
{
    std::cout<<"solve_2D_p0p1"<<std::endl;

    std::vector<std::vector<double>> map2D(box.p0_res,std::vector<double>(box.p1_res,0.0));

    for(int i=0;i<box.p0_res;i++)
    {
        for(int j=0;j<box.p1_res;j++)
        {
            p0[id1]=box.getP0(i);
            p0[id2]=box.getP1(j);

            solve();       

            //std::cout<<i<<" "<<j<<" "<<info[5]<<std::endl;
            if(MODE_ARG==mode)map2D[i][j]=atan2(results.p_hat[0],results.p_hat[1]);
            else if(MODE_IT==mode)map2D[i][j]=(int)results.it_performed;
        }

        emit progress(i);
    }

    return map2D;
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
    VectorXd err(data.y.size()*nb_y);
    err.setZero();

    for(unsigned int i=0;i<data.x.size();i++)
    {
        VectorXd yi=eval(data.x[i],p);

        for(unsigned int j=0;j<yi.rows();j++)
        {
            err[i*yi.rows()+j]=yi[j];
        }
    }

    return err;
}

void System::eval()
{
    model.x.clear();
    model.y.clear();

    for(unsigned int i=0;i<data.x.size();i++)
    {
        VectorXd yi=eval(data.x[i],results.p_hat);

        model.x.push_back(data.x[i]);
        model.y.push_back(yi);
    }
}

VectorXd System::eval(VectorXd x,VectorXd p)
{
    VectorXd y(nb_y);
    y.setZero();

    if(x.rows()==nb_x && p.rows()==nb_p)
    {

        ptr_parser->getVarList().clear();
        for(int i=0;i<nb_p;i++)
        {
            ptr_parser->getVarList().set_value(getCharName('p',i),p[i]);
            //std::cout<<"p["<<i<<"]="<<p[i]<<" "<<ptr_parser->parse(getCharName('p',i))<<std::endl;
        }
        for(int i=0;i<nb_x;i++)
        {
            ptr_parser->getVarList().set_value(getCharName('x',i),x[i]);
            //std::cout<<"x["<<i<<"]="<<x[i]<<" "<<ptr_parser->parse(getCharName('x',i))<<" "<<ptr_parser->parse("x2")<<std::endl;
        }

        for(int i=0;i<nb_y;i++)
        {
            y[i]=ptr_parser->parse(eq_list[i].data());
            //std::cout<<"y["<<i<<"]="<<y[i]<<" "<<eq_list[i].data()<<std::endl;
        }
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

VectorXd System::serialize(std::vector<VectorXd> v)
{
    VectorXd v_serilized(v[0].rows()*v.size());
    for(unsigned int i=0;i<v.size();i++)
    {
        for(unsigned int j=0;j<v[0].rows();j++)
        {
            v_serilized[i*v[0].rows()+j]=v[i][j];
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
    for(int i=0;i<v.size();i++)
    {
        v_out[i]=v[i][id];
    }
    return v_out;
}

void System::searchMinMax(const std::vector<std::vector<double> > &data, double &min, double &max)
{
    min=data[0][0];
    max=data[0][0];

    for(int i=1;i<data.size();i++)
    {
        for(int j=0;j<data[0].size();j++)
        {
            if(data[i][j]<min)min=data[i][j];
            if(data[i][j]>max)max=data[i][j];
        }
    }
}

QImage System::toImage(const std::vector< std::vector<double> > & data, ScaleColorMode mode)
{
    QImage image(QSize(data.size(),data[0].size()),QImage::Format_RGB32);

    double min,max;
    searchMinMax(data,min,max);

    for(int i=0;i<image.width();i++)
    {
        for(int j=0;j<image.height();j++)
        {
            if(mode==MODE_BLUE_GRADIENT)
            {
                int value= (255.0*(data[i][j]-min))/(max-min);
                image.setPixel(i,j,qRgb(value,std::min(255,2*value),std::min(255,3*value)));
            }
            else if(mode==MODE_PERIODIC)
            {
                double value= (M_PI*(data[i][j]-min))/(max-min);
                image.setPixel(i,j,qRgb(255*sin(value),255*sin(value+2*M_PI/3),255*sin(value+4*M_PI/3)));
            }
        }
    }

    return image;
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

    addTab(new_plot_all,QString("All Fit"));
    plots.push_back(new_plot_all);


    this->setCurrentIndex(id_active);
}

double System::getRMS(int id)
{
    double sum=0.0,cpt=0;
    for(int i=0;i<data.x.size();i++)
    {
        sum+= (data.y[i][id]-model.y[i][id])*(data.y[i][id]-model.y[i][id]);
        cpt++;
    }
    return sqrt(sum/cpt);
}
