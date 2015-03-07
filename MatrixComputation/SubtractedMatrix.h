#ifndef SUBTRACTED_MATRIX_H
#define SUBTRACTED_MATRIX_H

#include "MatrixExpression.h"

namespace NewQuant
{
    template<typename TYPE> class MatrixIndex;

    /// Difference between two matrices.
    template<typename TYPE, typename MATRIX1, typename MATRIX2>
    class SubtractedMatrix : public BinaryMatrixExpression < TYPE, MATRIX1, MATRIX2 >
    {
    public:
        SubtractedMatrix(const MATRIX1 &m1, const MATRIX2 &m2) : BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>(m1, m2)
        {
            MatrixExpression<TYPE>::Set(m1.Nrows(), m1.Ncols());
            MatrixExpression<TYPE>::band_width = m1.BandWidth() + m2.BandWidth();
        }

        ~SubtractedMatrix() {}

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            MatrixIndex<TYPE> mi1, mi2;
            BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat1.GetRowIndex(r, mi1);
            BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat2.GetRowIndex(r, mi2);
            Union(mi1, mi2, mi);
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            MatrixIndex<TYPE> mi1, mi2;
            BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat1.GetColIndex(c, mi1);
            BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat2.GetColIndex(c, mi2);
            Union(mi1, mi2, mi);
        }

        TYPE operator () (const int &r, const int &c) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            return BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat1(r, c) - BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat2(r, c);
        }
    };

    // GeneralMatrix
    template<typename TYPE>
    SubtractedMatrix<TYPE, GeneralMatrix<TYPE>, GeneralMatrix<TYPE> > operator - (const GeneralMatrix<TYPE> & mat1, const GeneralMatrix<TYPE> & mat2)
    {
        assert(mat1.Nrows() == mat2.Nrows() && mat1.Ncols() == mat2.Ncols());
        return SubtractedMatrix<TYPE, GeneralMatrix<TYPE>, GeneralMatrix<TYPE> >(mat1, mat2);
    }

    template<typename TYPE>
    SubtractedMatrix<TYPE, GeneralMatrix<TYPE>, MatrixExpression<TYPE> > operator - (const GeneralMatrix<TYPE> & mat1, const MatrixExpression<TYPE> & mat2)
    {
        assert(mat1.Nrows() == mat2.Nrows() && mat1.Ncols() == mat2.Ncols());
        return SubtractedMatrix<TYPE, GeneralMatrix<TYPE>, MatrixExpression<TYPE> >(mat1, mat2);
    }

    // MatrixExpression
    template<typename TYPE>
    SubtractedMatrix<TYPE, MatrixExpression<TYPE>, GeneralMatrix<TYPE> > operator - (const MatrixExpression<TYPE> & mat1, const GeneralMatrix<TYPE> & mat2)
    {
        assert(mat1.Nrows() == mat2.Nrows() && mat1.Ncols() == mat2.Ncols());
        return SubtractedMatrix<TYPE, MatrixExpression<TYPE>, GeneralMatrix<TYPE> >(mat1, mat2);
    }

    template<typename TYPE>
    SubtractedMatrix<TYPE, MatrixExpression<TYPE>, MatrixExpression<TYPE> > operator - (const MatrixExpression<TYPE> & mat1, const MatrixExpression<TYPE> & mat2)
    {
        assert(mat1.Nrows() == mat2.Nrows() && mat1.Ncols() == mat2.Ncols());
        return SubtractedMatrix<TYPE, MatrixExpression<TYPE>, MatrixExpression<TYPE> >(mat1, mat2);
    }
}

#endif //SUBTRACTED_MATRIX_H

