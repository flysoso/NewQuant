#ifndef INV_SCALED_MATRIX_H
#define INV_SCALED_MATRIX_H

#include "MatrixExpression.h"

namespace NewQuant
{
    template<typename TYPE> class MatrixIndex;

    /// Any type of matrix multiplies TYPE.
    template<typename TYPE, typename MATRIX>
    class InvScaledMatrix : public UnitaryMatrixExpression < TYPE, MATRIX >
    {
    private:
        TYPE div_val;
    public:
        InvScaledMatrix(const TYPE &x, const MATRIX &m) : UnitaryMatrixExpression<TYPE, MATRIX>(m), div_val(x)
        {
            MatrixExpression<TYPE>::Set(m.Nrows(), m.Ncols());
            MatrixExpression<TYPE>::band_width = m.BandWidth();
        }

        ~InvScaledMatrix() {}

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            UnitaryMatrixExpression<TYPE, MATRIX>::mat.GetRowIndex(r, mi);
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            UnitaryMatrixExpression<TYPE, MATRIX>::mat.GetColIndex(c, mi);
        }

        TYPE operator () (const int &r, const int &c) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            return UnitaryMatrixExpression<TYPE, MATRIX>::mat(r, c) / div_val;
        }
    };

    // GeneralMatrix
    template<typename TYPE>
    InvScaledMatrix<TYPE, GeneralMatrix<TYPE> > operator / (const GeneralMatrix<TYPE> & mat, const TYPE &x)
    {
        return InvScaledMatrix<TYPE, GeneralMatrix<TYPE> >(x, mat);
    }

    // MatrixExpression
    template<typename TYPE>
    InvScaledMatrix<TYPE, MatrixExpression<TYPE> > operator / (const MatrixExpression<TYPE> & mat, const TYPE &x)
    {
        return InvScaledMatrix<TYPE, MatrixExpression<TYPE> >(x, mat);
    }

    // BaseMatrix
    template<typename TYPE>
    InvScaledMatrix<TYPE, BaseMatrix<TYPE> > operator / (const BaseMatrix<TYPE> & mat, const TYPE &x)
    {
        return InvScaledMatrix<TYPE, BaseMatrix<TYPE> >(x, mat);
    }
}

#endif //INV_SCALED_MATRIX_H


