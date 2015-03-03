#ifndef BAND_CHOLESKY_SOLVER_H
#define BAND_CHOLESKY_SOLVER_H

#include "SimpleSolver.h"
#include "LowerBandMatrix.h"


template<typename TYPE>
class BandCholeskySolver :public SimpleSolver < TYPE >
{
private:
    LowerBandMatrix<TYPE> lm;

    void BandCholeskyDecomposition(const BaseMatrix<TYPE> &);
public:
    BandCholeskySolver(const BaseMatrix<TYPE> &bm, const TYPE &e) :
        SimpleSolver<TYPE>(bm, e), lm(bm.Nrows(),bm.BandWidth().Lower())
    {
        BandCholeskyDecomposition(bm);
    }

    const LowerBandMatrix<TYPE> & Lower() const
    {
        return lm;
    }

    LogAndSign<TYPE> LogDeterminant() const;

    void Solve(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;
};

#include "BandCholeskySolver.cpp"


#endif //BAND_CHOLESKY_SOLVER_H
