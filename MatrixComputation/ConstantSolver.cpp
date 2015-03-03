#ifndef CONSTANT_SOLVER_CPP
#define CONSTANT_SOLVER_CPP

#include "ConstantSolver.h"

#include "SingularException.h"

template <typename TYPE>
void ConstantSolver<TYPE>::Solve(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const
{
    if (LinearEquationSolver<TYPE>::IsFailed())
    {
        Singleton<Tracer>::Instance()->AddMessage("ConstantSolver::Solve");
        throw SingularException(SimpleSolver<TYPE>::mat);
    }

    int r = SimpleSolver<TYPE>::mat.Nrows();
    int c = SimpleSolver<TYPE>::mat.Ncols();

    assert(r == 1 && c == 1 && c == in.Nrows());
    assert(in.Ncols() == out.Ncols() && in.Nrows() == out.Nrows());

    const BaseMatrix<TYPE> &m = SimpleSolver<TYPE>::mat;
    for (int i = 1; i <= c; ++i)
    {
        for (int j = r; j >= 1; --j)
        {
            out(j, i) = in(j, i) / m(j, j);
        }
    }
}

template<typename TYPE>
LogAndSign<TYPE> ConstantSolver<TYPE>::LogDeterminant() const
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

#endif //CONSTANT_SOLVER_CPP
