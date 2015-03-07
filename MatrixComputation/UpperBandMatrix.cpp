#ifndef UPPERBAND_MATRIX_CPP
#define UPPERBAND_MATRIX_CPP

#include "UpperBandMatrix.h"

namespace NewQuant
{
    template<typename TYPE>
    UpperBandMatrix<TYPE> & UpperBandMatrix<TYPE>::operator=(const BaseMatrix<TYPE> &bm)
    {
        if (&bm == this)
        {
            return *this;
        }
        assert(bm.BandWidth().Evalued());
        assert(bm.BandWidth().Lower() == 0);
        int ub = bm.BandWidth().Upper();
        int n = bm.Nrows();
        if (bm.Search(*this) == 0)
        {
            Resize(n, ub);
            for (int i = 0; i <= ub; ++i)
            {
                for (int j = i + 1; j <= n; ++j)
                {
                    operator()(j - i, j) = bm(j - i, j);
                }
            }
        }
        else
        {
            UpperBandMatrix<TYPE> t;
            t = bm;
            this->Swap(t);
        }
        return *this;
    }

    template<typename TYPE>
    MatrixType UpperBandMatrix<TYPE>::Type() const
    {
        return MatrixType(MatrixType::Type::UpperBandMatrix);
    }

    template<typename TYPE>
    void UpperBandMatrix<TYPE>::Resize(const int &n, const int &lb, const int &ub)
    {
        assert(n > 0 && lb == 0 && ub >= 0 && ub < n);
        BandMatrix<TYPE>::Resize(n, lb, ub);
    }

    template<typename TYPE>
    TYPE& UpperBandMatrix<TYPE>::operator()(const int &m, const int &n)
    {
        int w = GeneralMatrix<TYPE>::band_width.Upper() + 1;
        int i = n - m;
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

    template<typename TYPE>
    TYPE UpperBandMatrix<TYPE>::operator()(const int &m, const int &n) const
    {
        int w = GeneralMatrix<TYPE>::band_width.Upper() + 1;
        int i = n - m;
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

    template<typename TYPE>
    void UpperBandMatrix<TYPE>::Swap(BandMatrix<TYPE>& gm)
    {
        assert(gm.BandWidth().Lower() == 0);
        BandMatrix<TYPE>::Swap(gm);
    }
}

#endif //UPPERBAND_MATRIX_CPP

