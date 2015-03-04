#ifndef LU_SOLVER_NOPIVOT_H
#define LU_SOLVER_NOPIVOT_H

#include "LUsolver.h"

namespace NewQuant
{
    template <typename TYPE>
    class LUsolverNoPivot : public LUsolver < TYPE >
    {
    private:
        void LUdecomposion();
    public:
        LUsolverNoPivot(const BaseMatrix<TYPE> &, const TYPE &);

        ~LUsolverNoPivot() {}

        void Solve(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;

        LogAndSign<TYPE> LogDeterminant() const;
    };
}
#include "LUsolverNoPivot.cpp"

#endif //LU_SOLVER_NOPIVOT_H
