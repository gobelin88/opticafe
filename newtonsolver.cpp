#include "newtonsolver.h"

NewtonSolver::NewtonSolver(FunctorType & _functor):functor(_functor)
{
    nfev = njev = iter = 0;
    fnorm = gnorm = 0.;
}

