#ifndef BAND_LU_SOLVER_CPP
#define BAND_LU_SOLVER_CPP

#include "BandLUsolver.h"

namespace NewQuant
{
    template<typename TYPE>
    BandLUsolver<TYPE>::BandLUsolver(const BaseMatrix<TYPE> &bm, const TYPE &e) :
        LinearEquationSolver<TYPE>(),
        lbw(bm.BandWidth().Lower()), ubw(bm.BandWidth().Upper()),
        epsilon(e), left(bm.Nrows()), right(bm.Nrows()), mat(bm)
    {}

    template<typename TYPE>
    BandLUsolver<TYPE>::BandLUsolver(const BaseMatrix<TYPE> &bm, const int &lw, const int &uw, const TYPE &e) :
        LinearEquationSolver<TYPE>(), lbw(lw), ubw(uw), epsilon(e),
        left(bm.Nrows()), right(bm.Nrows()), mat(bm)
    {}

    /***** BandLUcombine_LbUb *****/
    template<typename TYPE>
    BandLUcombine_LbUb<TYPE>::BandLUcombine_LbUb(LowerBandMatrix<TYPE> &lm, UpperBandMatrix<TYPE> &um) : l(lm), u(um), MatrixExpression<TYPE>()
    {
        dim = lm.Nrows();
        MatrixExpression<TYPE>::nrows = dim;
        MatrixExpression<TYPE>::ncols = dim;
        MatrixExpression<TYPE>::band_width.Set(lm.BandWidth().Lower(), um.BandWidth().Upper(), true);
    }

    /***** BandLUcombine_LtUb *****/
    template<typename TYPE>
    BandLUcombine_LtUb<TYPE>::BandLUcombine_LtUb(LowerTriangularMatrix<TYPE> &lm, UpperBandMatrix<TYPE> &um) : l(lm), u(um), MatrixExpression<TYPE>()
    {
        dim = lm.Nrows();
        MatrixExpression<TYPE>::nrows = dim;
        MatrixExpression<TYPE>::ncols = dim;
        MatrixExpression<TYPE>::band_width.Set(lm.BandWidth().Lower(), um.BandWidth().Upper(), true);
    }
}
#endif //BAND_LU_SOLVER_CPP
