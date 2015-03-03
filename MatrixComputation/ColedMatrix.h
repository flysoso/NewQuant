#ifndef COLED_MATRIX_H
#define COLED_MATRIX_H


#include "MatrixExpression.h"

template<typename TYPE> class MatrixIndex;

/// Any type of matrix interpreted as a ColumnVector.
template <typename TYPE, typename MATRIX>
class ColedMatrix : public UnitaryMatrixExpression < TYPE, MATRIX >
{
private:
    int row_num;
public:
    ColedMatrix(const MATRIX &m) : UnitaryMatrixExpression<TYPE, MATRIX>(m), row_num(m.Nrows())
    {
        MatrixExpression<TYPE>::Set(m.Nrows() * m.Ncols(), 1);
        if (MatrixExpression<TYPE>::nrows == 1)
        {
            MatrixExpression<TYPE>::band_width.Set(0, 0, true);
        }
        else
        {
            MatrixExpression<TYPE>::band_width.Set(-1, -1, false);
        }
    }

    ~ColedMatrix() {}

    void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
    {
        assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
        mi.Clear();
        mi.Append(1, 1);
    }

    void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
    {
        assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
        mi.Clear();
        mi.Append(1, MatrixExpression<TYPE>::nrows);
    }

    TYPE operator () (const int &r, const int &c) const
    {
        assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
        assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
        int row = (r - 1) % row_num + 1;
        int col = (r - 1) / row_num + 1;
        return UnitaryMatrixExpression<TYPE, MATRIX>::mat(row, col);
    }
};

// GeneralMatrix
template <typename TYPE>
ColedMatrix<TYPE, GeneralMatrix<TYPE> > as_col(const GeneralMatrix<TYPE> & mat)
{
    return ColedMatrix<TYPE, GeneralMatrix<TYPE> >(mat);
}

// MatrixExpression
template <typename TYPE>
ColedMatrix<TYPE, MatrixExpression<TYPE> > as_col(const MatrixExpression<TYPE> & mat)
{
    return ColedMatrix<TYPE, MatrixExpression<TYPE> >(mat);
}

#endif //COLED_MATRIX_H

