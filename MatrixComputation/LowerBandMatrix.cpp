#ifndef LOWERBAND_MATRIX_CPP
#define LOWERBAND_MATRIX_CPP

#include "LowerBandMatrix.h"

template <typename TYPE>
LowerBandMatrix<TYPE> & LowerBandMatrix<TYPE>::operator=(const BaseMatrix<TYPE> &bm)
{
    if (&bm == this)
    {
        return *this;
    }
    assert(bm.BandWidth().Evalued());
    assert(bm.BandWidth().Upper() == 0);
    int lb = bm.BandWidth().Lower();
    int n = bm.Nrows();
    if (bm.Search(*this) == 0)
    {
        Resize(n, lb);
        for (int i = 0; i <= lb; ++i)
        {
            for (int j = 1; j <= n - i; ++j)
            {
                operator()(j + i, j) = bm(j + i, j);
            }
        }
    }
    else
    {
        LowerBandMatrix<TYPE> t;
        t = bm;
        this->Swap(t);
    }
    return *this;
}

template <typename TYPE>
MatrixType LowerBandMatrix<TYPE>::Type() const
{
    return MatrixType(MatrixType::Type::LowerBandMatrix);
}

template <typename TYPE>
void LowerBandMatrix<TYPE>::Resize(const int &n, const int &lb, const int &ub)
{
    assert(n > 0 && ub == 0 && lb >= 0 && lb < n);
    BandMatrix<TYPE>::Resize(n, lb, ub);
}

template <typename TYPE>
TYPE& LowerBandMatrix<TYPE>::operator()(const int &m, const int &n)
{
    int w = GeneralMatrix<TYPE>::band_width.Lower() + 1;
    int i = GeneralMatrix<TYPE>::band_width.Lower() + n - m;
    assert(m > 0 && m <= GeneralMatrix<TYPE>::nrows && n > 0 && n <= GeneralMatrix<TYPE>::ncols);
    if (i < 0 || i >= w)
    {
        GeneralMatrix<TYPE>::zero_buff = GeneralMatrix<TYPE>::zero;
        return GeneralMatrix<TYPE>::zero_buff;
    }
    else
    {
        return GeneralMatrix<TYPE>::store[w*(m - 1) + i];
    }
}

template <typename TYPE>
TYPE LowerBandMatrix<TYPE>::operator()(const int &m, const int &n) const
{
    int w = GeneralMatrix<TYPE>::band_width.Lower() + 1;
    int i = GeneralMatrix<TYPE>::band_width.Lower() + n - m;
    assert(m > 0 && m <= GeneralMatrix<TYPE>::nrows && n > 0 && n <= GeneralMatrix<TYPE>::ncols);
    if (i < 0 || i >= w)
    {
        return GeneralMatrix<TYPE>::zero;
    }
    else
    {
        return GeneralMatrix<TYPE>::store[w*(m - 1) + i];
    }
}

template <typename TYPE>
void LowerBandMatrix<TYPE>::Swap(BandMatrix<TYPE>& gm)
{
    assert(gm.BandWidth().Upper() == 0);
    BandMatrix<TYPE>::Swap(gm);
}

#endif //LOWERBAND_MATRIX_CPP

