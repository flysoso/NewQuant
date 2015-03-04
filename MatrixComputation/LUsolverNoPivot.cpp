#ifndef LU_SOLVER_NOPIVOT_CPP
#define LU_SOLVER_NOPIVOT_CPP

#include "LUsolverNoPivot.h"
#include "GetSubMatrix.h"
#include "../ExceptionClass/LogicError.h"

namespace NewQuant
{
    template <typename TYPE>
    LUsolverNoPivot<TYPE>::LUsolverNoPivot(const BaseMatrix<TYPE> &gm, const TYPE &e) : LUsolver<TYPE>(gm, e)
    {
        LUdecomposion();
    }

    template <typename TYPE>
    void LUsolverNoPivot<TYPE>::LUdecomposion()
    {
        LUcombine<TYPE> &m = LUsolver<TYPE>::combine;
        const TYPE &e = LUsolver<TYPE>::epsilon;
        TYPE t;
        int n = m.Dim();
        for (int i = 1; i <= n - 1; ++i)
        {
            if (fabs(m(i, i)) <= e)
            {
                LinearEquationSolver<TYPE>::fail = true;
                return;
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
    void LUsolverNoPivot<TYPE>::Solve(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const
    {
        assert(in.Nrows() == combine.Ncols());
        assert(in.Nrows() == out.Nrows() && in.Ncols() == out.Ncols());
        if (LinearEquationSolver<TYPE>::IsFailed())
        {
            Singleton<Tracer>::Instance()->AddMessage("LUsolverNoPivot::Solve");
            throw LogicError("LUsolverNoPivot: LU decomposition is failed");
        }
        Matrix<TYPE> t(in.Nrows(), in.Ncols());
        LUsolver<TYPE>::lm.Solve(in, t);
        LUsolver<TYPE>::um.Solve(t, out);
    }

    template <typename TYPE>
    LogAndSign<TYPE> LUsolverNoPivot<TYPE>::LogDeterminant() const
    {
        if (LinearEquationSolver<TYPE>::IsFailed())
        {
            Singleton<Tracer>::Instance()->AddMessage("LUsolverNoPivot::LogDeterminant");
            throw LogicError("LUsolverNoPivot: LU decomposition is failed");
        }
        LogAndSign<TYPE> ld;
        const LUcombine<TYPE> &m = LUsolver<TYPE>::combine;
        for (int i = 1; i <= m.Dim(); ++i)
        {
            ld *= m(i, i);
        }
        return ld;
    }
}
#endif //LU_SOLVER_NOPIVOT_CPP
