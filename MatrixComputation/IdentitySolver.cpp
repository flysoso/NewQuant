#ifndef IDENTITY_SOLVER_CPP
#define IDENTITY_SOLVER_CPP

#include "IdentitySolver.h"

#include "SingularException.h"

template <typename TYPE>
void IdentitySolver<TYPE>::Solve(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const
{
    if (LinearEquationSolver<TYPE>::IsFailed())
    {
        Singleton<Tracer>::Instance()->AddMessage("IdentitySolver::Solve");
        throw SingularException(SimpleSolver<TYPE>::mat);
    }

    int n = SimpleSolver<TYPE>::mat.Nrows();

    assert(n == in.Nrows());
    assert(in.Ncols() == out.Ncols() && in.Nrows() == out.Nrows());

    TYPE t = SimpleSolver<TYPE>::mat(1, 1);
    int c = in.Ncols();
    for (int i = 1; i <= c; ++i)
    {
        for (int j = n; j >= 1; --j)
        {
            out(j, i) = in(j, i) / t;
        }
    }

}

template<typename TYPE>
LogAndSign<TYPE> IdentitySolver<TYPE>::LogDeterminant() const
{
    if (LinearEquationSolver<TYPE>::IsFailed())
    {
        static const TYPE zero(0);
        LogAndSign<TYPE> ld(zero);
        return ld;
    }
    const BaseMatrix<TYPE> &m = SimpleSolver<TYPE>::mat;
    LogAndSign<TYPE> ld(m(1, 1));
    int n = m.Nrows();
    ld.PowEq(n);
    return ld;
}

#endif //IDENTITY_SOLVER_CPP
