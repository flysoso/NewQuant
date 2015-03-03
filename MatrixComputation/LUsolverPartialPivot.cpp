#ifndef LU_SOLVER_PARTIALPIVOT_CPP
#define LU_SOLVER_PARTIALPIVOT_CPP

#include "LUsolverPartialPivot.h"
#include "GetSubMatrix.h"
#include "ConstPermutedMatrix.h"
#include "ScaledMatrix.h"

#include "SingularException.h"

template <typename TYPE>
LUsolverPartialPivot<TYPE>::LUsolverPartialPivot(const BaseMatrix<TYPE> &gm, const TYPE &e) : LUsolver<TYPE>(gm, e)
{
    LUdecomposion();
}

template <typename TYPE>
void LUsolverPartialPivot<TYPE>::LUdecomposion()
{
    LUcombine<TYPE> &m = LUsolver<TYPE>::combine;
    const TYPE &e = LUsolver<TYPE>::epsilon;
    PermuteMatrix<TYPE> &lp = LUsolver<TYPE>::left;
    TYPE t, max;
    int n = m.Dim(), r, c;
    for (int i = 1; i <= n - 1; ++i)
    {
        FindAbsMax(sub(m, i, n, i, i), max, r, c);

        if (fabs(max) <= e)
        {
            LinearEquationSolver<TYPE>::fail = true;
            return;
        }

        if (r + i - 1 != i) //row skip is i-1
        {
            m.SwapRow(r + i - 1, i);
            lp.SwapRow(r + i - 1, i);
        }

        for (int j = i + 1; j <= n; ++j)
        {
            t = -m(j, i) / m(i, i);
            sub(m, j, j, i, n) += t * sub(m, i, i, i, n);
            m(j, i) = -t;
        }
    }
}

template <typename TYPE>
void LUsolverPartialPivot<TYPE>::Solve(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const
{
    assert(in.Nrows() == LUsolver<TYPE>::combine.Ncols());
    assert(in.Nrows() == out.Nrows() && in.Ncols() == out.Ncols());
    if (LinearEquationSolver<TYPE>::IsFailed())
    {
        Singleton<Tracer>::Instance()->AddMessage("LUsolverPartialPivot::Solve");
        throw SingularException(LUsolver<TYPE>::mat);
    }
    const PermuteMatrix<TYPE> &lp = LUsolver<TYPE>::left;
    Matrix<TYPE> t(in.Nrows(), in.Ncols());
    LUsolver<TYPE>::lm.Solve(c_perm(lp, in), t);
    LUsolver<TYPE>::um.Solve(t, out);
}

template <typename TYPE>
LogAndSign<TYPE> LUsolverPartialPivot<TYPE>::LogDeterminant() const
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

    if (n1 % 2 == 1)
    {
        ld.ChangeSign();
    }
    return ld;
}


#endif //LU_SOLVER_PARTIALPIVOT_CPP
