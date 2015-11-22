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
            : factor(100.0)
            , maxfev(400)
            , ftol(Eigen::internal::sqrt(Eigen::NumTraits<double>::epsilon()))
            , ptol(Eigen::internal::sqrt(Eigen::NumTraits<double>::epsilon()))
            , gtol(0.0)
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
        minimizeInit(p);

        bool stop_crit=false;
        do
        {
            stop_crit = minimizeOneStep(p);
        }
        while (!stop_crit);
    }

    bool minimizeOneStep(VectorXd & p)
    {
        functor.df(p,J);
        functor(p, fvec);
        //dp=J.colPivHouseholderQr().solve(-fvec);
        dp=-J.inverse()*fvec;
        iter+=1;

        p+=dp;

        return( (dp.norm()<1e-3) );
    }

    void minimizeInit(VectorXd  &p)
    {
        iter=0;
        J.resize(functor.values(),functor.inputs());
        fvec.resize(functor.values());
    }

    Parameters parameters;
    unsigned int nfev;
    unsigned int njev;
    unsigned int iter;
    double fnorm, gnorm;

private:

    FunctorType & functor;

    MatrixXd J;
    VectorXd dp;
    VectorXd fvec;   
};

#endif // NEWTONSOLVER_H
