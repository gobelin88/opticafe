#include <Eigen/Dense>
#include <unsupported/Eigen/NumericalDiff>
using Eigen::VectorXd;
using Eigen::MatrixXd;

#ifndef LMFUNCTOR_H
#define LMFUNCTOR_H

// Generic functor
template<typename _Scalar, int NX = Eigen::Dynamic, int NY = Eigen::Dynamic>
class LMFunctor
{
public:
typedef _Scalar Scalar;
enum {
    InputsAtCompileTime = NX,
    ValuesAtCompileTime = NY
};
typedef Eigen::Matrix<Scalar,InputsAtCompileTime,1> InputType;
typedef Eigen::Matrix<Scalar,ValuesAtCompileTime,1> ValueType;
typedef Eigen::Matrix<Scalar,ValuesAtCompileTime,InputsAtCompileTime> JacobianType;

int m_inputs, m_values;

LMFunctor() : m_inputs(InputsAtCompileTime), m_values(ValuesAtCompileTime) {}
LMFunctor(int inputs, int values) : m_inputs(inputs), m_values(values) {}

int inputs() const { return m_inputs; }
int values() const { return m_values; }

};

#endif // LMFUNCTOR_H
