#ifndef MATRIX_CPP
#define MATRIX_CPP

#include "Matrix.h"

#include "ColumnVector.h"
#include "RowVector.h"

namespace NewQuant
{
    template<typename TYPE>
    Matrix<TYPE>::Matrix() : GeneralMatrix<TYPE>(1, 1, 1)
    {
        GeneralMatrix<TYPE>::band_width.Set(0, 0, true);
    }

    template<typename TYPE>
    Matrix<TYPE>::Matrix(const int &m, const int &n) : GeneralMatrix<TYPE>(m, n, m*n)
    {
        if (m == n)
        {
            GeneralMatrix<TYPE>::band_width.Set(m - 1, n - 1, true);
        }
        else
        {
            GeneralMatrix<TYPE>::band_width.Set(-1, -1, false);
        }
    }

    template<typename TYPE>
    Matrix<TYPE>::Matrix(const int &m, const int &n, const TYPE &a) : GeneralMatrix<TYPE>(m, n, m * n)
    {
        GeneralMatrix<TYPE>::operator << (a);

        if (m == n)
        {
            GeneralMatrix<TYPE>::band_width.Set(m - 1, n - 1, true);
        }
        else
        {
            GeneralMatrix<TYPE>::band_width.Set(-1, -1, false);
        }
    }

    template<typename TYPE>
    Matrix<TYPE>::Matrix(const int &m, const int &n, const TYPE* a) : GeneralMatrix<TYPE>(m, n, m * n)
    {
        this->operator << (a);

        if (m == n)
        {
            GeneralMatrix<TYPE>::band_width.Set(m - 1, n - 1, true);
        }
        else
        {
            GeneralMatrix<TYPE>::band_width.Set(-1, -1, false);
        }
    }

    template<typename TYPE>
    Matrix<TYPE> & Matrix<TYPE>::operator=(const BaseMatrix<TYPE> &bm)
    {
        if (&bm == this)
        {
            return *this;
        }
        int r = bm.Nrows(), c = bm.Ncols();
        GeneralMatrix<TYPE>::nrows = r;
        GeneralMatrix<TYPE>::ncols = c;

        if (bm.Search(*this) == 0)
        {
            this->Resize(r, c);
            for (int i = 1; i <= r; ++i)
            {
                for (int j = 1; j <= c; ++j)
                {
                    operator()(i, j) = bm(i, j);
                }
            }
            if (r == c)
            {
                GeneralMatrix<TYPE>::band_width.Set(r - 1, c - 1, true);
            }
            else
            {
                GeneralMatrix<TYPE>::band_width.Set(-1, -1, false);
            }
        }
        else
        {
            Matrix<TYPE> t;
            t = bm;
            this->Swap(t);
        }
        return *this;
    }

    template<typename TYPE>
    void Matrix<TYPE>::operator<<(const BaseMatrix<TYPE> &bm)
    {
        if (&bm == this)
        {
            return;
        }
        assert(bm.Nrows() == GeneralMatrix<TYPE>::nrows && bm.Ncols() == GeneralMatrix<TYPE>::ncols);
        int r = GeneralMatrix<TYPE>::nrows, c = GeneralMatrix<TYPE>::ncols;
        if (bm.Search(*this) == 0)
        {
            for (int i = 1; i <= r; ++i)
            {
                for (int j = 1; j <= c; ++j)
                {
                    operator()(i, j) = bm(i, j);
                }
            }
        }
        else
        {
            Matrix<TYPE> t(r, c);
            t << bm;
            this->Swap(t);
        }
    }

    template<typename TYPE>
    MatrixType Matrix<TYPE>::Type() const
    {
        return MatrixType(MatrixType::Type::Matrix);
    }

    template<typename TYPE>
    TYPE& Matrix<TYPE>::operator()(const int &m, const int &n)
    {
        assert(m > 0 && m <= GeneralMatrix<TYPE>::nrows && n > 0 && n <= GeneralMatrix<TYPE>::ncols);
        return GeneralMatrix<TYPE>::store[(m - 1)*GeneralMatrix<TYPE>::ncols + n - 1];
    }

    template<typename TYPE>
    TYPE Matrix<TYPE>::operator()(const int &m, const int &n) const
    {
        assert(m > 0 && m <= GeneralMatrix<TYPE>::nrows && n > 0 && n <= GeneralMatrix<TYPE>::ncols);
        return GeneralMatrix<TYPE>::store[(m - 1)*GeneralMatrix<TYPE>::ncols + n - 1];
    }

    template<typename TYPE>
    void Matrix<TYPE>::Solve(const BaseMatrix<TYPE>& in, BaseMatrix<TYPE>& out) const
    {
        int n = GeneralMatrix<TYPE>::nrows;
        assert(n == in.Nrows());
        assert(in.Ncols() == out.Ncols() && in.Nrows() == out.Nrows());

        std::shared_ptr<LinearEquationSolver<TYPE> > solver = this->MakeSolver();
        solver->Solve(in, out);
    }


    template<typename TYPE>
    void Matrix<TYPE>::Resize(const int &nr, const int &nc)
    {
        assert(nr > 0 && nc > 0);
        GeneralMatrix<TYPE>::GeneralResize(nr, nc, nr*nc);

        if (nr == nc)
        {
            GeneralMatrix<TYPE>::band_width.Set(nr - 1, nc - 1, true);
        }
        else
        {
            GeneralMatrix<TYPE>::band_width.Set(-1, -1, false);
        }

    }

    template<typename TYPE>
    void Matrix<TYPE>::SwapRow(const int &r1, const int &r2)
    {
        assert(r1 > 0 && r1 <= GeneralMatrix<TYPE>::nrows);
        assert(r2 > 0 && r2 <= GeneralMatrix<TYPE>::nrows);
        if (r1 == r2)
        {
            return;
        }
        TYPE t;
        for (int i = 1; i <= GeneralMatrix<TYPE>::ncols; ++i)
        {
            t = operator()(r1, i);
            operator()(r1, i) = operator()(r2, i);
            operator()(r2, i) = t;
        }
    }

    template<typename TYPE>
    void Matrix<TYPE>::SwapCol(const int &c1, const int &c2)
    {
        assert(c1 > 0 && c1 <= GeneralMatrix<TYPE>::ncols);
        assert(c2 > 0 && c2 <= GeneralMatrix<TYPE>::ncols);
        if (c1 == c2)
        {
            return;
        }
        TYPE t;
        for (int i = 1; i <= GeneralMatrix<TYPE>::nrows; ++i)
        {
            t = operator()(i, c1);
            operator()(i, c1) = operator()(i, c2);
            operator()(i, c2) = t;
        }
    }
}
#endif //MATRIX_CPP

