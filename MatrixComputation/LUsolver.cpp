#ifndef LU_SOLVER_CPP
#define LU_SOLVER_CPP

#include "LUsolver.h"

template <typename TYPE>
LUsolver<TYPE>::LUsolver(const BaseMatrix<TYPE> &bm, const TYPE &e) :
LinearEquationSolver<TYPE>(), lm(bm.Nrows()), um(bm.Nrows()),
combine(lm, um), epsilon(e), left(bm.Nrows()), right(bm.Nrows()),
mat(bm)
{
    int n = bm.Nrows();
    LUcombine<TYPE> &m = LUsolver<TYPE>::combine;
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= n; ++j)
        {
            m(i, j) = bm(i, j);
        }
    }
}

/***** LUcombine *****/
template <typename TYPE>
LUcombine<TYPE>::LUcombine(LowerTriangularMatrix<TYPE> &lm, UpperTriangularMatrix<TYPE> &um) : l(lm), u(um), MatrixExpression<TYPE>()
{
    dim = lm.Nrows();
    MatrixExpression<TYPE>::nrows = dim;
    MatrixExpression<TYPE>::ncols = dim;
    MatrixExpression<TYPE>::band_width.Set(dim - 1, dim - 1, true);

    static const TYPE one(1);
    for (int i = 1; i <= dim; ++i)
    {
        l(i, i) = one;
    }
}


#endif //LU_SOLVER_CPP
