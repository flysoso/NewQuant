#ifndef TRIDIAGONAL_MATRIX_CPP
#define TRIDIAGONAL_MATRIX_CPP

#include "TridiagonalMatrix.h"

namespace NewQuant
{
    template<typename TYPE>
    TridiagonalMatrix<TYPE> & TridiagonalMatrix<TYPE>::operator=(const BaseMatrix<TYPE> &bm)
    {
        if (&bm == this)
        {
            return *this;
        }
        assert(bm.BandWidth().Evalued());
        assert(bm.BandWidth().Upper() == 1 && bm.BandWidth().Lower() == 1);
        int lb = 1, ub = 1;
        int n = bm.Nrows();
        if (bm.Search(*this) == 0)
        {
            Resize(n);
            for (int i = 1; i <= ub; ++i)
            {
                for (int j = i + 1; j <= n; ++j)
                {
                    this->operator()(j - i, j) = bm(j - i, j);
                }
            }
            for (int i = 1; i <= lb; ++i)
            {
                for (int j = 1; j <= n - i; ++j)
                {
                    this->operator()(j + i, j) = bm(j + i, j);
                }
            }
            for (int i = 1; i <= n; ++i)
            {
                this->operator()(i, i) = bm(i, i);
            }
        }
        else
        {
            TridiagonalMatrix<TYPE> t;
            t = bm;
            this->Swap(t);
        }
        return *this;
    }

    template<typename TYPE>
    MatrixType TridiagonalMatrix<TYPE>::Type() const
    {
        return MatrixType(MatrixType::Type::TridiagonalMatrix);
    }

    template<typename TYPE>
    void TridiagonalMatrix<TYPE>::Resize(const int &n, const int &lb, const int &ub)
    {
        assert(n > 0 && lb == 1 && ub == 1);
        BandMatrix<TYPE>::Resize(n, lb, ub);
    }

    template<typename TYPE>
    void TridiagonalMatrix<TYPE>::Swap(BandMatrix<TYPE>& gm)
    {
        assert(gm.BandWidth().Upper() == 1 && gm.BandWidth().Lower() == 1);
        BandMatrix<TYPE>::Swap(gm);
    }
}
#endif //TRIDIAGONAL_MATRIX_CPP

