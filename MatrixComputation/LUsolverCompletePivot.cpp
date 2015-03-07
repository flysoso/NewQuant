#ifndef LU_SOLVER_COMPLETEPIVOT_CPP
#define LU_SOLVER_COMPLETEPIVOT_CPP

#include "LUsolverCompletePivot.h"
#include "GetSubMatrix.h"
#include "ConstPermutedMatrix.h"

#include "SingularException.h"

namespace NewQuant
{
    template<typename TYPE>
    LUsolverCompletePivot<TYPE>::LUsolverCompletePivot(const BaseMatrix<TYPE> &gm, const TYPE &e) : LUsolver<TYPE>(gm, e)
    {
        LUdecomposion();
    }

    template<typename TYPE>
    void LUsolverCompletePivot<TYPE>::LUdecomposion()
    {
        LUcombine<TYPE> &m = LUsolver<TYPE>::combine;
        PermuteMatrix<TYPE> &lp = LUsolver<TYPE>::left;
        PermuteMatrix<TYPE> &rp = LUsolver<TYPE>::right;
        TYPE e = LUsolver<TYPE>::epsilon;
        TYPE t, max;
        int n = m.Dim(), r, c;
        for (int i = 1; i <= n - 1; ++i)
        {
            FindAbsMax(sub(m, i, n, i, n), max, r, c);

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

            if (c + i - 1 != i) //col skip is i-1
            {
                m.SwapCol(c + i - 1, i);
                rp.SwapCol(c + i - 1, i);
            }

            for (int j = i + 1; j <= n; ++j)
            {
                t = -m(j, i) / m(i, i);
                sub(m, j, j, i, n) += t * sub(m, i, i, i, n);
                m(j, i) = -t;
            }
        }
    }

    template<typename TYPE>
    void LUsolverCompletePivot<TYPE>::Solve(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const
    {
        assert(in.Nrows() == combine.Ncols());
        assert(in.Nrows() == out.Nrows() && in.Ncols() == out.Ncols());
        if (LinearEquationSolver<TYPE>::IsFailed())
        {
            Singleton<Tracer>::Instance()->AddMessage("LUsolverCompletePivot::Solve");
            throw SingularException(LUsolver<TYPE>::mat);
        }
        const PermuteMatrix<TYPE> &lp = LUsolver<TYPE>::left;
        Matrix<TYPE> t1(in.Nrows(), in.Ncols()), t2(in.Nrows(), in.Ncols());
        LUsolver<TYPE>::lm.Solve(c_perm(lp, in), t1);
        LUsolver<TYPE>::um.Solve(t1, t2);
        LUsolver<TYPE>::right.Solve(t2, out);
    }


    template<typename TYPE>
    LogAndSign<TYPE> LUsolverCompletePivot<TYPE>::LogDeterminant() const
    {
        if (LinearEquationSolver<TYPE>::IsFailed())
        {
            static const TYPE zero(0);
            LogAndSign<TYPE> ld(zero);
            return ld;
        }
        LogAndSign<TYPE> ld;
        const LUcombine<TYPE> &m = LUsolver<TYPE>::combine;
        for (int i = 1; i <= m.Dim(); ++i)
        {
            ld *= m(i, i);
        }
        int n1 = LUsolver<TYPE>::left.SwapTimes();
        int n2 = LUsolver<TYPE>::right.SwapTimes();

        if (n1 % 2 == 1)
        {
            ld.ChangeSign();
        }

        if (n2 % 2 == 1)
        {
            ld.ChangeSign();
        }
        return ld;
    }
}
#endif //LU_SOLVER_COMPLETEPIVOT_CPP
