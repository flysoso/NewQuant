#ifndef LU_SOLVER_COMPLETEPIVOT_H
#define LU_SOLVER_COMPLETEPIVOT_H


#include "LUsolver.h"

namespace NewQuant
{
    template<typename TYPE>
    class LUsolverCompletePivot : public LUsolver < TYPE >
    {
    private:
        void LUdecomposion();
    public:
        LUsolverCompletePivot(const BaseMatrix<TYPE> &, const TYPE &);

        ~LUsolverCompletePivot() {}

        void Solve(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;

        LogAndSign<TYPE> LogDeterminant() const;
    };
}
#include "LUsolverCompletePivot.cpp"

#endif //LU_SOLVER_COMPLETEPIVOT_H
