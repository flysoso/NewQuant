#ifndef CONSTANT_SOLVER_H
#define CONSTANT_SOLVER_H

#include "SimpleSolver.h"

template <typename TYPE>
class ConstantSolver : public SimpleSolver < TYPE >
{
public:
    ConstantSolver(const BaseMatrix<TYPE> &bm, const TYPE &e) : SimpleSolver<TYPE>(bm, e)
    {
        if (bm.Nrows() > 1)
        {
            LinearEquationSolver<TYPE>::fail = true;
        }
        else if (fabs(bm(1, 1)) <= e)
        {
            LinearEquationSolver<TYPE>::fail = true;
        }
    }

    void Solve(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;

    LogAndSign<TYPE> LogDeterminant() const;
};

#include "ConstantSolver.cpp"

#endif //CONSTANT_SOLVER_H


