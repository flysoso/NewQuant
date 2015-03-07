#ifndef NEGATED_MATRIX_H
#define NEGATED_MATRIX_H


#include "MatrixExpression.h"

namespace NewQuant
{
    template<typename TYPE> class MatrixIndex;

    /// Any type of matrix multiplies -1.
    template<typename TYPE, typename MATRIX>
    class NegatedMatrix : public UnitaryMatrixExpression < TYPE, MATRIX >
    {
    public:
        NegatedMatrix(const MATRIX &m) : UnitaryMatrixExpression<TYPE, MATRIX>(m)
        {
            MatrixExpression<TYPE>::Set(m.Nrows(), m.Ncols());
            MatrixExpression<TYPE>::band_width = m.BandWidth();
        }
        ~NegatedMatrix() {}

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
            return -UnitaryMatrixExpression<TYPE, MATRIX>::mat(r, c);
        }
    };

    // GeneralMatrix
    template<typename TYPE>
    NegatedMatrix<TYPE, GeneralMatrix<TYPE> > operator - (const GeneralMatrix<TYPE> & mat)
    {
        return NegatedMatrix<TYPE, GeneralMatrix<TYPE> >(mat);
    }

    // MatrixExpression
    template<typename TYPE>
    NegatedMatrix<TYPE, MatrixExpression<TYPE> > operator - (const MatrixExpression<TYPE> & mat)
    {
        return NegatedMatrix<TYPE, MatrixExpression<TYPE> >(mat);
    }
}
#endif //NEGATED_MATRIX_H

