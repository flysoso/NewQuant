#ifndef PERMUTE_SOLVER_H
#define PERMUTE_SOLVER_H

#include "SimpleSolver.h"
#include "PermuteMatrix.h"
#include "TransposedMatrix.h"
#include "MatrixIndex.h"

namespace NewQuant
{
    template <typename TYPE> class PermuteMatrix;

    template <typename TYPE>
    class PermuteSolver :public SimpleSolver < TYPE >
    {
    private:
        const PermuteMatrix<TYPE> &per_mat;
    public:
        PermuteSolver(const PermuteMatrix<TYPE> &pm, const TYPE &e) :SimpleSolver<TYPE>(pm, e), per_mat(pm){}

        LogAndSign<TYPE> LogDeterminant() const
        {
            static const TYPE one(1), neg_one(-1);
            if (per_mat.SwapTimes() % 2 == 0)
            {
                return one;
            }
            else
            {
                return neg_one;
            }
        }

        void TestSingular(){}

        void Solve(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const
        {
            int n = SimpleSolver<TYPE>::mat.Nrows();

            assert(n == in.Nrows());
            assert(in.Ncols() == out.Ncols() && in.Nrows() == out.Nrows());
            PermuteMatrix<TYPE> per_mat_inv;
            per_mat_inv.InvEq(per_mat);

            for (int i = 1; i <= in.Nrows(); ++i)
            {
                for (int j = 1; j <= in.Ncols(); ++j)
                {
                    out(i, j) = in(per_mat_inv.RowIndex(i), j);
                }
            }
        }

    };
}

#endif //PERMUTE_SOLVER_H
