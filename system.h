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
#include "exprtk/exprtk.hpp"
#include "box.h"

using Eigen::Vector3d;

struct SystemData
{
    std::vector< VectorXd > x,y;
};

class Results
{
public:
    Results()
    {
        reset();
        id1=-1;
        id2=-1;
        id3=-1;
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
        for(int i=0;i<cov_hat.rows();i++)
        {
            for(int j=0;j<cov_hat.cols();j++)
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

    int id1,id2,id3;
};

class System:  public QTabWidget
{
    Q_OBJECT
public:
    void init();
    System();
    System(QString script);

    bool compile();
    bool load_system(QString script);
    bool load_p_init(QString script);
    void load_null_data();
    bool load_data(QString filename);

    void solve();
    void solve_Levmar();
    void solve_Dogleg();
    void solve_Gauss_Newton();

    void clearPlots();
    void plot();

    void set_p_init(double _p0,double _p1);
    void set_p_init(double _p0, double _p1, double _p2);
    void set_p_init(VectorXd p_init);

    double System::getColorModeValue(ColorMode mode);
    std::vector<double> solve_1D_p0(Box box, ColorMode mode);
    std::vector< std::vector<double> > solve_2D_p0p1(Box box, ColorMode mode);
    std::vector< std::vector< std::vector<double> > > solve_3D_p0p1p2(Box box, ColorMode mode);

    VectorXd get_y(VectorXd p);

    VectorXd eval(VectorXd p);      //pour chaque x a p
    VectorXd evalErr(VectorXd p);   //pour chaque x a p
    VectorXd eval_atX0(VectorXd p); //pour x=0 a p
    VectorXd eval(VectorXd x,VectorXd p); //pour x

    std::vector<double> eval_1D_p0(Box box, ColorMode mode);
    std::vector< std::vector<double> > eval_2D_p0p1(Box box, ColorMode mode);
    std::vector< std::vector< std::vector<double> > > eval_3D_p0p1p2(Box box, ColorMode mode);

    static QColor getColor(double value, ScaleColorMode mode);
    static QColor getColor(double val, ScaleColorMode mode,double gamma,double min,double max);
    static QImage toImage(const std::vector< std::vector<double> > & data, ScaleColorMode mode, double gamma);
    static std::vector<std::pair<Vector3d,QColor>> toCloud(const std::vector<std::vector< std::vector<double> > > & data, ScaleColorMode mode,double gamma,double cut,double scale);
    static void searchMinMax(const std::vector< std::vector<double> > & data,double & min,double & max);
    static void searchMinMax(const std::vector<std::vector<std::vector<double> >> &data, double &min, double &max);

    const SystemData & getSystemData(){return data;}
    const SystemData & getSystemModel(){return model;}
    VectorXd serialize(const std::vector<Eigen::VectorXd> &v);

    VectorXd p0;


    void setSolveMode(SolveMode mode){this->solve_mode=mode;}
    SolveMode getSolveMode(){return solve_mode;}

    ParamHandler * getParamHandler(){return handler;}

    Results results;

    bool selectId1(int id)
    {
        if(id<p0.rows())
        {
            results.id1=id;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool selectId2(int id)
    {
        if(id<p0.rows())
        {
            results.id2=id;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool selectId3(int id)
    {
        if(id<p0.rows())
        {
            results.id3=id;
            return true;
        }
        else
        {
            return false;
        }
    }

signals:
    void progress(int value);

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

    SystemData data,model;
    VectorXd y_serialized;

    //Parser & Helper
    ParamHandler * handler;
    exprtk::parser<double> parser;
    std::vector<QByteArray> expr_str;
    std::vector<exprtk::expression<double>> expr;
    exprtk::symbol_table<double> symbol_table;

    int id_active;

    //Variables
    double X[9];
    double P[9];
};

class SystemFunctor:public LMFunctor<double>
{
public:
    SystemFunctor(System * system_ptr,std::vector<VectorXd> * p_list)
    {
        this->p_list=p_list;

        setSystem(system_ptr);
        p_list->clear();
    }

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

        p_list->push_back(p);

        return 0;
    }

    std::vector<VectorXd> * p_list;

private:
    System * sys;
    VectorXd y_serialized;
};


#endif
