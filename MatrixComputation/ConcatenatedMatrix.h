#ifndef CONCATENAED_MATRIX_H
#define CONCATENAED_MATRIX_H

#include "MatrixExpression.h"

namespace NewQuant
{
    template<typename TYPE> class MatrixIndex;

    /// Two matrices horizontally concatenated.
    template <typename TYPE, typename MATRIX1, typename MATRIX2>
    class ConcatenatedMatrix : public BinaryMatrixExpression < TYPE, MATRIX1, MATRIX2 >
    {
    private:
        int col;//the number of columns of the first matrix
    public:
        ConcatenatedMatrix(const MATRIX1 &m1, const MATRIX2 &m2) : BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>(m1, m2)
        {
            MatrixExpression<TYPE>::Set(m1.Nrows(), m1.Ncols() + m2.Ncols());
            col = BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat1.Ncols();

            if (MatrixExpression<TYPE>::nrows == MatrixExpression<TYPE>::ncols)
            {
                MatrixExpression<TYPE>::band_width.Set(MatrixExpression<TYPE>::nrows - 1, MatrixExpression<TYPE>::ncols - 1, true);
            }
            else
            {
                MatrixExpression<TYPE>::band_width.Set(-1, -1, false);
            }
        }

        ~ConcatenatedMatrix() {}

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            MatrixIndex<TYPE> mit;
            BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat1.GetRowIndex(r, mi);
            BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat2.GetRowIndex(r, mit);

            mit.Shift(col);
            mi.GetIndexList().insert(mi.GetIndexList().end(), mit.GetIndexList().begin(), mit.GetIndexList().end());
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            if (c <= col)
            {
                BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat1.GetColIndex(c, mi);
            }
            else
            {
                BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat2.GetColIndex(c - col, mi);
                mi.Shift(col);
            }
        }

        TYPE operator () (const int &r, const int &c) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            if (c <= col)
                return BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat1(r, c);
            else
                return BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat2(r, c - col);
        }
    };

    // GeneralMatrix
    template <typename TYPE>
    ConcatenatedMatrix<TYPE, GeneralMatrix<TYPE>, GeneralMatrix<TYPE> > operator | (const GeneralMatrix<TYPE> & mat1, const GeneralMatrix<TYPE> & mat2)
    {
        assert(mat1.Nrows() == mat2.Nrows());
        return ConcatenatedMatrix<TYPE, GeneralMatrix<TYPE>, GeneralMatrix<TYPE> >(mat1, mat2);
    }

    template <typename TYPE>
    ConcatenatedMatrix<TYPE, GeneralMatrix<TYPE>, MatrixExpression<TYPE> > operator | (const GeneralMatrix<TYPE> & mat1, const MatrixExpression<TYPE> & mat2)
    {
        assert(mat1.Nrows() == mat2.Nrows());
        return ConcatenatedMatrix<TYPE, GeneralMatrix<TYPE>, MatrixExpression<TYPE> >(mat1, mat2);
    }

    // MatrixExpression
    template <typename TYPE>
    ConcatenatedMatrix<TYPE, MatrixExpression<TYPE>, GeneralMatrix<TYPE> > operator | (const MatrixExpression<TYPE> & mat1, const GeneralMatrix<TYPE> & mat2)
    {
        assert(mat1.Nrows() == mat2.Nrows());
        return ConcatenatedMatrix<TYPE, MatrixExpression<TYPE>, GeneralMatrix<TYPE> >(mat1, mat2);
    }

    template <typename TYPE>
    ConcatenatedMatrix<TYPE, MatrixExpression<TYPE>, MatrixExpression<TYPE> > operator | (const MatrixExpression<TYPE> & mat1, const MatrixExpression<TYPE> & mat2)
    {
        assert(mat1.Nrows() == mat2.Nrows());
        return ConcatenatedMatrix<TYPE, MatrixExpression<TYPE>, MatrixExpression<TYPE> >(mat1, mat2);
    }
}

#endif //CONCATENAED_MATRIX_H

