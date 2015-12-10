#ifndef PARAMETERS
#define PARAMETERS

#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QGroupBox>
#include <QTabWidget>

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


#define NBColorMode 3
static char * ColorMode_str[NBColorMode]=
{
    "Argument - atan2(y0,y1)",
    "Module - |y0+y1+...+yn|",
    "Algorithm iterations",
};

enum ColorMode
{
    MODE_ARG,
    MODE_MODULE,
    MODE_IT,
};


#define NBScaleColorMode 3
static char * ScaleColorMode_str[NBScaleColorMode]={
    "Blue Gradient",
    "Periodic",
    "Rainbow"
};

enum ScaleColorMode
{
    MODE_BLUE_GRADIENT,
    MODE_PERIODIC,
    MODE_RAINBOW
};

#define NBSolveMode 3
static char * SolveMode_str[NBSolveMode]={
    "Levenberg-Marquardt",
    "Dogleg",
    "Gauss-Newton"
};

enum SolveMode
{
    MODE_LEVMAR,
    MODE_DOGLEG,
    MODE_GAUSS_NEWTON
};

class ParamHandler:public QWidget
{
public:
    ParamHandler()
    {
        sb_levmar_lambda=new QDoubleSpinBox();sb_levmar_lambda->setValue(1.0);
        sb_levmar_lambda->setDecimals(10);
        sb_levmar_lambda->setSingleStep(0.01);
        sb_dogleg_lambda=new QDoubleSpinBox();sb_dogleg_lambda->setValue(1.0);
        sb_dogleg_lambda->setDecimals(10);
        sb_dogleg_lambda->setSingleStep(0.01);
        sb_newton_lambda=new QDoubleSpinBox();sb_newton_lambda->setValue(1.0);
        sb_newton_lambda->setDecimals(10);
        sb_newton_lambda->setSingleStep(0.01);

        sb_it_max=new QSpinBox();
        sb_it_max->setToolTip("Maximmum number of iterations");
        sb_it_max->setPrefix("it_max=");
        sb_it_max->setRange(0,10000);
        sb_dp_min=new QDoubleSpinBox();
        sb_dp_min->setToolTip("Minimum delta for the state");
        sb_dp_min->setPrefix("|dp|_min=");
        sb_dp_min->setRange(-1000,1000);
        sb_df_min=new QDoubleSpinBox();
        sb_df_min->setToolTip("Minimum delta for the function");
        sb_df_min->setPrefix("|df|_min=");
        sb_df_min->setRange(-1000,1000);
        sb_delta=new QDoubleSpinBox();
        sb_delta->setToolTip("Delta for finite differences");
        sb_delta->setPrefix("delta=");
        sb_delta->setRange(-1000,1000);

        sb_dp_min->setDecimals(10);
        sb_df_min->setDecimals(10);
        sb_delta->setDecimals(10);

        QVBoxLayout * vlayout=new QVBoxLayout(this);
        QGridLayout * glayout=new QGridLayout();
        glayout->addWidget(sb_it_max,0,0);
        glayout->addWidget(sb_dp_min,0,1);
        glayout->addWidget(sb_df_min,0,2);
        glayout->addWidget(sb_delta,1,0);

        QGroupBox * gb_commons_params=new QGroupBox("Commons parameters");
        gb_commons_params->setLayout(glayout);
        QGroupBox * gb_specifics_params=new QGroupBox("Specifics parameters");
        tab_specifics=new QTabWidget();
        QVBoxLayout * vlayout2=new QVBoxLayout();
        vlayout2->addWidget(tab_specifics);
        gb_specifics_params->setLayout(vlayout2);

        vlayout->addWidget(gb_commons_params);
        vlayout->addWidget(gb_specifics_params);

        reset();

        for(int i=0;i<NBSolveMode;i++)
        {
            gb_specifics[i]=new QWidget(this);
            QGridLayout * new_grid=new QGridLayout(gb_specifics[i]);
            if(i==0)
            {
                new_grid->addWidget(sb_levmar_lambda,0,0);
            }
            if(i==1)
            {
                new_grid->addWidget(sb_dogleg_lambda,0,0);
            }
            if(i==2)
            {
                new_grid->addWidget(sb_newton_lambda,0,0);
            }

            tab_specifics->addTab(gb_specifics[i],SolveMode_str[i]);
        }
    }

    void reset()
    {
      sb_it_max->setValue(100);
      sb_dp_min->setValue(1e-9);
      sb_df_min->setValue(1e-9);
      sb_delta->setValue(1e-8);
    }

    QSpinBox * sb_it_max;
    QDoubleSpinBox * sb_dp_min;
    QDoubleSpinBox * sb_df_min;
    QDoubleSpinBox * sb_delta;

    QTabWidget * tab_specifics;

    //Specifics
    QDoubleSpinBox * sb_levmar_lambda;
    QDoubleSpinBox * sb_dogleg_lambda;
    QDoubleSpinBox * sb_newton_lambda;

    QWidget * gb_specifics[NBSolveMode];
};


#endif // PARAMETERS

