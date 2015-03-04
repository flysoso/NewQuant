#ifndef SQUARE_MATRIX_CPP
#define SQUARE_MATRIX_CPP

#include "SquareMatrix.h"

namespace NewQuant
{
    template <typename TYPE>
    SquareMatrix<TYPE>::SquareMatrix(const int &n) : Matrix<TYPE>(n, n)
    {}

    template <typename TYPE>
    SquareMatrix<TYPE>::SquareMatrix(const Matrix<TYPE>& gm)
    {
        assert(gm.Nrows() == gm.Ncols());
        GeneralMatrix<TYPE>::CopyMatrix(gm);
    }

    template <typename TYPE>
    SquareMatrix<TYPE> & SquareMatrix<TYPE>::operator=(const BaseMatrix<TYPE> &bm)
    {
        if (&bm == this)
        {
            return *this;
        }
        int r = bm.Nrows(), c = bm.Ncols();
        assert(r == c);

        if (bm.Search(*this) == 0)
        {
            this->Resize(r, c);
            for (int i = 1; i <= r; ++i)
            {
                for (int j = 1; j <= c; ++j)
                {
                    this->operator()(i, j) = bm(i, j);
                }
            }
        }
        else
        {
            SquareMatrix<TYPE> t;
            t = bm;
            this->Swap(t);
        }
        return *this;
    }

    template <typename TYPE>
    SquareMatrix<TYPE> & SquareMatrix<TYPE>::operator=(const Matrix<TYPE>& m)
    {
        assert(m.Nrows() == m.Ncols());
        if (&m == this)
        {
            return *this;
        }
        GeneralMatrix<TYPE>::CopyMatrix(m);
        return *this;
    }

    template <typename TYPE>
    MatrixType SquareMatrix<TYPE>::Type() const
    {
        return MatrixType(MatrixType::Type::SquareMatrix);
    }


    template <typename TYPE>
    void SquareMatrix<TYPE>::Resize(const int &n)
    {
        assert(n > 0);
        Matrix<TYPE>::Resize(n, n);
    }

    template <typename TYPE>
    void SquareMatrix<TYPE>::Resize(const int &nr, const int &nc)
    {
        assert(nc == nr && nr > 0);
        Resize(nr);
    }

    template <typename TYPE>
    void SquareMatrix<TYPE>::Swap(Matrix<TYPE>& gm)
    {
        assert(gm.Nrows() == gm.Ncols());
        Matrix<TYPE>::Swap(gm);
    }
}
#endif //SQUARE_MATRIX_CPP

