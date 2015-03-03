#ifndef SYMMETRICBAND_MATRIX_H
#define SYMMETRICBAND_MATRIX_H

#include "GeneralMatrix.h"
#include "IdentityMatrix.h"
#include "SymmetricMatrix.h"
#include "DiagonalMatrix.h"

#include "DiagonalSolver.h"
#include "BandLUsolverPartialPivot.h"
#include "LUsolverPartialPivot.h"

/// Symmetric band matrix.
template <typename TYPE>
class SymmetricBandMatrix : public GeneralMatrix < TYPE >
{
private:
    void CornerClear() const;                    // set unused elements to zero
public:
    SymmetricBandMatrix();

    SymmetricBandMatrix(const int &, const int &);

    SymmetricBandMatrix(const SymmetricBandMatrix<TYPE>& gm)
    {
        GeneralMatrix<TYPE>::CopyMatrix(gm);
    }

    ~SymmetricBandMatrix() {}

    SymmetricBandMatrix<TYPE> & operator=(const BaseMatrix<TYPE>&);

    SymmetricBandMatrix<TYPE> & operator=(const SymmetricBandMatrix<TYPE>& m)
    {
        if (&m == this)
        {
            return *this;
        }
        GeneralMatrix<TYPE>::CopyMatrix(m);
        return *this;
    }

    void operator<<(const BaseMatrix<TYPE>&);

    void operator<<(const TYPE &x)
    {
        GeneralMatrix<TYPE>::operator<<(x);
    }

    void operator<<(const int &x)
    {
        GeneralMatrix<TYPE>::operator<<(x);
    }

    TYPE& operator()(const int &, const int &);                  // access element

    TYPE operator()(const int &, const int &) const;             // access element

    MatrixType Type() const;

    std::shared_ptr<GeneralMatrix<TYPE> > MakeInv() const
    {
        int lbw = GeneralMatrix<TYPE>::band_width.Lower();
        int n = GeneralMatrix<TYPE>::nrows;
        std::shared_ptr<GeneralMatrix<TYPE> > inv;

        if (lbw == 0)
        {
            inv.reset(new DiagonalMatrix<TYPE>(n));
        }
        else
        {
            inv.reset(new SymmetricMatrix<TYPE>(n));
        }
        IdentityMatrix<TYPE> imat(n);
        Solve(imat, *inv);
        return inv;
    }

    std::shared_ptr<LinearEquationSolver<TYPE> > MakeSolver() const
    {
        std::shared_ptr<LinearEquationSolver<TYPE> > solver;
        int lbw = GeneralMatrix<TYPE>::band_width.Lower();
        int n = GeneralMatrix<TYPE>::nrows;
        if (lbw == 0)
        {
            solver.reset(new DiagonalSolver<TYPE>(*this, Precision<TYPE>::GetPrecision()));
        }
        else if (lbw < n / 2)
        {
            solver.reset(new BandLUsolverPartialPivot<TYPE>(*this, Precision<TYPE>::GetPrecision()));
        }
        else
        {
            solver.reset(new LUsolverPartialPivot<TYPE>(*this, Precision<TYPE>::GetPrecision()));
        }
        return solver;
    }

    void Solve(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;

    void Resize(const int &, const int &);                       // change dimensions

    void Swap(SymmetricBandMatrix<TYPE>& gm);

    void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
    {
        assert(r > 0 && r <= GeneralMatrix<TYPE>::nrows);
        const MatrixBandWidth<TYPE> &bw = GeneralMatrix<TYPE>::band_width;
        int dim = GeneralMatrix<TYPE>::nrows;
        int left = std::min(bw.Lower(), r - 1);
        int right = std::min(bw.Upper(), dim - r);

        mi.Clear();
        mi.Append(r - left, r + right);
    }

    void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
    {
        assert(c > 0 && c <= GeneralMatrix<TYPE>::ncols);
        const MatrixBandWidth<TYPE> &bw = GeneralMatrix<TYPE>::band_width;
        int dim = GeneralMatrix<TYPE>::nrows;
        int up = std::min(bw.Upper(), c - 1);
        int down = std::min(bw.Lower(), dim - c);

        mi.Clear();
        mi.Append(c - up, c + down);
    }
};

template <typename TYPE>
inline void Swap(SymmetricBandMatrix<TYPE>& A, SymmetricBandMatrix<TYPE>& B)
{
    A.Swap(B);
}

#include "SymmetricBandMatrix.cpp"

#endif //SYMMETRICBAND_MATRIX_H

