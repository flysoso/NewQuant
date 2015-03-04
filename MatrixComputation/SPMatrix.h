#ifndef SP_MATRIX_H
#define SP_MATRIX_H


#include "MatrixExpression.h"

namespace NewQuant
{
    template<typename TYPE> class MatrixIndex;

    /// Schur (elementwise) product of two matrices.
    template <typename TYPE, typename MATRIX1, typename MATRIX2>
    class SPMatrix : public BinaryMatrixExpression < TYPE, MATRIX1, MATRIX2 >
    {
    public:
        SPMatrix(const MATRIX1 &m1, const MATRIX2 &m2) : BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>(m1, m2)
        {
            MatrixExpression<TYPE>::Set(m1.Nrows(), m1.Ncols());

            if (m1.BandWidth().Evalued() && m1.BandWidth().Evalued())
            {
                MatrixExpression<TYPE>::band_width.SetLower(std::min(m1.BandWidth().Lower(), m2.BandWidth().Lower()));
                MatrixExpression<TYPE>::band_width.SetUpper(std::min(m1.BandWidth().Upper(), m2.BandWidth().Upper()));
                MatrixExpression<TYPE>::band_width.SetEvalued(true);
            }
            else
            {
                MatrixExpression<TYPE>::band_width.Set(-1, -1, false);
            }
        }

        ~SPMatrix() {}

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            MatrixIndex<TYPE> mi1, mi2;
            BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat1.GetRowIndex(r, mi1);
            BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat2.GetRowIndex(r, mi2);
            Intersect(mi1, mi2, mi);
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            MatrixIndex<TYPE> mi1, mi2;
            BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat1.GetColIndex(c, mi1);
            BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat2.GetColIndex(c, mi2);
            Intersect(mi1, mi2, mi);
        }

        TYPE operator () (const int &r, const int &c) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            return BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat1(r, c) * BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat2(r, c);
        }
    };



    // GeneralMatrix
    template <typename TYPE>
    SPMatrix<TYPE, GeneralMatrix<TYPE>, GeneralMatrix<TYPE> > sp(const GeneralMatrix<TYPE> & mat1, const GeneralMatrix<TYPE> & mat2)
    {
        assert(mat1.Nrows() == mat2.Nrows() && mat1.Ncols() == mat2.Ncols());
        return SPMatrix<TYPE, GeneralMatrix<TYPE>, GeneralMatrix<TYPE> >(mat1, mat2);
    }

    template <typename TYPE>
    SPMatrix<TYPE, GeneralMatrix<TYPE>, MatrixExpression<TYPE> > sp(const GeneralMatrix<TYPE> & mat1, const MatrixExpression<TYPE> & mat2)
    {
        assert(mat1.Nrows() == mat2.Nrows() && mat1.Ncols() == mat2.Ncols());
        return SPMatrix<TYPE, GeneralMatrix<TYPE>, MatrixExpression<TYPE> >(mat1, mat2);
    }

    // MatrixExpression
    template <typename TYPE>
    SPMatrix<TYPE, MatrixExpression<TYPE>, GeneralMatrix<TYPE> > sp(const MatrixExpression<TYPE> & mat1, const GeneralMatrix<TYPE> & mat2)
    {
        assert(mat1.Nrows() == mat2.Nrows() && mat1.Ncols() == mat2.Ncols());
        return SPMatrix<TYPE, MatrixExpression<TYPE>, GeneralMatrix<TYPE> >(mat1, mat2);
    }

    template <typename TYPE>
    SPMatrix<TYPE, MatrixExpression<TYPE>, MatrixExpression<TYPE> > sp(const MatrixExpression<TYPE> & mat1, const MatrixExpression<TYPE> & mat2)
    {
        assert(mat1.Nrows() == mat2.Nrows() && mat1.Ncols() == mat2.Ncols());
        return SPMatrix<TYPE, MatrixExpression<TYPE>, MatrixExpression<TYPE> >(mat1, mat2);
    }
}
#endif //SP_MATRIX_H

