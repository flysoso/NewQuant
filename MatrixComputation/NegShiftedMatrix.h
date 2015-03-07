#ifndef NEGSHIFTED_MATRIX_H
#define NEGSHIFTED_MATRIX_H

#include "MatrixExpression.h"

namespace NewQuant
{
    template<typename TYPE> class MatrixIndex;

    /// TYPE minus matrix.
    template<typename TYPE, typename MATRIX>
    class NegShiftedMatrix : public UnitaryMatrixExpression < TYPE, MATRIX >
    {
    public:
        enum MinusType { num_mat = 1, mat_num = 2 };
        //num_mat : num - mat
        //mat_num : mat - num
    private:
        TYPE minus_val;
        MinusType type;
    public:
        NegShiftedMatrix(const TYPE &x, const MATRIX &m, const MinusType &t) : UnitaryMatrixExpression<TYPE, MATRIX>(m), minus_val(x), type(t)
        {
            MatrixExpression<TYPE>::Set(m.Nrows(), m.Ncols());
            MatrixExpression<TYPE>::band_width = m.BandWidth();

            if (MatrixExpression<TYPE>::band_width.Evalued() == true)
            {
                MatrixExpression<TYPE>::band_width.SetLower(MatrixExpression<TYPE>::nrows - 1);
                MatrixExpression<TYPE>::band_width.SetUpper(MatrixExpression<TYPE>::nrows - 1);
            }
        }

        ~NegShiftedMatrix() {}

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
            switch (type)
            {
            case num_mat:
                return minus_val - UnitaryMatrixExpression<TYPE, MATRIX>::mat(r, c);
                break;
            case mat_num:
                return UnitaryMatrixExpression<TYPE, MATRIX>::mat(r, c) - minus_val;
                break;
            default:
                break;
            }
        }
    };

    // GeneralMatrix
    template<typename TYPE>
    NegShiftedMatrix<TYPE, GeneralMatrix<TYPE> > operator - (const GeneralMatrix<TYPE> & mat, const TYPE &x)
    {
        return NegShiftedMatrix<TYPE, GeneralMatrix<TYPE> >(x, mat, NegShiftedMatrix<TYPE, GeneralMatrix<TYPE> >::MinusType::mat_num);
    }

    template<typename TYPE>
    NegShiftedMatrix<TYPE, GeneralMatrix<TYPE> > operator - (const TYPE &x, const GeneralMatrix<TYPE> & mat)
    {
        return NegShiftedMatrix<TYPE, GeneralMatrix<TYPE> >(x, mat, NegShiftedMatrix<TYPE, GeneralMatrix<TYPE> >::MinusType::num_mat);
    }

    // MatrixExpression
    template<typename TYPE>
    NegShiftedMatrix<TYPE, MatrixExpression<TYPE> > operator - (const MatrixExpression<TYPE> & mat, const TYPE &x)
    {
        return NegShiftedMatrix<TYPE, MatrixExpression<TYPE> >(x, mat, NegShiftedMatrix<TYPE, MatrixExpression<TYPE> >::MinusType::mat_num);
    }

    template<typename TYPE>
    NegShiftedMatrix<TYPE, MatrixExpression<TYPE> > operator - (const TYPE &x, const MatrixExpression<TYPE> & mat)
    {
        return NegShiftedMatrix<TYPE, MatrixExpression<TYPE> >(x, mat, NegShiftedMatrix<TYPE, MatrixExpression<TYPE> >::MinusType::num_mat);
    }
}
#endif //NEGSHIFTED_MATRIX_H


