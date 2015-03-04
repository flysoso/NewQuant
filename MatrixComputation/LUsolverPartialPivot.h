#ifndef LU_SOLVER_PARTIALPIVOT_H
#define LU_SOLVER_PARTIALPIVOT_H


#include "LUsolver.h"
namespace NewQuant
{
    template <typename TYPE> class LUsolver;
    template <typename TYPE> class LUcombine;

    template <typename TYPE>
    class LUsolverPartialPivot : public LUsolver < TYPE >
    {
    private:
        void LUdecomposion();
    public:
        LUsolverPartialPivot(const BaseMatrix<TYPE> &, const TYPE &);

        ~LUsolverPartialPivot() {}

        void Solve(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;

        LogAndSign<TYPE> LogDeterminant() const;
    };
}
#include "LUsolverPartialPivot.cpp"

#endif //LU_SOLVER_PARTIALPIVOT_H
