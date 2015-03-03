#ifndef SYMMETRIC_MATRIX_CPP
#define SYMMETRIC_MATRIX_CPP

#include "SymmetricMatrix.h"

template <typename TYPE>
SymmetricMatrix<TYPE>::SymmetricMatrix() : GeneralMatrix<TYPE>(1, 1, 1)
{
    GeneralMatrix<TYPE>::band_width.Set(0, 0, true);
}

template <typename TYPE>
SymmetricMatrix<TYPE>::SymmetricMatrix(const int &n) : GeneralMatrix<TYPE>(n, n, tristore(n))
{
    GeneralMatrix<TYPE>::band_width.Set(n - 1, n - 1, true);
}

template <typename TYPE>
SymmetricMatrix<TYPE> & SymmetricMatrix<TYPE>::operator=(const BaseMatrix<TYPE>& bm)
{
    if (&bm == this)
    {
        return *this;
    }
    assert(bm.BandWidth().Evalued());
    assert(bm.BandWidth().Upper() == bm.BandWidth().Lower());
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
        SymmetricMatrix<TYPE> t;
        t = bm;
        this->Swap(t);
    }
    return *this;
}

template <typename TYPE>
void SymmetricMatrix<TYPE>::operator << (const BaseMatrix<TYPE> &bm)
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
            for (int j = 1; j <= i; ++j)
            {
                
                operator()(i, j) = bm(i, j);
            }
        }
    }
    else
    {
        SymmetricMatrix<TYPE> t(n);
        t << bm;
        this->Swap(t);
    }
}

template <typename TYPE>
TYPE& SymmetricMatrix<TYPE>::operator()(const int &m, const int &n)
{
    assert(m > 0 && n > 0 && m <= GeneralMatrix<TYPE>::nrows && n <= GeneralMatrix<TYPE>::ncols);
    if (m >= n)
    {
        return GeneralMatrix<TYPE>::store[tristore(m - 1) + n - 1];
    }
    else
    {
        return GeneralMatrix<TYPE>::store[tristore(n - 1) + m - 1];
    }
}

template <typename TYPE>
TYPE SymmetricMatrix<TYPE>::operator()(const int &m, const int &n) const
{
    assert(m > 0 && n > 0 && m <= GeneralMatrix<TYPE>::nrows && n <= GeneralMatrix<TYPE>::ncols);
    if (m >= n)
    {
        return GeneralMatrix<TYPE>::store[tristore(m - 1) + n - 1];
    }
    else
    {
        return GeneralMatrix<TYPE>::store[tristore(n - 1) + m - 1];
    }
}

template <typename TYPE>
MatrixType SymmetricMatrix<TYPE>::Type() const
{
    return MatrixType(MatrixType::Type::SymmetricMatrix);
}

template <typename TYPE>
void SymmetricMatrix<TYPE>::Solve(const BaseMatrix<TYPE>& in, BaseMatrix<TYPE>& out) const
{
    int n = GeneralMatrix<TYPE>::nrows;
    assert(n == in.Nrows());
    assert(in.Ncols() == out.Ncols() && in.Nrows() == out.Nrows());

    std::shared_ptr<LinearEquationSolver<TYPE> > solver = this->MakeSolver();
    solver->Solve(in, out);
}

template <typename TYPE>
void SymmetricMatrix<TYPE>::Resize(const int &n)
{
    assert(n > 0);
    GeneralMatrix<TYPE>::GeneralResize(n, n, tristore(n));
    GeneralMatrix<TYPE>::band_width.Set(n - 1, n - 1, true);
}

#endif //SYMMETRIC_MATRIX_CPP

