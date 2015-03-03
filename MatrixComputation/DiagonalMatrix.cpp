#ifndef DIAGONAL_MATRIX_CPP
#define DIAGONAL_MATRIX_CPP

#include "DiagonalMatrix.h"

template <typename TYPE>
DiagonalMatrix<TYPE>::DiagonalMatrix() : GeneralMatrix<TYPE>(1, 1, 1)
{
    GeneralMatrix<TYPE>::band_width.Set(0, 0, true);
}

template <typename TYPE>
DiagonalMatrix<TYPE>::DiagonalMatrix(const int &m) : GeneralMatrix<TYPE>(m, m, m)
{
    GeneralMatrix<TYPE>::band_width.Set(0, 0, true);
}

template <typename TYPE>
DiagonalMatrix<TYPE> & DiagonalMatrix<TYPE>::operator=(const BaseMatrix<TYPE> &bm)
{
    if (&bm == this)
    {
        return *this;
    }
    assert(bm.BandWidth().Evalued());
    assert(bm.BandWidth().Upper() == bm.BandWidth().Lower() && bm.BandWidth().Lower() == 0);
    int n = bm.Nrows();
    if (bm.Search(*this) == 0)
    {
        Resize(n);
        for (int i = 1; i <= n; ++i)
        {
            GeneralMatrix<TYPE>::store[i - 1] = bm(i, i);
        }
    }
    else
    {
        DiagonalMatrix<TYPE> t;
        t = bm;
        this->Swap(t);
    }
    return *this;
}

template <typename TYPE>
void DiagonalMatrix<TYPE>::operator<<(const BaseMatrix<TYPE> &bm)
{
    if (&bm == this)
    {
        return;
    }
    assert(bm.Nrows() == GeneralMatrix<TYPE>::nrows && bm.Ncols() == GeneralMatrix<TYPE>::ncols);
    int n = GeneralMatrix<TYPE>::nrows;
    if (bm.Search(*this) == 0)
    {
        for (int i = 1; i <= n; ++i)
        {
            GeneralMatrix<TYPE>::store[i - 1] = bm(i, i);
        }
    }
    else
    {
        DiagonalMatrix<TYPE> t(n);
        t << bm;
        this->Swap(t);
    }
}

template <typename TYPE>
TYPE& DiagonalMatrix<TYPE>::operator()(const int &m, const int &n)
{
    assert(n > 0 && m <= GeneralMatrix<TYPE>::nrows && n <= GeneralMatrix<TYPE>::ncols && m > 0);
    if (m == n)
    {
        return GeneralMatrix<TYPE>::store[n - 1];
    }
    else
    {
        GeneralMatrix<TYPE>::zero_buff = GeneralMatrix<TYPE>::zero;
        return GeneralMatrix<TYPE>::zero_buff;
    }
}

template <typename TYPE>
TYPE& DiagonalMatrix<TYPE>::operator()(const int &m)
{
    assert(m > 0 && m <= GeneralMatrix<TYPE>::nrows);
    return GeneralMatrix<TYPE>::store[m - 1];
}

template <typename TYPE>
TYPE DiagonalMatrix<TYPE>::operator()(const int &m, const int &n) const
{
    assert(n > 0 && m <= GeneralMatrix<TYPE>::nrows && n <= GeneralMatrix<TYPE>::ncols && m > 0);
    if (m == n)
    {
        return GeneralMatrix<TYPE>::store[n - 1];
    }
    else
    {
        return GeneralMatrix<TYPE>::zero;
    }
}

template <typename TYPE>
TYPE DiagonalMatrix<TYPE>::operator()(const int &m) const
{
    assert(m > 0 && m <= GeneralMatrix<TYPE>::nrows);
    return GeneralMatrix<TYPE>::store[m - 1];
}

template <typename TYPE>
MatrixType DiagonalMatrix<TYPE>::Type() const
{
    return MatrixType(MatrixType::Type::DiagonalMatrix);
}

template <typename TYPE>
TYPE DiagonalMatrix<TYPE>::Trace() const
{
    int i = GeneralMatrix<TYPE>::nrows;
    TYPE sum(0);
    TYPE* s = GeneralMatrix<TYPE>::store;
    while (i--)
    {
        sum += *s++;
    }

    return sum;
}

template <typename TYPE>
void DiagonalMatrix<TYPE>::Solve(const BaseMatrix<TYPE>& in, BaseMatrix<TYPE>& out) const
{
    int n = GeneralMatrix<TYPE>::nrows;
    assert(n == in.Nrows());
    assert(in.Ncols() == out.Ncols() && in.Nrows() == out.Nrows());

    std::shared_ptr<LinearEquationSolver<TYPE> > solver = this->MakeSolver();
    solver->Solve(in, out);
}

template <typename TYPE>
void DiagonalMatrix<TYPE>::Resize(const int &nr)
{
    assert(nr > 0);
    GeneralMatrix<TYPE>::GeneralResize(nr, nr, nr);
}

#endif //DIAGONAL_MATRIX_CPP

