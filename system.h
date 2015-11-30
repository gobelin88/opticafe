#ifndef SYSTEM_H
#define SYSTEM_H

#include <vector>
#include <QString>
#include <QStringList>
#include <QFile>
#include <iostream>
#include <qcustomplot.h>
#include <QTabWidget>
#include "lmfunctor.h"
#include <Eigen/Dense>
#include <unsupported/Eigen/NonLinearOptimization>
#include "newtonsolver.h"
#include "parameters.h"
#include "parser/parser.h"
#include "box.h"

struct SystemData
{
   std::vector< VectorXd > x,y;
};

struct Results
{
    Results()
    {
       reset();
    }

    int it_performed;
    double err_final;
    int time_elapsed;
    MatrixXd cov_hat,cor_hat;
    std::vector<VectorXd> p_list;
    VectorXd p_hat;

    void computeCor()
    {
        cor_hat.resize(cov_hat.rows(),cov_hat.cols());
        for(unsigned int i=0;i<cov_hat.rows();i++)
        {
            for(unsigned int j=0;j<cov_hat.cols();j++)
            {
                cor_hat(i,j)=std::abs(cov_hat(i,j)/sqrt(std::abs(cov_hat(i,i)*cov_hat(j,j))));
            }
        }
    }   

    void reset()
    {
        it_performed=0;
        err_final=0;
        time_elapsed=0;
        cov_hat.setZero();
        cor_hat.setZero();
        p_list.clear();
    }
};

class System:  public QTabWidget
{
    Q_OBJECT
public:
    void init(Parser * parser);
    System(Parser * parser);
    System(Parser * parser,int nb_p,int nb_x,int nb_y);
    System(Parser * parser,QString script);

    bool load_system(QString script);
    void load_p_init(QString script);
    void load_data(QString filename);
    void solve();
    void solve_Levmar();
    void solve_Dogleg();
    void solve_Gauss_Newton();

    void clearPlots();
    void plot();

    void set_p_init(double _p0,double _p1);
    void set_p_init(VectorXd p_init);
    std::vector< std::vector<int> > solve_2D_p0p1(Box box, ColorMode mode);

    VectorXd get_y(VectorXd p);

    void eval();
    VectorXd eval(VectorXd x,VectorXd p);

    static QImage toImage(const std::vector< std::vector<int> > & data, ScaleColorMode mode);
    static void searchMinMax(const std::vector< std::vector<int> > & data,int & min,int & max);

    void setProgressBar(QProgressBar * bar)
    {
        this->progress_bar=bar;
    }

    const SystemData & getSystemData(){return data;}
    const SystemData & getSystemModel(){return model;}
    VectorXd serialize(std::vector<VectorXd> v);

    VectorXd p0;


    void setSolveMode(SolveMode mode){this->solve_mode=mode;}
    SolveMode getSolveMode(){return solve_mode;}

    ParamHandler * getParamHandler(){return &handler;}

    Results results;

private:
    //Gui
    std::vector<QWidget*> plots;
    QProgressBar * progress_bar;

    //Solve & Data
    SolveMode solve_mode;
    int getNB(char c,QString script);
    QVector<double> extract(std::vector<VectorXd> v, int id);
    QByteArray getCharName(char var,int var_id);
    double getRMS(int id);
    int nb_p,nb_x,nb_y;
    std::vector<QByteArray> eq_list;
    SystemData data,model;
    VectorXd y_serialized;

    //Parser & Helper
    ParamHandler handler;
    Parser * ptr_parser;
};

class SystemFunctor:public LMFunctor<double>
{
public:
    SystemFunctor(System * system_ptr){setSystem(system_ptr);}

    inline void setSystem(System * system_ptr)
    {
        this->sys=system_ptr;
        this->y_serialized=sys->serialize(sys->getSystemData().y);

        m_values=y_serialized.rows();
        m_inputs=sys->p0.rows();
    }

    int operator()(const Eigen::VectorXd &p, Eigen::VectorXd &fvec)const
    {
        fvec=sys->get_y(p)-this->y_serialized;

        return 0;
    }

private:
    System * sys;
    VectorXd y_serialized;
};


#endif
