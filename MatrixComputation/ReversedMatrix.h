#ifndef REVERSED_MATRIX_H
#define REVERSED_MATRIX_H


#include "MatrixExpression.h"

template<typename TYPE> class MatrixIndex;

/// Any type of matrix with order of elements reversed.
template <typename TYPE, typename MATRIX>
class ReversedMatrix : public UnitaryMatrixExpression < TYPE, MATRIX >
{
public:
    enum ReversedType { rev_by_r = 1, rev_by_c = 2 };
private:
    ReversedType type;
public:
    ReversedMatrix(const MATRIX &m, const ReversedType &t) : UnitaryMatrixExpression<TYPE, MATRIX>(m), type(t)
    {
        MatrixExpression<TYPE>::Set(m.Nrows(), m.Ncols());
        if (MatrixExpression<TYPE>::nrows == MatrixExpression<TYPE>::ncols)
        {
            MatrixExpression<TYPE>::band_width.Set(MatrixExpression<TYPE>::nrows - 1, MatrixExpression<TYPE>::nrows - 1, true);
        }
        else
        {
            MatrixExpression<TYPE>::band_width.Set(-1, -1, false);
        }
    }

    ~ReversedMatrix() {}

    void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
    {
        assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
        switch (type)
        {
        case rev_by_r:
            int row = MatrixExpression<TYPE>::nrows + 1 - r;
            UnitaryMatrixExpression<TYPE, MATRIX>::mat.GetRowIndex(row, mi);
            break;
        case rev_by_c:
            MatrixIndex<TYPE> mit;
            UnitaryMatrixExpression<TYPE, MATRIX>::mat.GetRowIndex(r, mit);

            int s = mit.Size();
            mi.Resize(s);
            int left, right;
            for (int i = s - 1; i >= 0; --i)
            {
                left = MatrixExpression<TYPE>::ncols + 1 - mit.GetIndexList()[i].GetRight().GetPoint();
                right = MatrixExpression<TYPE>::ncols + 1 - mit.GetIndexList()[i].GetLeft().GetPoint();
                mi.GetIndexList()[s - 1 - i].SetLeft(left);
                mi.GetIndexList()[s - 1 - i].SetRight(right);
            }
            break;
        }
    }

    void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
    {
        assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
        switch (type)
        {
        case rev_by_r:
            MatrixIndex<TYPE> mit;
            UnitaryMatrixExpression<TYPE, MATRIX>::mat.GetColIndex(c, mit);

            int s = mit.Size();
            mi.Resize(mit.Size());
            int left, right;
            for (int i = s - 1; i >= 0; --i)
            {
                left = MatrixExpression<TYPE>::nrows + 1 - mit.GetIndexList()[i].GetRight().GetPoint();
                right = MatrixExpression<TYPE>::nrows + 1 - mit.GetIndexList()[i].GetLeft().GetPoint();
                mi.GetIndexList()[s - 1 - i].SetLeft(left);
                mi.GetIndexList()[s - 1 - i].SetRight(right);
            }
            break;
        case rev_by_c:
            int col = MatrixExpression<TYPE>::ncols + 1 - c;
            UnitaryMatrixExpression<TYPE, MATRIX>::mat.GetColIndex(col, mi);
            break;
        }
    }

    TYPE operator () (const int &r, const int &c) const
    {
        assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
        assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
        int row, col;
        switch (type)
        {
        case rev_by_r:
            row = MatrixExpression<TYPE>::nrows + 1 - r;
            col = c;
            return UnitaryMatrixExpression<TYPE, MATRIX>::mat(row, col);
            break;
        case rev_by_c:
            row = r;
            col = MatrixExpression<TYPE>::ncols + 1 - c;
            return UnitaryMatrixExpression<TYPE, MATRIX>::mat(row, col);
            break;
        }
    }
};


// GeneralMatrix
template <typename TYPE>
ReversedMatrix<TYPE, GeneralMatrix<TYPE> > reverse_by_row(const GeneralMatrix<TYPE> & mat)
{
    return ReversedMatrix<TYPE, GeneralMatrix<TYPE> >(mat, ReversedMatrix<TYPE, GeneralMatrix<TYPE> >::ReversedType::rev_by_r);
}

// MatrixExpression
template <typename TYPE>
ReversedMatrix<TYPE, MatrixExpression<TYPE> > reverse_by_row(const MatrixExpression<TYPE> & mat)
{
    return ReversedMatrix<TYPE, MatrixExpression<TYPE> >(mat, ReversedMatrix<TYPE, MatrixExpression<TYPE> >::ReversedType::rev_by_r);
}

// GeneralMatrix
template <typename TYPE>
ReversedMatrix<TYPE, GeneralMatrix<TYPE> > reverse_by_col(const GeneralMatrix<TYPE> & mat)
{
    return ReversedMatrix<TYPE, GeneralMatrix<TYPE> >(mat, ReversedMatrix<TYPE, GeneralMatrix<TYPE> >::ReversedType::rev_by_c);
}

// MatrixExpression
template <typename TYPE>
ReversedMatrix<TYPE, MatrixExpression<TYPE> > reverse_by_col(const MatrixExpression<TYPE> & mat)
{
    return ReversedMatrix<TYPE, MatrixExpression<TYPE> >(mat, ReversedMatrix<TYPE, MatrixExpression<TYPE> >::ReversedType::rev_by_c);
}


#endif //REVERSED_MATRIX_H

