#ifndef SUPPER_TRIANGULAR_SOLVER_CPP
#define SUPPER_TRIANGULAR_SOLVER_CPP

#include "UpperTriangularSolver.h"

#include "SingularException.h"

template <typename TYPE>
void UpperTriangularSolver<TYPE>::Solve(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const
{
    if (LinearEquationSolver<TYPE>::IsFailed())
    {
        Singleton<Tracer>::Instance()->AddMessage("UpperTriangularSolver::Solve");
        throw SingularException(SimpleSolver<TYPE>::mat);
    }

    int n = SimpleSolver<TYPE>::mat.Nrows();

    assert(n == in.Nrows());
    assert(in.Ncols() == out.Ncols() && in.Nrows() == out.Nrows());

    TYPE t, s;
    static const TYPE zero(0);
    int c = in.Ncols();
    const BaseMatrix<TYPE> &m = SimpleSolver<TYPE>::mat;
    for (int i = 1; i <= c; ++i)
    {
        for (int j = n; j >= 1; --j)
        {
            t = zero;
            for (int k = j + 1; k <= n; ++k)
            {
                t += out(k, i)* m(j, k);
            }
            s = m(j, j);
            out(j, i) = (in(j, i) - t) / m(j, j);
        }
    }
}

template<typename TYPE>
LogAndSign<TYPE> UpperTriangularSolver<TYPE>::LogDeterminant() const
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
#endif //SUPPER_TRIANGULAR_SOLVER_CPP
