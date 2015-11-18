#include "system.h"


System::System(Parser * parser,int nb_p,int nb_x,int nb_y):QTabWidget()
{
    this->ptr_parser=parser;
    this->nb_p=nb_p;
    this->nb_x=nb_x;
    this->nb_y=nb_y;
    eq_list.resize(nb_y);
    p0.resize(nb_p);

    it=500;
    progress_bar=NULL;
}

System::System(Parser * parser,QString script)
{
    this->ptr_parser=parser;
    eq_list.clear();
    load_system(script);
    progress_bar=NULL;
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

void System::load_system(QString script)
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

    std::cout<<"nb_x="<<nb_x<<std::endl;
    std::cout<<"nb_y="<<nb_y<<std::endl;
    std::cout<<"nb_p="<<nb_p<<std::endl;

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
                std::cout<<"Erreur : Equation incohérente"<<std::endl;
            }
        }
    }
    else
    {
        std::cout<<"Erreur : Le nombre d'équations est incohérent avec le nombre de sorties"<<std::endl;
    }

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
    QFile file(filename);

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QStringList content=QString(file.readAll()).split('\n',QString::SkipEmptyParts);

        for(int i=0;i<content.size();i++)
        {
            QStringList line=content[i].split(";",QString::SkipEmptyParts);

            if(line.size()==nb_y+nb_x)
            {
                vectord yp(nb_y),xp(nb_x);
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

std::vector< std::vector<int> > System::solve_2D_p0p1(double p0_min,double p0_max,
                                                      double p1_min,double p1_max,
                                                      int width,int height,ColorMode mode)
{
    std::vector<std::vector<int>> map2D(width,std::vector<int>(height,0.0));

    for(int i=0;i<width;i++)
    {
        for(int j=0;j<height;j++)
        {
            p0[0]=(i*(p0_max-p0_min))/width+p0_min;
            p0[1]=(j*(p1_max-p1_min))/height+p1_min;

            it=100;
            solve();

            //std::cout<<i<<" "<<j<<" "<<info[5]<<std::endl;

            if(MODE_ARG==mode)map2D[i][j]=atan2(p_hat[0],p_hat[1]);
            else if(MODE_IT==mode)map2D[i][j]=(int)info[5];
        }

        progress_bar->setValue(i);
        progress_bar->repaint();
    }

    return map2D;
}

void System::solve()
{
    vectord y_vec=serialize(data.y);

    cov_hat.resize(p0.size()*p0.size());

    double opts[LM_OPTS_SZ]={0,LM_STOP_THRESH,LM_STOP_THRESH,LM_STOP_THRESH,-LM_DIFF_DELTA};

    dlevmar_dif(levmar_func,p0.data(),y_vec.data(),p0.size(),y_vec.size(),it,opts,info,NULL,cov_hat.data(),this);

    cor_hat.resize(cov_hat.size());
    for(unsigned int i=0;i<p0.size();i++)
    {
        for(unsigned int j=0;j<p0.size();j++)
        {
            cor_hat[i*p0.size()+j]=std::abs(cov_hat[i*p0.size()+j]/sqrt(std::abs(cov_hat[i*p0.size()+i]*cov_hat[j*p0.size()+j])));
        }
    }
}

vectord System::get_y(vectord p)
{
    vectord err(data.y.size()*nb_y,0.0);

    for(unsigned int i=0;i<data.x.size();i++)
    {
        vectord yi=eval(data.x[i],p);

        for(unsigned int j=0;j<yi.size();j++)
        {
            err[i*yi.size()+j]=yi[j];
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
        vectord yi=eval(data.x[i],p_hat);

        model.x.push_back(data.x[i]);
        model.y.push_back(yi);
    }
}

vectord System::eval(vectord x,vectord p)
{
    vectord y(nb_y,0);

    if(x.size()==nb_x && p.size()==nb_p)
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

void System::levmar_func(double *p, double *hx, int m, int n, void *adata)
{
    System * sys=(System*)adata;

    sys->p_hat=vectord(p,p+sys->nb_p);

    vectord y_vec=sys->get_y(sys->p_hat);

    memcpy(hx,y_vec.data(),y_vec.size()*sizeof(double));
}

vectord System::serialize(std::vector<vectord> v)
{
    vectord v_serilized(v[0].size()*v.size());
    for(unsigned int i=0;i<v.size();i++)
    {
        for(unsigned int j=0;j<v[0].size();j++)
        {
            v_serilized[i*v[0].size()+j]=v[i][j];
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

void System::clearPlots()
{
    for(unsigned int i=0;i<plots.size();i++)
    {
        delete plots[i];
    }
    plots.clear();
}

QVector<double> System::extract(std::vector<vectord> v,int id)
{
    QVector<double> v_out(v.size());
    for(int i=0;i<v.size();i++)
    {
        v_out[i]=v[i][id];
    }
    return v_out;
}

void System::searchMinMax(const std::vector< std::vector<int> > & data,int & min,int & max)
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

QImage System::toImage(const std::vector< std::vector<int> > & data, ScaleColorMode mode)
{
    QImage image(QSize(data.size(),data[0].size()),QImage::Format_RGB32);

    int min,max;
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

void System::plot()
{
    this->setWindowTitle("System Results");

    clearPlots();

    QTextEdit * widget_results=new QTextEdit(this);
    QString p_str,cov_str,cor_str,levmar_str;
    for(int i=0;i<p_hat.size();i++)
    {
        p_str+=QString("p[%1]=%2\n").arg(i).arg(p_hat[i]);
    }

    cov_str=QString("Cov(p,p)=\n");
    for(int i=0;i<p_hat.size();i++)
    {
        for(int j=0;j<p_hat.size();j++)
        {
            cov_str+=QString("%1  ").arg(cov_hat[i*p_hat.size()+j],8,'f',3,' ');
        }
        cov_str+=QString("\n");
    }

    cor_str=QString("Cor(p,p)=\n");
    for(int i=0;i<p_hat.size();i++)
    {
        for(int j=0;j<p_hat.size();j++)
        {
            cor_str+=QString("%1  ").arg(cor_hat[i*p_hat.size()+j],8,'f',3,' ');
        }
        cor_str+=QString("\n");
    }

    levmar_str=QString("Levenberg-Marquardt=\n");
    levmar_str+=QString("   -->||e||_2 at initial p= %1\n").arg(info[0]);
    levmar_str+=QString("   -->||e||_2= %1\n").arg(info[1]);
    levmar_str+=QString("   -->iterations= %1\n").arg(info[5]);
    levmar_str+=QString("   -->reason for terminating= %1\n").arg(info[6]);

    levmar_str+=QString("1 - stopped by small gradient J^T e\n");
    levmar_str+=QString("2 - stopped by small Dp\n");
    levmar_str+=QString("3 - stopped by itmax\n");
    levmar_str+=QString("4 - singular matrix. Restart from current p with increased \mu\n");
    levmar_str+=QString("5 - no further error reduction is possible. Restart with increased mu\n");
    levmar_str+=QString("6 - stopped by small ||e||_2\n");
    levmar_str+=QString("7 - stopped by invalid (i.e. NaN or Inf) func values; a user error\n");

    widget_results->append(p_str);
    widget_results->append(cor_str);
    widget_results->append(cov_str);
    widget_results->append(levmar_str);

    addTab(widget_results,"Results");

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
