#include <vector>
#include "parser/parser.h"
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

#ifndef SYSTEM_H
#define SYSTEM_H

struct SystemData
{
   std::vector< VectorXd > x,y;
};

static float color_tab[40][3]={
    {1,0,0},//0
    {0,1,0},//1
    {0,0,1},//2
    {1,1,0},//3
    {1,0,1},//4
    {0,1,1},//5
    {1,0.5,0},//6
    {0.5,1,0},//7
    {1,0,0.5},//8
    {0.5,0,1},//9
    {0,0.5,1},//10
    {0,1,0.5},//11
    {1,0.5,0.5},//12
    {.5,1,0.5},//13
    {.5,0.5,1},//14
    {.5,0,0},//15
    {0,.5,0},//16
    {0,0,.5},//17
    {.5,.5,.5},//18
    {1,1,1},//19
    {1,0,0},//20
    {0,1,0},//21
    {0,0,1},//22
    {1,1,0},//23
    {1,0,1},//24
    {0,1,1},//25
    {1,0.5,0},//26
    {0.5,1,0},//27
    {1,0,0.5},//28
    {0.5,0,1},//29
    {0,0.5,1},//30
    {0,1,0.5},//31
    {1,0.5,0.5},//32
    {.5,1,0.5},//33
    {.5,0.5,1},//34
    {.5,0,0},//35
    {0,.5,0},//36
    {0,0,.5},//37
    {.5,.5,.5},//38
    {1,1,1}//39
};


#define NBColorMode 2
static char * ColorMode_str[NBColorMode]={
    "MODE_ARG",
    "MODE_IT"
};

enum ColorMode
{
    MODE_ARG,
    MODE_IT
};


#define NBScaleColorMode 2
static char * ScaleColorMode_str[NBScaleColorMode]={
    "MODE_BLUE_GRADIENT",
    "MODE_PERIODIC"
};

enum ScaleColorMode
{
    MODE_BLUE_GRADIENT,
    MODE_PERIODIC
};

#define NBSolveMode 3
static char * SolveMode_str[NBSolveMode]={
    "LEVMAR",
    "DOGLEG",
    "NEWTON"
};

enum SolveMode
{
    MODE_LEVMAR,
    MODE_DOGLEG,
    MODE_NEWTON
};

class System:  public QTabWidget
{
    Q_OBJECT
public:
    System(Parser * parser,int nb_p,int nb_x,int nb_y);
    System(Parser * parser,QString script);

    void load_system(QString script);
    void load_p_init(QString script);
    void load_data(QString filename);
    void solve();
    void solve_Levmar();
    void solve_Dogleg();
    void solve_Newton();

    std::vector< std::vector<int> > solve_2D_p0p1(double p0_min, double p0_max,
                                                  double p1_min, double p1_max,
                                                  int width, int height, ColorMode mode);

    VectorXd get_y(VectorXd p);

    void eval();
    VectorXd eval(VectorXd x,VectorXd p);



    void clearPlots();
    void plot();

    static QImage toImage(const std::vector< std::vector<int> > & data, ScaleColorMode mode);
    static void searchMinMax(const std::vector< std::vector<int> > & data,int & min,int & max);

    void setProgressBar(QProgressBar * bar)
    {
        this->progress_bar=bar;
    }

    const SystemData & getSystemData(){return data;}
    const SystemData & getSystemModel(){return model;}
    VectorXd serialize(std::vector<VectorXd> v);

    VectorXd p0,p_hat,cov_hat,cor_hat;

    void setSolveMode(SolveMode mode){this->solve_mode=mode;}
    SolveMode getSolveMode(){return solve_mode;}

private:
    //static void levmar_func(double *p, double *hx, int m, int n, void *adata);

    int getNB(char c,QString script);
    QVector<double> extract(std::vector<VectorXd> v, int id);
    QByteArray getCharName(char var,int var_id);

    double getRMS(int id);

    int nb_p,nb_x,nb_y;
    std::vector<QByteArray> eq_list;
    Parser * ptr_parser;

    SystemData data,model;
    VectorXd y_serialized;
    std::vector<QCustomPlot*> plots;

    unsigned int it,it_performed;

    QProgressBar * progress_bar;

    SolveMode solve_mode;
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
        sys->p_hat=p;

        fvec=sys->get_y(p)-this->y_serialized;

        return 0;
    }

private:
    System * sys;
    VectorXd y_serialized;
};


#endif
