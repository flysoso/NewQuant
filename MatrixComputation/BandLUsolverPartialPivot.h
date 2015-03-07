#ifndef BAND_LU_SOLVER_PARTIALPIVOT_H
#define BAND_LU_SOLVER_PARTIALPIVOT_H

#include "BandLUsolver.h"
#include "LowerTriangularMatrix.h"
#include "UpperBandMatrix.h"

namespace NewQuant
{
    template<typename TYPE> class BandLUcombine_LtUb;
    template<typename TYPE> class BandLUsolver;

    template<typename TYPE>
    class BandLUsolverPartialPivot : public BandLUsolver < TYPE >
    {
    private:
        LowerTriangularMatrix<TYPE> lm;
        UpperBandMatrix<TYPE> um;
        BandLUcombine_LtUb<TYPE> combine;

        void BandLUdecomposion();

    public:
        BandLUsolverPartialPivot(const BaseMatrix<TYPE> &gm, const TYPE &e);

        ~BandLUsolverPartialPivot() {}

        void Solve(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;

        const LowerTriangularMatrix<TYPE> & Lower() const
        {
            return lm;
        }

        const UpperBandMatrix<TYPE> & Upper() const
        {
            return um;
        }

        void GetLowerPart(GeneralMatrix<TYPE> &out) const
        {
            out << lm;
        }

        void GetUpperPart(GeneralMatrix<TYPE> &out) const
        {
            out << um;
        }

        LogAndSign<TYPE> LogDeterminant() const;
    };
}

#include "BandLUsolverPartialPivot.cpp"

#endif //BAND_LU_SOLVER_PARTIALPIVOT_H
