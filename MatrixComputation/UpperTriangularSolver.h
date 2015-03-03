#ifndef UPPER_TRIANGULAR_SOLVER_H
#define UPPER_TRIANGULAR_SOLVER_H

#include "SimpleSolver.h"

template <typename TYPE>
class UpperTriangularSolver : public SimpleSolver < TYPE >
{
public:
    UpperTriangularSolver(const BaseMatrix<TYPE> &gm, const TYPE &e) : SimpleSolver<TYPE>(gm, e)
    {
        SimpleSolver<TYPE>::TestSingular();
    }

    void Solve(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;

    LogAndSign<TYPE> LogDeterminant() const;
};

#include "UpperTriangularSolver.cpp"

#endif //UPPER_TRIANGULAR_SOLVER_H


