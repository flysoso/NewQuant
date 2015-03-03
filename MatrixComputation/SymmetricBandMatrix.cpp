#ifndef SYMMETRICBAND_MATRIX_CPP
#define SYMMETRICBAND_MATRIX_CPP

#include "SymmetricBandMatrix.h"

template <typename TYPE>
SymmetricBandMatrix<TYPE>::SymmetricBandMatrix() : GeneralMatrix<TYPE>(1, 1, 1)
{
    GeneralMatrix<TYPE>::band_width.Set(0, 0, true);
    CornerClear();
}

template <typename TYPE>
SymmetricBandMatrix<TYPE>::SymmetricBandMatrix(const int &n, const int &b) : GeneralMatrix<TYPE>(n, n, n*(b + 1))
{
    GeneralMatrix<TYPE>::band_width.Set(b, b, true);
    CornerClear();
}

template <typename TYPE>
void SymmetricBandMatrix<TYPE>::CornerClear() const
{
    // set unused parts of BandMatrix to zero
    int i = GeneralMatrix<TYPE>::band_width.Lower();
    TYPE* s = GeneralMatrix<TYPE>::store;
    int bw = i + 1;
    if (i)
    {
        for (;;)
        {
            int j = i;
            TYPE* sj = s;
            while (j--)
            {
                *sj++ = GeneralMatrix<TYPE>::zero;
            }
            if (!(--i))
            {
                break;
            }
            s += bw;
        }
    }
}

template <typename TYPE>
SymmetricBandMatrix<TYPE> & SymmetricBandMatrix<TYPE>::operator=(const BaseMatrix<TYPE>& bm)
{
    if (&bm == this)
    {
        return *this;
    }
    assert(bm.BandWidth().Evalued());
    assert(bm.BandWidth().Upper() == bm.BandWidth().Lower());
    int n = bm.Nrows(), lb = bm.BandWidth().Lower();
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
        SymmetricBandMatrix<TYPE> t;
        t = bm;
        this->Swap(t);
    }
    return *this;
}

template <typename TYPE>
void SymmetricBandMatrix<TYPE>::operator<<(const BaseMatrix<TYPE>& bm)
{
    if (&bm == this)
    {
        return;
    }
    assert(bm.Nrows() == GeneralMatrix<TYPE>::nrows && bm.Ncols() == GeneralMatrix<TYPE>::ncols);
    int n = GeneralMatrix<TYPE>::nrows, lb = this->BandWidth().Lower();
    if (bm.Search(*this) == 0)
    {
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
        SymmetricBandMatrix<TYPE> t(n, lb);
        t << bm;
        this->Swap(t);
    }
}

template <typename TYPE>
TYPE& SymmetricBandMatrix<TYPE>::operator()(const int &m, const int &n)
{
    int lower_val = GeneralMatrix<TYPE>::band_width.Lower();
    int w = lower_val + 1;
    if (m >= n)
    {
        int i = lower_val + n - m;
        assert(m <= GeneralMatrix<TYPE>::nrows && n > 0);
        if (i < 0)
        {
            GeneralMatrix<TYPE>::zero_buff = GeneralMatrix<TYPE>::zero;
            return GeneralMatrix<TYPE>::zero_buff;
        }
        return GeneralMatrix<TYPE>::store[w*(m - 1) + i];
    }
    else
    {
        int i = lower_val + m - n;
        assert(n <= GeneralMatrix<TYPE>::nrows && m > 0);
        if (i < 0)
        {
            GeneralMatrix<TYPE>::zero_buff = GeneralMatrix<TYPE>::zero;
            return GeneralMatrix<TYPE>::zero_buff;
        }
        return GeneralMatrix<TYPE>::store[w*(n - 1) + i];
    }
}

template <typename TYPE>
TYPE SymmetricBandMatrix<TYPE>::operator()(const int &m, const int &n) const
{
    int lower_val = GeneralMatrix<TYPE>::band_width.Lower();
    int w = lower_val + 1;
    if (m >= n)
    {
        int i = lower_val + n - m;
        assert(m <= GeneralMatrix<TYPE>::nrows && n > 0);
        if (i < 0)
        {
            return GeneralMatrix<TYPE>::zero;
        }
        return GeneralMatrix<TYPE>::store[w*(m - 1) + i];
    }
    else
    {
        int i = lower_val + m - n;
        assert(n <= GeneralMatrix<TYPE>::nrows && m > 0);
        if (i < 0)
        {
            return GeneralMatrix<TYPE>::zero;
        }
        return GeneralMatrix<TYPE>::store[w*(n - 1) + i];
    }
}

template <typename TYPE>
MatrixType SymmetricBandMatrix<TYPE>::Type() const
{
    return MatrixType(MatrixType::Type::SymmetricBandMatrix);
}

template <typename TYPE>
void SymmetricBandMatrix<TYPE>::Solve(const BaseMatrix<TYPE>& in, BaseMatrix<TYPE>& out) const
{
    int n = GeneralMatrix<TYPE>::nrows;
    assert(n == in.Nrows());
    assert(in.Ncols() == out.Ncols() && in.Nrows() == out.Nrows());

    std::shared_ptr<LinearEquationSolver<TYPE> > solver = this->MakeSolver();
    solver->Solve(in, out);
}


template <typename TYPE>
void SymmetricBandMatrix<TYPE>::Resize(const int &n, const int &b)
{
    assert(n > 0 && b >= 0 && b < n);
    GeneralMatrix<TYPE>::GeneralResize(n, n, n*(b + 1));
    GeneralMatrix<TYPE>::band_width.Set(b, b, true);
}

template <typename TYPE>
void SymmetricBandMatrix<TYPE>::Swap(SymmetricBandMatrix<TYPE>& gm)
{
    GeneralMatrix<TYPE>::Swap((GeneralMatrix<TYPE>&)gm);
}

#endif //SYMMETRICBAND_MATRIX_CPP

