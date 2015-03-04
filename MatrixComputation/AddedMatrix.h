#ifndef ADDED_MATRIX_H
#define ADDED_MATRIX_H

#include "MatrixExpression.h"

namespace NewQuant
{
    template<typename TYPE> class MatrixIndex;

    /// Sum of two matrices.
    template <typename TYPE, typename MATRIX1, typename MATRIX2>
    class AddedMatrix : public BinaryMatrixExpression < TYPE, MATRIX1, MATRIX2 >
    {
    private:
        AddedMatrix<TYPE, MATRIX1, MATRIX2> & operator = (const AddedMatrix<TYPE, MATRIX1, MATRIX2> &);

    public:
        AddedMatrix(const MATRIX1 &m1, const MATRIX2 &m2) : BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>(m1, m2)
        {
            MatrixExpression<TYPE>::Set(m1.Nrows(), m1.Ncols());
            MatrixExpression<TYPE>::band_width = m1.BandWidth() + m2.BandWidth();
        }

        ~AddedMatrix() {}

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            MatrixIndex<TYPE> mi1, mi2;
            BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat1.GetRowIndex(r, mi1);
            BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat2.GetRowIndex(r, mi2);
            Union(mi1, mi2, mi);
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            MatrixIndex<TYPE> mi1, mi2;
            BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat1.GetColIndex(c, mi1);
            BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat2.GetColIndex(c, mi2);
            Union(mi1, mi2, mi);
        }

        TYPE operator () (const int &r, const int &c) const
        {
            return BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat1(r, c) + BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat2(r, c);
        }
    };


    // GeneralMatrix
    template <typename TYPE>
    AddedMatrix<TYPE, GeneralMatrix<TYPE>, GeneralMatrix<TYPE> > operator + (const GeneralMatrix<TYPE> & mat1, const GeneralMatrix<TYPE> & mat2)
    {
        assert(mat1.Nrows() == mat2.Nrows() && mat1.Ncols() == mat2.Ncols());
        return AddedMatrix<TYPE, GeneralMatrix<TYPE>, GeneralMatrix<TYPE> >(mat1, mat2);
    }

    template <typename TYPE>
    AddedMatrix<TYPE, GeneralMatrix<TYPE>, MatrixExpression<TYPE> > operator + (const GeneralMatrix<TYPE> & mat1, const MatrixExpression<TYPE> & mat2)
    {
        assert(mat1.Nrows() == mat2.Nrows() && mat1.Ncols() == mat2.Ncols());
        return AddedMatrix<TYPE, GeneralMatrix<TYPE>, MatrixExpression<TYPE> >(mat1, mat2);
    }

    // MatrixExpression
    template <typename TYPE>
    AddedMatrix<TYPE, MatrixExpression<TYPE>, GeneralMatrix<TYPE> > operator + (const MatrixExpression<TYPE> & mat1, const GeneralMatrix<TYPE> & mat2)
    {
        assert(mat1.Nrows() == mat2.Nrows() && mat1.Ncols() == mat2.Ncols());
        return AddedMatrix<TYPE, MatrixExpression<TYPE>, GeneralMatrix<TYPE> >(mat1, mat2);
    }

    template <typename TYPE>
    AddedMatrix<TYPE, MatrixExpression<TYPE>, MatrixExpression<TYPE> > operator + (const MatrixExpression<TYPE> & mat1, const MatrixExpression<TYPE> & mat2)
    {
        assert(mat1.Nrows() == mat2.Nrows() && mat1.Ncols() == mat2.Ncols());
        return AddedMatrix<TYPE, MatrixExpression<TYPE>, MatrixExpression<TYPE> >(mat1, mat2);
    }
}
#endif //ADDED_MATRIX_H

