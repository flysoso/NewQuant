#ifndef GETSUB_MATRIX_H
#define GETSUB_MATRIX_H

#include "MatrixExpression.h"

/// A submatrix of a matrix.
template <typename TYPE, typename MATRIX>
class GetSubMatrix : public UnitaryMatrixExpression < TYPE, MATRIX >
{
private:
    int row_skip;
    int col_skip;
    int row1, row2, col1, col2;
    /*
    row_skip:the number of row indexes to skip
    col_skip:the number of col indexes to skip
    row1:start of row index,row2:end of row index
    col1:start of col index,col2:end of col index
    */
    MATRIX &mat_r;
public:
    GetSubMatrix(MATRIX &m, int r1, int r2, int c1, int c2) : mat_r(m), UnitaryMatrixExpression<TYPE, MATRIX>(m)
    {
        row_skip = r1 - 1;
        col_skip = c1 - 1;
        row1 = r1, row2 = r2, col1 = c1, col2 = c2;
        MatrixExpression<TYPE>::Set(r2 - r1 + 1, c2 - c1 + 1);

        if (MatrixExpression<TYPE>::nrows == MatrixExpression<TYPE>::ncols)
        {
            MatrixExpression<TYPE>::band_width.Set(MatrixExpression<TYPE>::nrows - 1, MatrixExpression<TYPE>::nrows - 1, true);
        }
        else
        {
            MatrixExpression<TYPE>::band_width.Set(-1, -1, false);
        }
    }

    ~GetSubMatrix() {}

    GetSubMatrix<TYPE, MATRIX> & operator=(const TYPE &x)
    {
        int r = MatrixExpression<TYPE>::nrows;
        int c = MatrixExpression<TYPE>::ncols;
        for (int i = 1; i <= r; ++i)
        {
            for (int j = 1; j <= c; ++j)
            {
                mat_r(i + row_skip, j + col_skip) = x;
            }
        }
        return *this;
    }

    GetSubMatrix<TYPE, MATRIX> & operator=(const GeneralMatrix<TYPE> &x)
    {
        int r = MatrixExpression<TYPE>::nrows;
        int c = MatrixExpression<TYPE>::ncols;
        assert(r == x.Nrows() && c == x.Ncols());
        for (int i = 1; i <= r; ++i)
        {
            for (int j = 1; j <= c; ++j)
            {
                mat_r(i + row_skip, j + col_skip) = x(i, j);
            }
        }
        return *this;
    }

    GetSubMatrix<TYPE, MATRIX> & operator=(const MatrixExpression<TYPE> &x)
    {
        int r = MatrixExpression<TYPE>::nrows;
        int c = MatrixExpression<TYPE>::ncols;
        assert(r == x.Nrows() && c == x.Ncols());
        for (int i = 1; i <= r; ++i)
        {
            for (int j = 1; j <= c; ++j)
            {
                mat_r(i + row_skip, j + col_skip) = x(i, j);
            }
        }
        return *this;
    }

    void operator+=(const TYPE &x)
    {
        int r = MatrixExpression<TYPE>::nrows;
        int c = MatrixExpression<TYPE>::ncols;
        for (int i = 1; i <= r; ++i)
        {
            for (int j = 1; j <= c; ++j)
            {
                mat_r(i + row_skip, j + col_skip) += x;
            }
        }
    }

    void operator+=(const GeneralMatrix<TYPE> &x)
    {
        int r = MatrixExpression<TYPE>::nrows;
        int c = MatrixExpression<TYPE>::ncols;
        assert(r == x.Nrows() && c == x.Ncols());
        for (int i = 1; i <= r; ++i)
        {
            for (int j = 1; j <= c; ++j)
            {
                mat_r(i + row_skip, j + col_skip) += x(i, j);
            }
        }
    }

    void operator+=(const MatrixExpression<TYPE> &x)
    {
        int r = MatrixExpression<TYPE>::nrows;
        int c = MatrixExpression<TYPE>::ncols;
        assert(r == x.Nrows() && c == x.Ncols());
        for (int i = 1; i <= r; ++i)
        {
            for (int j = 1; j <= c; ++j)
            {
                mat_r(i + row_skip, j + col_skip) += x(i, j);
            }
        }
    }

    void operator-=(const TYPE &x)
    {
        int r = MatrixExpression<TYPE>::nrows;
        int c = MatrixExpression<TYPE>::ncols;
        for (int i = 1; i <= r; ++i)
        {
            for (int j = 1; j <= c; ++j)
            {
                mat_r(i + row_skip, j + col_skip) -= x;
            }
        }
    }

    void operator-=(const GeneralMatrix<TYPE> &x)
    {
        int r = MatrixExpression<TYPE>::nrows;
        int c = MatrixExpression<TYPE>::ncols;
        assert(r == x.Nrows() && c == x.Ncols());
        for (int i = 1; i <= r; ++i)
        {
            for (int j = 1; j <= c; ++j)
            {
                mat_r(i + row_skip, j + col_skip) -= x(i, j);
            }
        }
    }

    void operator-=(const MatrixExpression<TYPE> &x)
    {
        int r = MatrixExpression<TYPE>::nrows;
        int c = MatrixExpression<TYPE>::ncols;
        assert(r == x.Nrows() && c == x.Ncols());
        for (int i = 1; i <= r; ++i)
        {
            for (int j = 1; j <= c; ++j)
            {
                mat_r(i + row_skip, j + col_skip) -= x(i, j);
            }
        }
    }

    void SwapRow(const int &r1, const int &r2)
    {
        assert(r1 > 0 && r1 <= MatrixExpression<TYPE>::nrows);
        assert(r2 > 0 && r2 <= MatrixExpression<TYPE>::nrows);
        TYPE t;
        for (int j = 1; j <= MatrixExpression<TYPE>::ncols; ++j)
        {
            t = mat_r(r1 + row_skip, j + col_skip);
            mat_r(r1 + row_skip, j + col_skip) = mat_r(r2 + row_skip, j + col_skip);
            mat_r(r2 + row_skip, j + col_skip) = t;
        }
    }

    void SwapCol(const int &c1, const int &c2)
    {
        assert(r1 > 0 && r1 <= MatrixExpression<TYPE>::nrows);
        assert(r2 > 0 && r2 <= MatrixExpression<TYPE>::nrows);
        TYPE t;
        for (int j = 1; j <= MatrixExpression<TYPE>::nrows; ++j)
        {
            t = mat_r(j + row_skip, c1 + col_skip);
            mat_r(j + row_skip, c1 + col_skip) = mat_r(j + row_skip, c2 + col_skip);
            mat_r(j + row_skip, c2 + col_skip) = t;
        }
    }

    void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
    {
        assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
        MatrixIndex<TYPE> mi1, mi2;
        mat_r.GetRowIndex(r + row_skip, mi1);
        mi1.Shift(-col_skip);

        mi2.Append(1, MatrixExpression<TYPE>::ncols);

        Intersect(mi1, mi2, mi);
    }

    void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
    {
        assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
        MatrixIndex<TYPE> mi1, mi2;
        mat_r.GetRowIndex(c + col_skip, mi1);
        mi1.Shift(-row_skip);

        mi2.Append(1, MatrixExpression<TYPE>::nrows);

        Intersect(mi1, mi2, mi);
    }

    TYPE operator () (const int &r, const int &c) const
    {
        assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
        assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
        int row = r + row_skip;
        int col = c + col_skip;
        return mat_r(row, col);
    }

    TYPE & operator () (const int &r, const int &c)
    {
        assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
        assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
        int row = r + row_skip;
        int col = c + col_skip;
        return mat_r(row, col);
    }
};



// GeneralMatrix
template <typename TYPE>
GetSubMatrix<TYPE, GeneralMatrix<TYPE> > sub(GeneralMatrix<TYPE> & mat, int r1, int r2, int c1, int c2)
{
    assert(r1 > 0 && r2 > 0 && c1 > 0 && c2 > 0 && r1 <= r2 && c1 <= c2);
    assert(r2 <= mat.Nrows() && c2 <= mat.Ncols());
    return GetSubMatrix<TYPE, GeneralMatrix<TYPE> >(mat, r1, r2, c1, c2);
}

//MatrixExpression
template <typename TYPE>
GetSubMatrix<TYPE, MatrixExpression<TYPE> > sub(MatrixExpression<TYPE> & mat, int r1, int r2, int c1, int c2)
{
    assert(r1 > 0 && r2 > 0 && c1 > 0 && c2 > 0 && r1 <= r2 && c1 <= c2);
    assert(r2 <= mat.Nrows() && c2 <= mat.Ncols());
    return GetSubMatrix<TYPE, MatrixExpression<TYPE> >(mat, r1, r2, c1, c2);
}

//BaseMatrix
template <typename TYPE>
GetSubMatrix<TYPE, BaseMatrix<TYPE> > sub(BaseMatrix<TYPE> & mat, int r1, int r2, int c1, int c2)
{
    assert(r1 > 0 && r2 > 0 && c1 > 0 && c2 > 0 && r1 <= r2 && c1 <= c2);
    assert(r2 <= mat.Nrows() && c2 <= mat.Ncols());
    return GetSubMatrix<TYPE, BaseMatrix<TYPE> >(mat, r1, r2, c1, c2);
}

#endif //GETSUB_MATRIX_H

