#ifndef ROW_VECTOR_CPP
#define ROW_VECTOR_CPP

#include "RowVector.h"

namespace NewQuant
{
    template<typename TYPE>
    RowVector<TYPE>& RowVector<TYPE>::operator=(const BaseMatrix<TYPE> &bm)
    {
        if (&bm == this)
        {
            return *this;
        }
        assert(bm.Nrows() == 1);
        if (bm.Search(*this) == 0)
        {
            this->Resize(bm.Ncols());
            for (int i = 1; i <= bm.Ncols(); ++i)
            {
                operator()(i) = bm(1, i);
            }
        }
        else
        {
            RowVector<TYPE> t;
            t = bm;
            this->Swap(t);
        }
        return *this;
    }

    template<typename TYPE>
    TYPE& RowVector<TYPE>::operator()(const int &n)
    {
        assert(n > 0 && n <= GeneralMatrix<TYPE>::ncols);
        return GeneralMatrix<TYPE>::store[n - 1];
    }

    template<typename TYPE>
    TYPE& RowVector<TYPE>::operator()(const int &m, const int &n)
    {
        assert(n > 0 && n <= GeneralMatrix<TYPE>::ncols && m == 1);
        return GeneralMatrix<TYPE>::store[n - 1];
    }

    template<typename TYPE>
    TYPE RowVector<TYPE>::operator()(const int &n) const
    {
        assert(n > 0 && n <= GeneralMatrix<TYPE>::ncols);
        return GeneralMatrix<TYPE>::store[n - 1];
    }

    template<typename TYPE>
    TYPE RowVector<TYPE>::operator()(const int &m, const int &n) const
    {
        assert(n > 0 && n <= GeneralMatrix<TYPE>::ncols && m == 1);
        return GeneralMatrix<TYPE>::store[n - 1];
    }

    template<typename TYPE>
    MatrixType RowVector<TYPE>::Type() const
    {
        return MatrixType(MatrixType::Type::RowVector);
    }

    template<typename TYPE>
    void RowVector<TYPE>::Resize(const int &nc)
    {
        assert(nc > 0);
        GeneralMatrix<TYPE>::GeneralResize(1, nc, nc);
        if (nc == 1)
        {
            GeneralMatrix<TYPE>::band_width.Set(0, 0, true);
        }
        else
        {
            GeneralMatrix<TYPE>::band_width.Set(-1, -1, false);
        }
    }

    template<typename TYPE>
    void RowVector<TYPE>::Resize(const int &nr, const int &nc)
    {
        assert(nc > 0 && nr == 1);
        Resize(nc);
    }

    template<typename TYPE>
    void RowVector<TYPE>::Swap(Matrix<TYPE>& gm)
    {
        assert(gm.Nrows() == 1);
        Matrix<TYPE>::Swap(gm);
    }
}
#endif //ROW_VECTOR_CPP

