#ifndef GETROWCOL_MATRIX_H
#define GETROWCOL_MATRIX_H

#include "MatrixExpression.h"
#include "VectorExpression.h"

template<typename TYPE> class MatrixIndex;

/// A row or column of a matrix.
template <typename TYPE, typename MATRIX>
class GetRowColMatrix : public UnitaryMatrixExpression < TYPE, MATRIX >, public VectorExpression < TYPE >
{
public:
    enum RowColType { get_row, get_col };
private:
    int row_col;
    int row_skip, col_skip;
    RowColType type;
    /*
    row_col:the row or column of one matrix to get
    */
    MATRIX &mat_r;
public:
    GetRowColMatrix(MATRIX &m, const int &rc, const RowColType &t) : UnitaryMatrixExpression<TYPE, MATRIX>(m), row_col(rc), type(t), mat_r(m)
    {
        switch (type)
        {
        case get_row:
            MatrixExpression<TYPE>::Set(1, m.Ncols());
            VectorExpression<TYPE>::SetLength(m.Ncols());
            row_skip = rc - 1, col_skip = 0;
            break;
        case get_col:
            MatrixExpression<TYPE>::Set(m.Nrows(), 1);
            VectorExpression<TYPE>::SetLength(m.Nrows());
            row_skip = 0, col_skip = rc - 1;
            break;
        }
        if (MatrixExpression<TYPE>::nrows == MatrixExpression<TYPE>::ncols)
        {
            MatrixExpression<TYPE>::band_width.Set(MatrixExpression<TYPE>::nrows - 1, MatrixExpression<TYPE>::nrows - 1, true);
        }
        else
        {
            MatrixExpression<TYPE>::band_width.Set(-1, -1, false);
        }
    }

    ~GetRowColMatrix() {}

    GetRowColMatrix<TYPE, MATRIX> & operator=(const TYPE &x)
    {
        int l;
        switch (type)
        {
        case get_row:
            l = MatrixExpression<TYPE>::ncols;
            for (int i = 1; i <= l; ++i)
            {
                mat_r(row_col, i) = x;
            }
            break;
        case get_col:
            l = MatrixExpression<TYPE>::nrows;
            for (int i = 1; i <= l; ++i)
            {
                mat_r(i, row_col) = x;
            }
            break;
        }
        return *this;
    }

    void operator+=(const TYPE &x)
    {
        int l;
        switch (type)
        {
        case get_row:
            l = MatrixExpression<TYPE>::ncols;
            for (int i = 1; i <= l; ++i)
            {
                mat_r(row_col, i) += x;
            }
            break;
        case get_col:
            l = MatrixExpression<TYPE>::nrows;
            for (int i = 1; i <= l; ++i)
            {
                mat_r(i, row_col) += x;
            }
            break;
        }
    }

    void operator+=(const GeneralMatrix<TYPE> &x)
    {
        int l;
        switch (type)
        {
        case get_row:
            l = MatrixExpression<TYPE>::ncols;
            for (int i = 1; i <= l; ++i)
            {
                mat_r(row_col, i) += x(1, i);
            }
            break;
        case get_col:
            l = MatrixExpression<TYPE>::nrows;
            for (int i = 1; i <= l; ++i)
            {
                mat_r(i, row_col) += x(i, 1);
            }
            break;
        }
    }

    void operator+=(const MatrixExpression<TYPE> &x)
    {
        int l;
        switch (type)
        {
        case get_row:
            l = MatrixExpression<TYPE>::ncols;
            for (int i = 1; i <= l; ++i)
            {
                mat_r(row_col, i) += x(1, i);
            }
            break;
        case get_col:
            l = MatrixExpression<TYPE>::nrows;
            for (int i = 1; i <= l; ++i)
            {
                mat_r(i, row_col) += x(i, 1);
            }
            break;
        }
    }

    void operator-=(const TYPE &x)
    {
        int l;
        switch (type)
        {
        case get_row:
            l = MatrixExpression<TYPE>::ncols;
            for (int i = 1; i <= l; ++i)
            {
                mat_r(row_col, i) -= x;
            }
            break;
        case get_col:
            l = MatrixExpression<TYPE>::nrows;
            for (int i = 1; i <= l; ++i)
            {
                mat_r(i, row_col) -= x;
            }
            break;
        }
    }

    void operator-=(const GeneralMatrix<TYPE> &x)
    {
        int l;
        switch (type)
        {
        case get_row:
            l = MatrixExpression<TYPE>::ncols;
            for (int i = 1; i <= l; ++i)
            {
                mat_r(row_col, i) -= x(1, i);
            }
            break;
        case get_col:
            l = MatrixExpression<TYPE>::nrows;
            for (int i = 1; i <= l; ++i)
            {
                mat_r(i, row_col) -= x(i, 1);
            }
            break;
        }
    }

    void operator-=(const MatrixExpression<TYPE> &x)
    {
        int l;
        switch (type)
        {
        case get_row:
            l = MatrixExpression<TYPE>::ncols;
            for (int i = 1; i <= l; ++i)
            {
                mat_r(row_col, i) -= x(1, i);
            }
            break;
        case get_col:
            l = MatrixExpression<TYPE>::nrows;
            for (int i = 1; i <= l; ++i)
            {
                mat_r(i, row_col) -= x(i, 1);
            }
            break;
        }
    }

    void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
    {
        assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
        switch (type)
        {
        case get_row:
            UnitaryMatrixExpression<TYPE, MATRIX>::mat.GetRowIndex(row_col, mi);
            break;
        case get_col:
            mi.Clear();
            mi.Append(1, 1);
            break;
        }
    }

    void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
    {
        assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
        switch (type)
        {
        case get_row:
            mi.Clear();
            mi.Append(1, 1);
            break;
        case get_col:
            UnitaryMatrixExpression<TYPE, MATRIX>::mat.GetColIndex(row_col, mi);
            break;
        }
    }

    TYPE operator () (const int &r, const int &c) const
    {
        assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
        assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
        switch (type)
        {
        case get_row:
            return mat_r(row_col, c);
        case get_col:
            return mat_r(r, row_col);
        }
    }

    TYPE & operator () (const int &r, const int &c)
    {
        assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
        assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
        switch (type)
        {
        case get_row:
            return mat_r(row_col, c);
        case get_col:
            return mat_r(r, row_col);
        }
    }

    TYPE operator () (const int &i) const
    {
        switch (type)
        {
        case get_row:
            assert(i > 0 && i <= MatrixExpression<TYPE>::ncols);
            return mat_r(row_col, i);
        case get_col:
            assert(i > 0 && i <= MatrixExpression<TYPE>::nrows);
            return mat_r(i, row_col);
        }
    }

    TYPE & operator () (const int &i)
    {
        switch (type)
        {
        case get_row:
            assert(i > 0 && i <= MatrixExpression<TYPE>::ncols);
            return mat_r(row_col, i);
        case get_col:
            assert(i > 0 && i <= MatrixExpression<TYPE>::nrows);
            return mat_r(i, row_col);
        }
    }

    void SwapRow(const int &r1, const int &r2)
    {
        assert(r1 > 0 && r1 <= MatrixExpression<TYPE>::nrows);
        assert(r2 > 0 && r2 <= MatrixExpression<TYPE>::nrows);
        assert(c1 > 0 && c1 <= MatrixExpression<TYPE>::ncols);
        assert(c2 > 0 && c2 <= MatrixExpression<TYPE>::ncols);
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
        assert(c1 > 0 && c1 <= MatrixExpression<TYPE>::ncols);
        assert(c2 > 0 && c2 <= MatrixExpression<TYPE>::ncols);
        TYPE t;
        for (int j = 1; j <= MatrixExpression<TYPE>::nrows; ++j)
        {
            t = mat_r(j + row_skip, c1 + col_skip);
            mat_r(j + row_skip, c1 + col_skip) = mat_r(j + row_skip, c2 + col_skip);
            mat_r(j + row_skip, c2 + col_skip) = t;
        }
    }

    int Search(const GeneralMatrix<TYPE> &gm) const
    {
        return mat_r.Search(gm);
    }
};


// GeneralMatrix
template <typename TYPE>
GetRowColMatrix<TYPE, GeneralMatrix<TYPE> > row(GeneralMatrix<TYPE> & mat, const int &r)
{
    assert(r > 0 && r <= mat.Nrows());
    return GetRowColMatrix<TYPE, GeneralMatrix<TYPE> >(mat, r, GetRowColMatrix<TYPE, GeneralMatrix<TYPE> >::RowColType::get_row);
}

// MatrixExpression
template <typename TYPE>
GetRowColMatrix<TYPE, MatrixExpression<TYPE> > row(MatrixExpression<TYPE> & mat, const int &r)
{
    assert(r > 0 && r <= mat.Nrows());
    return GetRowColMatrix<TYPE, MatrixExpression<TYPE> >(mat, r, GetRowColMatrix<TYPE, MatrixExpression<TYPE> >::RowColType::get_row);
}

// GeneralMatrix
template <typename TYPE>
GetRowColMatrix<TYPE, GeneralMatrix<TYPE> > col(GeneralMatrix<TYPE> & mat, const int &c)
{
    assert(c > 0 && c <= mat.Ncols());
    return GetRowColMatrix<TYPE, GeneralMatrix<TYPE> >(mat, c, GetRowColMatrix<TYPE, GeneralMatrix<TYPE> >::RowColType::get_col);
}

// MatrixExpression
template <typename TYPE>
GetRowColMatrix<TYPE, MatrixExpression<TYPE> > col(MatrixExpression<TYPE> & mat, const int &c)
{
    assert(c > 0 && c <= mat.Ncols());
    return GetRowColMatrix<TYPE, MatrixExpression<TYPE> >(mat, c, GetRowColMatrix<TYPE, MatrixExpression<TYPE> >::RowColType::get_col);
}


#endif //GETROWCOL_MATRIX_H

