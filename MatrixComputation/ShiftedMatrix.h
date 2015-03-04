#ifndef SHIFTED_MATRIX_H
#define SHIFTED_MATRIX_H


#include "MatrixExpression.h"

namespace NewQuant
{
    template<typename TYPE> class MatrixIndex;

    /// Any type of matrix plus TYPE.
    template <typename TYPE, typename MATRIX>
    class ShiftedMatrix : public UnitaryMatrixExpression < TYPE, MATRIX >
    {
    private:
        TYPE plus_val;
    public:
        ShiftedMatrix(const TYPE &x, const MATRIX &m) : UnitaryMatrixExpression<TYPE, MATRIX>(m), plus_val(x)
        {
            MatrixExpression<TYPE>::Set(m.Nrows(), m.Ncols());
            MatrixExpression<TYPE>::band_width = m.BandWidth();

            if (MatrixExpression<TYPE>::band_width.Evalued() == true)
            {
                MatrixExpression<TYPE>::band_width.lower_val = MatrixExpression<TYPE>::nrows - 1;
                MatrixExpression<TYPE>::band_width.upper_val = MatrixExpression<TYPE>::nrows - 1;
            }
        }

        ~ShiftedMatrix() {}

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
            return UnitaryMatrixExpression<TYPE, MATRIX>::mat(r, c) + plus_val;
        }
    };

    // GeneralMatrix
    template <typename TYPE>
    ShiftedMatrix<TYPE, GeneralMatrix<TYPE> > operator + (const GeneralMatrix<TYPE> &mat, const TYPE & x)
    {
        return ShiftedMatrix<TYPE, GeneralMatrix<TYPE> >(x, mat);
    }

    template <typename TYPE>
    ShiftedMatrix<TYPE, GeneralMatrix<TYPE> > operator + (const TYPE &x, const GeneralMatrix<TYPE> & mat)
    {
        return ShiftedMatrix<TYPE, GeneralMatrix<TYPE> >(x, mat);
    }

    // MatrixExpression
    template <typename TYPE>
    ShiftedMatrix<TYPE, MatrixExpression<TYPE> > operator + (const MatrixExpression<TYPE> & mat, const TYPE &x)
    {
        return ShiftedMatrix<TYPE, MatrixExpression<TYPE> >(x, mat);
    }

    template <typename TYPE>
    ShiftedMatrix<TYPE, MatrixExpression<TYPE> > operator + (const TYPE &x, const MatrixExpression<TYPE> & mat)
    {
        return ShiftedMatrix<TYPE, MatrixExpression<TYPE> >(x, mat);
    }
}
#endif //SHIFTED_MATRIX_H

