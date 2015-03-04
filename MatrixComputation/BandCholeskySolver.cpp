#ifndef BAND_CHOLESKY_SOLVER_CPP
#define BAND_CHOLESKY_SOLVER_CPP

#include "BandCholeskySolver.h"
#include "ConstGetSubMatrix.h"
#include "NPDException.h"

namespace NewQuant
{
    template<typename TYPE>
    void BandCholeskySolver<TYPE>::BandCholeskyDecomposition(const BaseMatrix<TYPE> &bm)
    {
        assert(bm.Nrows() == bm.Ncols());
        assert(bm.BandWidth().Lower() == bm.BandWidth().Upper());

        int n = lm.Nrows();
        int bw = lm.BandWidth().Lower();
        const TYPE &e = SimpleSolver<TYPE>::epsilon;
        TYPE temp;
        for (int i = 1; i <= n; ++i)
        {
            if (i == 1)
            {
                temp = bm(i, i);
            }
            else
            {
                temp = bm(i, i) - (c_sub(lm, i, i, 1, i - 1) * t(c_sub(lm, i, i, 1, i - 1)))(1, 1);
            }
            if (temp <= e)
            {
                LinearEquationSolver<TYPE>::fail = true;
                return;
            }
            else
            {
                lm(i, i) = sqrt(temp);
                for (int j = i + 1; j <= std::min(n, i + bw); ++j)
                {
                    if (i == 1)
                    {
                        lm(j, i) = bm(j, i) / lm(i, i);
                    }
                    else
                    {
                        lm(j, i) = (bm(j, i) - (c_sub(lm, i, i, 1, i - 1) * t(c_sub(lm, j, j, 1, i - 1)))(1, 1)) / lm(i, i);
                    }
                }
            }
        }
    }

    template<typename TYPE>
    void BandCholeskySolver<TYPE>::Solve(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const
    {
        if (LinearEquationSolver<TYPE>::fail)
        {
            Singleton<Tracer>::Instance()->AddMessage("BandCholeskySolver::Solve");
            throw NPDException(SimpleSolver<TYPE>::mat);
        }
        Matrix<TYPE> temp(out.Nrows(), out.Ncols());
        lm.Solve(in, temp);
        t(lm).Solve(temp, out);
    }

    template<typename TYPE>
    LogAndSign<TYPE> BandCholeskySolver<TYPE>::LogDeterminant() const
    {
        if (LinearEquationSolver<TYPE>::fail)
        {
            Singleton<Tracer>::Instance()->AddMessage("BandCholeskySolver::LogDeterminant");
            throw NPDException(SimpleSolver<TYPE>::mat);
        }
        LogAndSign<TYPE> ld;
        int n = lm.Nrows();
        for (int i = 1; i <= n; ++i)
        {
            ld *= lm(i, i);
        }
        ld.PowEq(2);
        return ld;
    }
}
#endif //BAND_CHOLESKY_SOLVER_CPP
