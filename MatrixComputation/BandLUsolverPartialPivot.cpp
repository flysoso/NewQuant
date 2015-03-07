#ifndef BAND_LU_SOLVER_PARTIALPIVOT_CPP
#define BAND_LU_SOLVER_PARTIALPIVOT_CPP

#include "BandLUsolverPartialPivot.h"
#include "GetSubMatrix.h"
#include "ConstPermutedMatrix.h"
#include "ScaledMatrix.h"

#include "SingularException.h"

namespace NewQuant
{
    template<typename TYPE>
    BandLUsolverPartialPivot<TYPE>::BandLUsolverPartialPivot(const BaseMatrix<TYPE> &bm, const TYPE &e) :
        BandLUsolver<TYPE>(bm, bm.BandWidth().Lower(), std::min(bm.BandWidth().Lower() + bm.BandWidth().Upper(), bm.Nrows() - 1), e),
        lm(bm.Nrows()), um(bm.Nrows(), BandLUsolver<TYPE>::ubw),
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
    void BandLUsolverPartialPivot<TYPE>::BandLUdecomposion()
    {
        BandLUcombine_LtUb<TYPE> &m = combine;
        PermuteMatrix<TYPE> &lp = BandLUsolver<TYPE>::left;
        TYPE e = BandLUsolver<TYPE>::epsilon;
        TYPE t, max;
        int n = m.Dim(), r, c, end;
        int lw = BandLUsolver<TYPE>::lbw;
        int uw = BandLUsolver<TYPE>::ubw;

        for (int i = 1; i <= n - 1; ++i)
        {
            FindAbsMax(sub(m, i, std::min(n, i + lw), i, i), max, r, c);

            if (fabs(max) < e)
            {
                LinearEquationSolver<TYPE>::fail = true;
                return;
            }

            if (r + i - 1 != i) //row skip is i-1
            {
                m.SwapRow(r + i - 1, i);
                lp.SwapRow(r + i - 1, i);
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
    void BandLUsolverPartialPivot<TYPE>::Solve(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const
    {
        assert(in.Nrows() == combine.Ncols());
        assert(in.Nrows() == out.Nrows() && in.Ncols() == out.Ncols());
        if (LinearEquationSolver<TYPE>::IsFailed())
        {
            Singleton<Tracer>::Instance()->AddMessage("BandLUsolverPartialPivot::Solve");
            throw SingularException(BandLUsolver<TYPE>::mat);
        }
        const PermuteMatrix<TYPE> &lp = BandLUsolver<TYPE>::left;
        Matrix<TYPE> t(in.Nrows(), in.Ncols());
        lm.Solve(c_perm(lp, in), t);
        um.Solve(t, out);
    }

    template<typename TYPE>
    LogAndSign<TYPE> BandLUsolverPartialPivot<TYPE>::LogDeterminant() const
    {
        if (LinearEquationSolver<TYPE>::IsFailed())
        {
            static const TYPE zero(0);
            LogAndSign<TYPE> ld(zero);
            return ld;
        }
        LogAndSign<TYPE> ld;
        const BandLUcombine_LtUb<TYPE> &m = combine;
        for (int i = 1; i <= m.Dim(); ++i)
        {
            ld *= m(i, i);
        }

        int n1 = BandLUsolver<TYPE>::left.SwapTimes();

        if (n1 % 2 == 1)
            ld.ChangeSign();
        return ld;
    }
}

#endif //BAND_LU_SOLVER_PARTIALPIVOT_CPP
