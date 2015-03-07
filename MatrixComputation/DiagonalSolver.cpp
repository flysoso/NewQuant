#ifndef DIAGONAL_SOLVER_CPP
#define DIAGONAL_SOLVER_CPP

#include "DiagonalSolver.h"

#include "SingularException.h"

namespace NewQuant
{
    template<typename TYPE>
    void DiagonalSolver<TYPE>::Solve(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const
    {
        if (LinearEquationSolver<TYPE>::IsFailed())
        {
            Singleton<Tracer>::Instance()->AddMessage("DiagonalSolver::Solve");
            throw SingularException(SimpleSolver<TYPE>::mat);
        }

        int n = SimpleSolver<TYPE>::mat.Nrows();

        assert(n == in.Nrows());
        assert(in.Ncols() == out.Ncols() && in.Nrows() == out.Nrows());

        int c = in.Ncols();
        const BaseMatrix<TYPE> &m = SimpleSolver<TYPE>::mat;
        for (int i = 1; i <= c; ++i)
        {
            for (int j = n; j >= 1; --j)
            {
                out(j, i) = in(j, i) / m(j, j);
            }
        }
    }


    template<typename TYPE>
    LogAndSign<TYPE> DiagonalSolver<TYPE>::LogDeterminant() const
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
}
#endif //DIAGONAL_SOLVER_CPP
