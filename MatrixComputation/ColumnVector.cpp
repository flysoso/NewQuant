#ifndef COLUMN_VECTOR_CPP
#define COLUMN_VECTOR_CPP

#include "ColumnVector.h"

template <typename TYPE>
ColumnVector<TYPE>& ColumnVector<TYPE>::operator=(const BaseMatrix<TYPE>& bm)
{
    if (&bm == this)
    {
        return *this;
    }
    assert(bm.Ncols() == 1);
    if (bm.Search(*this) == 0)
    {
        Resize(bm.Nrows());
        for (int i = 1; i <= bm.Nrows(); ++i)
        {
            operator()(i) = bm(i, 1);
        }
    }
    else
    {
        ColumnVector<TYPE> t;
        t = bm;
        this->Swap(t);
    }
    return *this;
}

template <typename TYPE>
TYPE& ColumnVector<TYPE>::operator()(const int &m)
{
    assert(m > 0 && m <= GeneralMatrix<TYPE>::nrows);
    return GeneralMatrix<TYPE>::store[m - 1];
}

template <typename TYPE>
TYPE& ColumnVector<TYPE>::operator()(const int &m, const int &n)
{
    assert(m > 0 && m <= GeneralMatrix<TYPE>::nrows && n == 1);
    return GeneralMatrix<TYPE>::store[m - 1];
}

template <typename TYPE>
TYPE ColumnVector<TYPE>::operator()(const int & m, const int & n) const
{
    assert(m > 0 && m <= GeneralMatrix<TYPE>::nrows && n == 1);
    return GeneralMatrix<TYPE>::store[m - 1];
}

template <typename TYPE>
TYPE ColumnVector<TYPE>::operator()(const int & m) const
{
    assert(m > 0 && m <= GeneralMatrix<TYPE>::nrows);
    return GeneralMatrix<TYPE>::store[m - 1];
}

template <typename TYPE>
MatrixType ColumnVector<TYPE>::Type() const
{
    return MatrixType(MatrixType::Type::ColumnVector);
}

template <typename TYPE>
void ColumnVector<TYPE>::Resize(const int &nr)
{
    assert(nr > 0);
    GeneralMatrix<TYPE>::GeneralResize(nr, 1, nr);
    if (nr == 1)
    {
        GeneralMatrix<TYPE>::band_width.Set(0, 0, true);
    }
    else
    {
        GeneralMatrix<TYPE>::band_width.Set(-1, -1, false);
    }
}

template <typename TYPE>
void ColumnVector<TYPE>::Resize(const int &nr, const int &nc)
{
    assert(nc == 1 && nr > 0);
    GeneralMatrix<TYPE>::GeneralResize(nr, 1, nr);
    if (nr == 1)
    {
        GeneralMatrix<TYPE>::band_width.Set(0, 0, true);
    }
    else
    {
        GeneralMatrix<TYPE>::band_width.Set(-1, -1, false);
    }
}

template <typename TYPE>
void ColumnVector<TYPE>::Swap(Matrix<TYPE>& gm)
{
    assert(gm.Ncols() == 1);
    Matrix<TYPE>::Swap(gm);
}

#endif //COLUMN_VECTOR_CPP

