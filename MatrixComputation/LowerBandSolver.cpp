#ifndef LOWER_BAND_SOLVER_CPP
#define LOWER_BAND_SOLVER_CPP

#include "LowerBandSolver.h"

#include "SingularException.h"

template <typename TYPE>
void LowerBandSolver<TYPE>::Solve(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const
{
    if (LinearEquationSolver<TYPE>::IsFailed())
    {
        Singleton<Tracer>::Instance()->AddMessage("LowerBandSolver::Solve");
        throw SingularException(SimpleSolver<TYPE>::mat);
    }

    int n = SimpleSolver<TYPE>::mat.Ncols();
    int lbw = SimpleSolver<TYPE>::mat.BandWidth().Lower();

    assert(n == in.Nrows());
    assert(in.Ncols() == out.Ncols() && in.Nrows() == out.Nrows());

    TYPE t;
    static const TYPE zero(0);
    int c = in.Ncols();
    const BaseMatrix<TYPE> &m = SimpleSolver<TYPE>::mat;
    for (int i = 1; i <= c; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            t = zero;
            for (int k = std::max(1, i - lbw); k <= j - 1; ++k)
            {
                t += out(k, i)* m(j, k);
            }
            out(j, i) = (in(j, i) - t) / m(j, j);
        }
    }

}


template<typename TYPE>
LogAndSign<TYPE> LowerBandSolver<TYPE>::LogDeterminant() const
{
    if (LinearEquationSolver<TYPE>::IsFailed())
    {
        static const TYPE zero(0);
        LogAndSign<TYPE> ld(zero);
        return ld;
    }
    const BaseMatrix<TYPE> &m = SimpleSolver<TYPE>::mat;
    LogAndSign<TYPE> ld;
    int n = m.Nrows();
    for (int i = 1; i <= n; ++i)
    {
        ld *= m(i, i);
    }
    return ld;
}

#endif //LOWER_BAND_SOLVER_CPP
