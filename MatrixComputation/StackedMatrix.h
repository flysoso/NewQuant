#ifndef STACKED_MATRIX_H
#define STACKED_MATRIX_H

#include "MatrixExpression.h"

namespace NewQuant
{
    template<typename TYPE> class MatrixIndex;

    /// Two matrices vertically concatenated.
    template <typename TYPE, typename MATRIX1, typename MATRIX2>
    class StackedMatrix : public BinaryMatrixExpression < TYPE, MATRIX1, MATRIX2 >
    {
    private:
        int row;//the number of rows of the first matrix
    public:
        StackedMatrix(const MATRIX1 &m1, const MATRIX2 &m2) : BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>(m1, m2)
        {
            row = m1.Nrows();
            MatrixExpression<TYPE>::Set(m1.Nrows() + m2.Nrows(), m1.Ncols());
            if (MatrixExpression<TYPE>::nrows == MatrixExpression<TYPE>::ncols)
            {
                MatrixExpression<TYPE>::band_width.Set(MatrixExpression<TYPE>::nrows - 1, MatrixExpression<TYPE>::ncols - 1, true);
            }
            else
            {
                MatrixExpression<TYPE>::band_width.Set(-1, -1, false);
            }
        }

        ~StackedMatrix() {}

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            if (r <= row)
            {
                BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat1.GetRowIndex(r, mi);
            }
            else
            {
                BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat2.GetRowIndex(r - row, mi);
                mi.Shift(row);
            }
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            MatrixIndex<TYPE> mit;
            BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat1.GetColIndex(c, mi);
            BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat2.GetColIndex(c, mit);

            mit.Shift(row);
            mi.GetIndexList().insert(mi.GetIndexList().end(), mit.GetIndexList().begin(), mit.GetIndexList().end());
        }

        TYPE operator () (const int &r, const int &c) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            if (r <= row)
                return BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat1(r, c);
            else
                return BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat2(r - row, c);
        }
    };


    // GeneralMatrix
    template <typename TYPE>
    StackedMatrix<TYPE, GeneralMatrix<TYPE>, GeneralMatrix<TYPE> > operator & (const GeneralMatrix<TYPE> & mat1, const GeneralMatrix<TYPE> & mat2)
    {
        assert(mat1.Ncols() == mat2.Ncols());
        return StackedMatrix<TYPE, GeneralMatrix<TYPE>, GeneralMatrix<TYPE> >(mat1, mat2);
    }

    template <typename TYPE>
    StackedMatrix<TYPE, GeneralMatrix<TYPE>, MatrixExpression<TYPE> > operator & (const GeneralMatrix<TYPE> & mat1, const MatrixExpression<TYPE> & mat2)
    {
        assert(mat1.Ncols() == mat2.Ncols());
        return StackedMatrix<TYPE, GeneralMatrix<TYPE>, MatrixExpression<TYPE> >(mat1, mat2);
    }

    // MatrixExpression
    template <typename TYPE>
    StackedMatrix<TYPE, MatrixExpression<TYPE>, GeneralMatrix<TYPE> > operator & (const MatrixExpression<TYPE> & mat1, const GeneralMatrix<TYPE> & mat2)
    {
        assert(mat1.Ncols() == mat2.Ncols());
        return StackedMatrix<TYPE, MatrixExpression<TYPE>, GeneralMatrix<TYPE> >(mat1, mat2);
    }

    template <typename TYPE>
    StackedMatrix<TYPE, MatrixExpression<TYPE>, MatrixExpression<TYPE> > operator & (const MatrixExpression<TYPE> & mat1, const MatrixExpression<TYPE> & mat2)
    {
        assert(mat1.Ncols() == mat2.Ncols());
        return StackedMatrix<TYPE, MatrixExpression<TYPE>, MatrixExpression<TYPE> >(mat1, mat2);
    }
}
#endif //STACKED_MATRIX_H


