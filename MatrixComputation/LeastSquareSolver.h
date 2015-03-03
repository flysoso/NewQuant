#ifndef LEAST_SQUARE_SOLVER_H
#define LEAST_SQUARE_SOLVER_H

#include <assert.h>
template<typename TYPE> class BaseMatrix;

template<typename TYPE>
class LeastSquareSolver
{
protected:
    bool fail;
    LeastSquareSolver() :fail(false){}
public:
    ~LeastSquareSolver(){}

    bool IsFailed() const
    {
        return fail;
    }

    virtual void SolveLS(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const = 0;
};





#endif //LEAST_SQUARE_SOLVER_H
