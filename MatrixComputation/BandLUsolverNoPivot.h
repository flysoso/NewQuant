#ifndef BAND_LU_SOLVER_NOPIVOT_H
#define BAND_LU_SOLVER_NOPIVOT_H

#include "BandLUsolver.h"
#include "LowerBandMatrix.h"
#include "UpperBandMatrix.h"

namespace NewQuant
{
    template<typename TYPE>
    class BandLUsolverNoPivot : public BandLUsolver < TYPE >
    {
    private:
        LowerBandMatrix<TYPE> lm;
        UpperBandMatrix<TYPE> um;
        BandLUcombine_LbUb<TYPE> combine;

        void BandLUdecomposion();
    public:
        BandLUsolverNoPivot(const BaseMatrix<TYPE> &gm, const TYPE &e);

        ~BandLUsolverNoPivot() {}

        void Solve(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;

        const LowerBandMatrix<TYPE> & Lower() const
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

#include "BandLUsolverNoPivot.cpp"

#endif //BAND_LU_SOLVER_NOPIVOT_H
