#ifndef TRANSPOSED_MATRIX_H
#define TRANSPOSED_MATRIX_H

#include "MatrixExpression.h"

namespace NewQuant
{
    template<typename TYPE> class MatrixIndex;

    /// Transposed matrix.
    template<typename TYPE, typename MATRIX>
    class TransposedMatrix : public UnitaryMatrixExpression < TYPE, MATRIX >
    {
    public:
        TransposedMatrix(const MATRIX &m) : UnitaryMatrixExpression<TYPE, MATRIX>(m)
        {
            MatrixExpression<TYPE>::Set(m.Ncols(), m.Nrows());
            MatrixExpression<TYPE>::band_width = m.BandWidth().t();
        }

        ~TransposedMatrix() {}

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            mi.Clear();
            UnitaryMatrixExpression<TYPE, MATRIX>::mat.GetColIndex(r, mi);
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            mi.Clear();
            UnitaryMatrixExpression<TYPE, MATRIX>::mat.GetRowIndex(c, mi);
        }

        TYPE operator () (const int &r, const int &c) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            return UnitaryMatrixExpression<TYPE, MATRIX>::mat(c, r);
        }
    };

    // GeneralMatrix
    template<typename TYPE>
    TransposedMatrix<TYPE, GeneralMatrix<TYPE> > t(const GeneralMatrix<TYPE> & mat)
    {
        return TransposedMatrix<TYPE, GeneralMatrix<TYPE> >(mat);
    }

    // MatrixExpression
    template<typename TYPE>
    TransposedMatrix<TYPE, MatrixExpression<TYPE> > t(const MatrixExpression<TYPE> & mat)
    {
        return TransposedMatrix<TYPE, MatrixExpression<TYPE> >(mat);
    }

    // BaseMatrix
    template<typename TYPE>
    TransposedMatrix<TYPE, BaseMatrix<TYPE> > t(const BaseMatrix<TYPE> & mat)
    {
        return TransposedMatrix<TYPE, BaseMatrix<TYPE> >(mat);
    }
}
#endif //TRANSPOSED_MATRIX_H

