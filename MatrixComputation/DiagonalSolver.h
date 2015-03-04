#ifndef DIAGONAL_SOLVER_H
#define DIAGONAL_SOLVER_H

#include "SimpleSolver.h"

namespace NewQuant
{
    template <typename TYPE>
    class DiagonalSolver : public SimpleSolver < TYPE >
    {
    public:
        DiagonalSolver(const BaseMatrix<TYPE> &bm, const TYPE &e) : SimpleSolver<TYPE>(bm, e)
        {
            SimpleSolver<TYPE>::TestSingular();
        }

        void Solve(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;

        LogAndSign<TYPE> LogDeterminant() const;
    };
}
#include "DiagonalSolver.cpp"

#endif //DIAGONAL_SOLVER_H


