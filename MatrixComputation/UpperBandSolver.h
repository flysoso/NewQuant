#ifndef SUPPER_BAND_SOLVER_H
#define SUPPER_BAND_SOLVER_H

#include "SimpleSolver.h"

namespace NewQuant
{
    template <typename TYPE>
    class UpperBandSolver : public SimpleSolver < TYPE >
    {
    public:
        UpperBandSolver(const BaseMatrix<TYPE> &gm, const TYPE &e) : SimpleSolver<TYPE>(gm, e)
        {
            SimpleSolver<TYPE>::TestSingular();
        }

        void Solve(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;

        LogAndSign<TYPE> LogDeterminant() const;
    };
}
#include "UpperBandSolver.cpp"

#endif //SUPPER_BAND_SOLVER_H


