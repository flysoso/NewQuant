#ifndef LOWERTRIANULAR_MATRIX_CPP
#define LOWERTRIANULAR_MATRIX_CPP

#include "LowerTriangularMatrix.h"

template <typename TYPE>
LowerTriangularMatrix<TYPE>::LowerTriangularMatrix() : GeneralMatrix<TYPE>(1, 1, 1)
{
    GeneralMatrix<TYPE>::band_width.Set(0, 0, true);
}

template <typename TYPE>
LowerTriangularMatrix<TYPE>::LowerTriangularMatrix(const int &n) : GeneralMatrix<TYPE>(n, n, tristore(n))
{
    GeneralMatrix<TYPE>::band_width.Set(n - 1, 0, true);
}

template <typename TYPE>
LowerTriangularMatrix<TYPE> & LowerTriangularMatrix<TYPE>::operator = (const BaseMatrix<TYPE> &bm)
{
    if (&bm == this)
    {
        return *this;
    }
    assert(bm.BandWidth().Evalued());
    assert(bm.BandWidth().Upper() == 0);
    int n = bm.Nrows();
    if (bm.Search(*this) == 0)
    {
        Resize(n);
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= i; ++j)
            {
                operator()(i, j) = bm(i, j);
            }
        }
    }
    else
    {
        LowerTriangularMatrix<TYPE> t;
        t = bm;
        this->Swap(t);
    }
    return *this;
}

template <typename TYPE>
void LowerTriangularMatrix<TYPE>::operator << (const BaseMatrix<TYPE> &bm)
{
    if (&bm == this)
    {
        return;
    }
    assert(bm.Nrows() == GeneralMatrix<TYPE>::nrows || bm.Ncols() == GeneralMatrix<TYPE>::ncols);
    int n = GeneralMatrix<TYPE>::nrows;
    if (bm.Search(*this) == 0)
    {
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= i; ++j)
            {
                operator()(i, j) = bm(i, j);
            }
        }
    }
    else
    {
        LowerTriangularMatrix<TYPE> t(n);
        t << bm;
        this->Swap(t);
    }
}

template <typename TYPE>
TYPE& LowerTriangularMatrix<TYPE>::operator()(const int &m, const int &n)
{
    assert(n > 0 && m <= GeneralMatrix<TYPE>::nrows && n <= GeneralMatrix<TYPE>::ncols && m > 0);
    if (m >= n)
    {
        return GeneralMatrix<TYPE>::store[tristore(m - 1) + n - 1];
    }
    else
    {
        GeneralMatrix<TYPE>::zero_buff = GeneralMatrix<TYPE>::zero;
        return GeneralMatrix<TYPE>::zero_buff;
    }
}

template <typename TYPE>
TYPE LowerTriangularMatrix<TYPE>::operator()(const int &m, const int &n) const
{
    assert(n > 0 && m <= GeneralMatrix<TYPE>::nrows && n <= GeneralMatrix<TYPE>::ncols && m > 0);
    if (m >= n)
    {
        return GeneralMatrix<TYPE>::store[tristore(m - 1) + n - 1];
    }
    else
    {
        return GeneralMatrix<TYPE>::zero;
    }
}

template <typename TYPE>
MatrixType LowerTriangularMatrix<TYPE>::Type() const
{
    return MatrixType(MatrixType::Type::LowerTriangularMatrix);
}

template <typename TYPE>
void LowerTriangularMatrix<TYPE>::Solve(const BaseMatrix<TYPE>& in, BaseMatrix<TYPE>& out) const
{
    int n = GeneralMatrix<TYPE>::nrows;
    assert(n == in.Nrows());
    assert(in.Ncols() == out.Ncols() && in.Nrows() == out.Nrows());

    std::shared_ptr<LinearEquationSolver<TYPE> > solver = this->MakeSolver();
    solver->Solve(in, out);
}


template <typename TYPE>
void LowerTriangularMatrix<TYPE>::Resize(const int &n)
{
    GeneralMatrix<TYPE>::GeneralResize(n, n, tristore(n));
    GeneralMatrix<TYPE>::band_width.Set(n - 1, 0, true);
}

#endif //LOWERTRIANULAR_MATRIX_CPP

