#ifndef CHOLESKY_SOLVER_H
#define CHOLESKY_SOLVER_H

#include "SimpleSolver.h"
#include "UpperTriangularSolver.h"
#include "LowerTriangularMatrix.h"

namespace NewQuant
{
    template<typename TYPE>
    class CholeskySolver :public SimpleSolver < TYPE >
    {
    private:
        LowerTriangularMatrix<TYPE> lm;

        void CholeskyDecomposition(const BaseMatrix<TYPE> &);
    public:
        CholeskySolver(const BaseMatrix<TYPE> &bm, const TYPE &e) :
            SimpleSolver<TYPE>(bm, e), lm(bm.Nrows())
        {
            CholeskyDecomposition(bm);
        }

        const LowerTriangularMatrix<TYPE> & Lower() const
        {
            return lm;
        }

        LogAndSign<TYPE> LogDeterminant() const;

        void Solve(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;
    };
}

#include "CholeskySolver.cpp"


#endif //CHOLESKY_SOLVER_H
