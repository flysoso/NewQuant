#ifndef IDENTITY_SOLVER_H
#define IDENTITY_SOLVER_H

#include "SimpleSolver.h"

namespace NewQuant
{
    template <typename TYPE>
    class IdentitySolver : public SimpleSolver < TYPE >
    {
    public:
        IdentitySolver(const BaseMatrix<TYPE> &gm, const TYPE &e) : SimpleSolver<TYPE>(gm, e)
        {
            TestSingular();
        }

        void Solve(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;

        void TestSingular()
        {
            const BaseMatrix<TYPE> &m = SimpleSolver<TYPE>::mat;
            bool not_sig = true;
            not_sig = not_sig && (fabs(m(1, 1)) >= SimpleSolver<TYPE>::epsilon);
            LinearEquationSolver<TYPE>::fail = !not_sig;
        }

        LogAndSign<TYPE> LogDeterminant() const;
    };
}
#include "IdentitySolver.cpp"

#endif //IDENTITY_SOLVER_H


