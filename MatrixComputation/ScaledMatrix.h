#ifndef SCALED_MATRIX_H
#define SCALED_MATRIX_H

#include "MatrixExpression.h"

namespace NewQuant
{
    template<typename TYPE> class MatrixIndex;

    /// Any type of matrix multiplies TYPE.
    template<typename TYPE, typename MATRIX>
    class ScaledMatrix : public UnitaryMatrixExpression < TYPE, MATRIX >
    {
    private:
        TYPE mult_val;
    public:
        ScaledMatrix(const TYPE &x, const MATRIX &m) : UnitaryMatrixExpression<TYPE, MATRIX>(m), mult_val(x)
        {
            MatrixExpression<TYPE>::Set(m.Nrows(), m.Ncols());
            MatrixExpression<TYPE>::band_width = m.BandWidth();
        }

        ~ScaledMatrix() {}

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
            return UnitaryMatrixExpression<TYPE, MATRIX>::mat(r, c) * mult_val;
        }
    };

    // GeneralMatrix
    template<typename TYPE>
    ScaledMatrix<TYPE, GeneralMatrix<TYPE> > operator * (const GeneralMatrix<TYPE> & mat, const TYPE &x)
    {
        return ScaledMatrix<TYPE, GeneralMatrix<TYPE> >(x, mat);
    }

    template<typename TYPE>
    ScaledMatrix<TYPE, GeneralMatrix<TYPE> > operator * (const TYPE &x, const GeneralMatrix<TYPE> & mat)
    {
        return ScaledMatrix<TYPE, GeneralMatrix<TYPE> >(x, mat);
    }

    // MatrixExpression
    template<typename TYPE>
    ScaledMatrix<TYPE, MatrixExpression<TYPE> > operator * (const MatrixExpression<TYPE> & mat, const TYPE &x)
    {
        return ScaledMatrix<TYPE, MatrixExpression<TYPE> >(x, mat);
    }

    template<typename TYPE>
    ScaledMatrix<TYPE, MatrixExpression<TYPE> > operator * (const TYPE &x, const MatrixExpression<TYPE> & mat)
    {
        return ScaledMatrix<TYPE, MatrixExpression<TYPE> >(x, mat);
    }
}
#endif //SCALED_MATRIX_H


