﻿#include <vector>

#include <Eigen/Dense>
using Eigen::VectorXd;
using Eigen::MatrixXd;

#ifndef NEWTONSOLVER_H
#define NEWTONSOLVER_H

template<typename FunctorType>
class NewtonSolver
{
public:
    NewtonSolver(FunctorType & _functor):functor(_functor)
    {
        nfev = njev = iter = 0;
        fnorm = gnorm = 0.;
    }

    struct Parameters {
        Parameters()
            : factor(1.0)
            , maxfev(100)
            , ftol(std::sqrt(Eigen::NumTraits<double>::epsilon()))
            , ptol(std::sqrt(Eigen::NumTraits<double>::epsilon()))
            , gtol(1e-10)
            , epsfcn(0.0) {}
        double factor;
        unsigned int maxfev;   // maximum number of function evaluation
        double ftol;
        double ptol;
        double gtol;
        double epsfcn;
    };

    void minimize(VectorXd  & p)
    {
        bool stop_crit=false;

        minimizeInit(p);
        do
        {
            stop_crit = minimizeOneStep(p);
        }
        while (!stop_crit);
    }

    bool minimizeOneStep(VectorXd & p)
    {
        functor.df(p,fjac);
        functor(p, fvec);
        //dp=-J.inverse()*fvec;//1
        dp=parameters.factor*fjac.colPivHouseholderQr().solve(-fvec);//2
        //MatrixXd jjt=(J.transpose()*J).inverse();dp=-jjt*J.transpose()*fvec;//3


        iter+=1;

        p+=dp;
        return( (dp.norm()<parameters.gtol) || (iter>parameters.maxfev) || (fvec.norm()<parameters.ftol) );
    }

    void minimizeInit(VectorXd  &p)
    {
        iter=0;
        fjac.resize(functor.values(),functor.inputs());
        fvec.resize(functor.values());
    }

    Parameters parameters;
    unsigned int nfev;
    unsigned int njev;
    unsigned int iter;
    double fnorm, gnorm;
    MatrixXd fjac;

private:

    FunctorType & functor;

    VectorXd dp;
    VectorXd fvec;


};

#endif // NEWTONSOLVER_H
