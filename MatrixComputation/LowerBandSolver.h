#ifndef LOWER_BAND_SOLVER_H
#define LOWER_BAND_SOLVER_H

#include "SimpleSolver.h"

namespace NewQuant
{
    template<typename TYPE>
    class LowerBandSolver : public SimpleSolver < TYPE >
    {
    public:
        LowerBandSolver(const BaseMatrix<TYPE> &gm, const TYPE &e) : SimpleSolver<TYPE>(gm, e)
        {
            SimpleSolver<TYPE>::TestSingular();
        }

        void Solve(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;

        LogAndSign<TYPE> LogDeterminant() const;
    };
}
#include "LowerBandSolver.cpp"

#endif //LOWER_BAND_SOLVER_H

