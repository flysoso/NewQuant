#ifndef KP_MATRIX_H
#define KP_MATRIX_H


#include "MatrixExpression.h"

namespace NewQuant
{
    template<typename TYPE> class MatrixIndex;

    /// Kronecker product of two matrices.
    template<typename TYPE, typename MATRIX1, typename MATRIX2>
    class KPMatrix : public BinaryMatrixExpression < TYPE, MATRIX1, MATRIX2 >
    {
    private:
        int row1;
        int col1;
        int row2;
        int col2;
    public:
        KPMatrix(const MATRIX1 &m1, const MATRIX2 &m2) : BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>(m1, m2)
        {
            row1 = m1.Nrows(), col1 = m1.Ncols();
            row2 = m2.Nrows(), col2 = m2.Ncols();

            MatrixExpression<TYPE>::Set(row1*row2, col1*col2);
            if (MatrixExpression<TYPE>::nrows == MatrixExpression<TYPE>::ncols)
            {
                MatrixExpression<TYPE>::band_width.Set(MatrixExpression<TYPE>::nrows - 1, MatrixExpression<TYPE>::ncols - 1, true);
            }
            else
            {
                MatrixExpression<TYPE>::band_width.Set(-1, -1, false);
            }
        }

        ~KPMatrix() {}

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
            mi.Append(1, MatrixExpression<TYPE>::nrows);
        }

        TYPE operator () (const int &r, const int &c) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            int r1 = (r - 1) / row2 + 1;
            int c1 = (c - 1) / col2 + 1;
            int r2 = (r - 1) % row2 + 1;
            int c2 = (c - 1) % col2 + 1;
            return BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat1(r1, c1) * BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat2(r2, c2);
        }
    };



    // GeneralMatrix
    template<typename TYPE>
    KPMatrix<TYPE, GeneralMatrix<TYPE>, GeneralMatrix<TYPE> > kp(const GeneralMatrix<TYPE> & mat1, const GeneralMatrix<TYPE> & mat2)
    {
        return KPMatrix<TYPE, GeneralMatrix<TYPE>, GeneralMatrix<TYPE> >(mat1, mat2);
    }

    template<typename TYPE>
    KPMatrix<TYPE, GeneralMatrix<TYPE>, MatrixExpression<TYPE> > kp(const GeneralMatrix<TYPE> & mat1, const MatrixExpression<TYPE> & mat2)
    {
        return KPMatrix<TYPE, GeneralMatrix<TYPE>, MatrixExpression<TYPE> >(mat1, mat2);
    }

    // MatrixExpression
    template<typename TYPE>
    KPMatrix<TYPE, MatrixExpression<TYPE>, GeneralMatrix<TYPE> > kp(const MatrixExpression<TYPE> & mat1, const GeneralMatrix<TYPE> & mat2)
    {
        return KPMatrix<TYPE, MatrixExpression<TYPE>, GeneralMatrix<TYPE> >(mat1, mat2);
    }

    template<typename TYPE>
    KPMatrix<TYPE, MatrixExpression<TYPE>, MatrixExpression<TYPE> > kp(const MatrixExpression<TYPE> & mat1, const MatrixExpression<TYPE> & mat2)
    {
        return KPMatrix<TYPE, MatrixExpression<TYPE>, MatrixExpression<TYPE> >(mat1, mat2);
    }

}
#endif //KP_MATRIX_H

