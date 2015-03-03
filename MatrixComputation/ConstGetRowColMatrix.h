#ifndef CONSTGETROWCOL_MATRIX_H
#define CONSTGETROWCOL_MATRIX_H

#include "MatrixExpression.h"
#include "VectorExpression.h"

template<typename TYPE> class MatrixIndex;

/// A row or column of a matrix.
template <typename TYPE, typename MATRIX>
class ConstGetRowColMatrix : public UnitaryMatrixExpression < TYPE, MATRIX >, public VectorExpression < TYPE >
{
public:
    enum RowColType { get_row, get_col };
private:
    int row_col;
    RowColType type;
    /*
    row_col:the row or column of one matrix to get
    */
public:
    ConstGetRowColMatrix(const MATRIX &m, const int &rc, const RowColType &t) : UnitaryMatrixExpression<TYPE, MATRIX>(m), row_col(rc), type(t)
    {
        switch (type)
        {
        case get_row:
            MatrixExpression<TYPE>::Set(1, m.Ncols());
            VectorExpression<TYPE>::SetLength(m.Ncols());
            break;
        case get_col:
            MatrixExpression<TYPE>::Set(m.Nrows(), 1);
            VectorExpression<TYPE>::SetLength(m.Nrows());
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

    ~ConstGetRowColMatrix() {}

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
            return UnitaryMatrixExpression<TYPE, MATRIX>::mat(row_col, c);
        case get_col:
            return UnitaryMatrixExpression<TYPE, MATRIX>::mat(r, row_col);
        }
    }

    TYPE operator () (const int &i) const
    {
        assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
        assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
        switch (type)
        {
        case get_row:
            return UnitaryMatrixExpression<TYPE, MATRIX>::mat(row_col, i);
        case get_col:
            return UnitaryMatrixExpression<TYPE, MATRIX>::mat(i, row_col);
        }
    }
};



// GeneralMatrix
template <typename TYPE>
ConstGetRowColMatrix<TYPE, GeneralMatrix<TYPE> > c_row(const GeneralMatrix<TYPE> & mat, const int &r)
{
    assert(r > 0 && r <= mat.Nrows());
    return ConstGetRowColMatrix<TYPE, GeneralMatrix<TYPE> >(mat, r, ConstGetRowColMatrix<TYPE, GeneralMatrix<TYPE> >::RowColType::get_row);
}

// MatrixExpression
template <typename TYPE>
ConstGetRowColMatrix<TYPE, MatrixExpression<TYPE> > c_row(const MatrixExpression<TYPE> & mat, const int &r)
{
    assert(r > 0 && r <= mat.Nrows());
    return ConstGetRowColMatrix<TYPE, MatrixExpression<TYPE> >(mat, r, ConstGetRowColMatrix<TYPE, MatrixExpression<TYPE> >::RowColType::get_row);
}

// GeneralMatrix
template <typename TYPE>
ConstGetRowColMatrix<TYPE, GeneralMatrix<TYPE> > c_col(const GeneralMatrix<TYPE> & mat, const int &c)
{
    assert(c > 0 && c <= mat.Nrows());
    return ConstGetRowColMatrix<TYPE, GeneralMatrix<TYPE> >(mat, c, ConstGetRowColMatrix<TYPE, GeneralMatrix<TYPE> >::RowColType::get_col);
}

// MatrixExpression
template <typename TYPE>
ConstGetRowColMatrix<TYPE, MatrixExpression<TYPE> > c_col(const MatrixExpression<TYPE> & mat, const int &c)
{
    assert(c > 0 && c <= mat.Nrows());
    return ConstGetRowColMatrix<TYPE, MatrixExpression<TYPE> >(mat, c, ConstGetRowColMatrix<TYPE, MatrixExpression<TYPE> >::RowColType::get_col);
}


#endif //CONSTGETROWCOL_MATRIX_H

