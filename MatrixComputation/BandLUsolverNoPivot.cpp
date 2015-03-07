#ifndef BAND_LU_SOLVER_NOPIVOT_CPP
#define BAND_LU_SOLVER_NOPIVOT_CPP

#include "BandLUsolverNoPivot.h"
#include "GetSubMatrix.h"

#include "../ExceptionClass/LogicError.h"

namespace NewQuant
{
    template<typename TYPE>
    BandLUsolverNoPivot<TYPE>::BandLUsolverNoPivot(const BaseMatrix<TYPE> &bm, const TYPE &e) :
        BandLUsolver<TYPE>(bm, e),
        lm(bm.Nrows(), bm.BandWidth().Lower()),
        um(bm.Nrows(), bm.BandWidth().Upper()),
        combine(lm, um)
    {
        lm << bm;
        um << bm;
        static const TYPE one(1);
        for (int i = 1; i <= bm.Nrows(); ++i)
        {
            lm(i, i) = one;
        }
        BandLUdecomposion();
    }

    template<typename TYPE>
    void BandLUsolverNoPivot<TYPE>::BandLUdecomposion()
    {
        BandLUcombine_LbUb<TYPE> &m = combine;
        const TYPE &e = BandLUsolver<TYPE>::epsilon;
        TYPE t;
        int n = m.Dim(), end;
        int lw = BandLUsolver<TYPE>::lbw;
        int uw = BandLUsolver<TYPE>::ubw;

        for (int i = 1; i <= n - 1; ++i)
        {
            if (fabs(m(i, i)) < e)
            {
                LinearEquationSolver<TYPE>::fail = true;
                return;
            }
            end = std::min(n, i + uw);
            for (int j = i + 1; j <= std::min(n, i + lw); ++j)
            {
                t = -m(j, i) / m(i, i);
                sub(m, j, j, i, end) += t * sub(m, i, i, i, end);
                m(j, i) = -t;
            }
        }
    }

    template<typename TYPE>
    void BandLUsolverNoPivot<TYPE>::Solve(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const
    {
        assert(in.Nrows() == combine.Ncols());
        assert(in.Nrows() == out.Nrows() && in.Ncols() == out.Ncols());
        if (LinearEquationSolver<TYPE>::IsFailed())
        {
            Singleton<Tracer>::Instance()->AddMessage("BandLUsolverNoPivot::Solve");
            throw LogicError("BandLUsolverNoPivot: LU decomposition is failed");
        }
        Matrix<TYPE> t(in.Nrows(), in.Ncols());
        lm.Solve(in, t);
        um.Solve(t, out);
    }

    template<typename TYPE>
    LogAndSign<TYPE> BandLUsolverNoPivot<TYPE>::LogDeterminant() const
    {
        if (LinearEquationSolver<TYPE>::IsFailed())
        {
            Singleton<Tracer>::Instance()->AddMessage("BandLUsolverNoPivot::LogDeterminant");
            throw LogicError("BandLUsolverNoPivot: LU decomposition is failed");
        }
        LogAndSign<TYPE> ld;
        const BandLUcombine_LbUb<TYPE> &m = combine;
        for (int i = 1; i <= m.Dim(); ++i)
        {
            ld *= m(i, i);
        }
        return ld;
    }
}
#endif //BAND_LU_SOLVER_NOPIVOT_CPP
