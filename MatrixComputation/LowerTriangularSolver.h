#ifndef LOWER_TRIANGULAR_SOLVER_H
#define LOWER_TRIANGULAR_SOLVER_H

#include "SimpleSolver.h"

template <typename TYPE>
class LowerTriangularSolver : public SimpleSolver < TYPE >
{
public:
    LowerTriangularSolver(const BaseMatrix<TYPE> &gm, const TYPE &e) : SimpleSolver<TYPE>(gm, e)
    {
        SimpleSolver<TYPE>::TestSingular();
    }

    void Solve(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;

    LogAndSign<TYPE> LogDeterminant() const;
};

#include "LowerTriangularSolver.cpp"

#endif //LOWER_TRIANGULAR_SOLVER_H

