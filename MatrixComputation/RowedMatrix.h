#ifndef ROWED_MATRIX_H
#define ROWED_MATRIX_H

#include "MatrixExpression.h"

namespace NewQuant
{
    template<typename TYPE> class MatrixIndex;

    /// Any type of matrix interpreted as a RowVector.
    template <typename TYPE, typename MATRIX>
    class RowedMatrix : public UnitaryMatrixExpression < TYPE, MATRIX >
    {
    public:
        RowedMatrix(const MATRIX &m) : UnitaryMatrixExpression<TYPE, MATRIX>(m)
        {
            MatrixExpression<TYPE>::Set(1, m.Nrows() * m.Ncols());
            if (MatrixExpression<TYPE>::nrows == 1)
            {
                MatrixExpression<TYPE>::band_width.Set(0, 0, true);
            }
            else
            {
                MatrixExpression<TYPE>::band_width.Set(-1, -1, false);
            }
        }

        ~RowedMatrix() {}

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            mi.Clear();
            mi.Append(1, MatrixExpression<TYPE>::ncols);
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            mi.Clear();
            mi.Append(1, 1);
        }

        TYPE operator () (const int &r, const int &c) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            int row = (c - 1) / UnitaryMatrixExpression<TYPE, MATRIX>::mat.Ncols() + 1;
            int col = (c - 1) % UnitaryMatrixExpression<TYPE, MATRIX>::mat.Ncols() + 1;
            return UnitaryMatrixExpression<TYPE, MATRIX>::mat(row, col);
        }
    };


    // GeneralMatrix
    template <typename TYPE>
    RowedMatrix<TYPE, GeneralMatrix<TYPE> > as_row(const GeneralMatrix<TYPE> & mat)
    {
        return RowedMatrix<TYPE, GeneralMatrix<TYPE> >(mat);
    }

    // MatrixExpression
    template <typename TYPE>
    RowedMatrix<TYPE, MatrixExpression<TYPE> > as_row(const MatrixExpression<TYPE> & mat)
    {
        return RowedMatrix<TYPE, MatrixExpression<TYPE> >(mat);
    }
}

#endif //ROWED_MATRIX_H


