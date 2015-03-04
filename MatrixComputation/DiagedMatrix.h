#ifndef DIAGED_MATRIX_H
#define DIAGED_MATRIX_H

#include "MatrixExpression.h"

namespace NewQuant
{
    template<typename TYPE> class MatrixIndex;

    /// Any type of matrix interpreted as a DiagonalMatrix.
    template <typename TYPE, typename MATRIX>
    class DiagedMatrix : public UnitaryMatrixExpression < TYPE, MATRIX >
    {
    public:
        enum DiagedType { diag_by_r = 1, diag_by_c = 2 };
    private:
        DiagedType type;
    public:
        DiagedMatrix(const MATRIX &m, const DiagedType &t) : UnitaryMatrixExpression<TYPE, MATRIX>(m), type(t)
        {
            MatrixExpression<TYPE>::Set(m.Nrows() * m.Ncols(), m.Nrows() * m.Ncols());
            MatrixExpression<TYPE>::band_width.Set(0, 0, true);
        }

        ~DiagedMatrix() {}

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            mi.Clear();
            mi.Append(r, r);
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            mi.Clear();
            mi.Append(c, c);
        }

        TYPE operator () (const int &r, const int &c) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            const MATRIX &mat = UnitaryMatrixExpression<TYPE, MATRIX>::mat;
            static const TYPE zero(0);
            switch (type)
            {
            case diag_by_r:
                if (r != c)
                {
                    return zero;
                }
                else
                {
                    int row = (c - 1) / mat.Nrows() + 1;
                    int col = (c - 1) % mat.Nrows() + 1;
                    return mat(row, col);
                }
                break;
            case diag_by_c:
                if (r != c)
                {
                    return zero;
                }
                else
                {
                    int row = (r - 1) % mat.Nrows() + 1;
                    int col = (r - 1) / mat.Nrows() + 1;
                    return mat(row, col);
                }
                break;
            }
        }
    };


    // GeneralMatrix
    template <typename TYPE>
    DiagedMatrix<TYPE, GeneralMatrix<TYPE> > diag_by_row(const GeneralMatrix<TYPE> & mat)
    {
        return DiagedMatrix<TYPE, GeneralMatrix<TYPE> >(mat, DiagedMatrix<TYPE, GeneralMatrix<TYPE> >::DiagedType::diag_by_r);
    }

    // MatrixExpression
    template <typename TYPE>
    DiagedMatrix<TYPE, MatrixExpression<TYPE> > diag_by_row(const MatrixExpression<TYPE> & mat)
    {
        return DiagedMatrix<TYPE, MatrixExpression<TYPE> >(mat, DiagedMatrix<TYPE, MatrixExpression<TYPE> >::DiagedType::diag_by_r);
    }


    // GeneralMatrix
    template <typename TYPE>
    DiagedMatrix<TYPE, GeneralMatrix<TYPE> > diag_by_col(const GeneralMatrix<TYPE> & mat)
    {
        return DiagedMatrix<TYPE, GeneralMatrix<TYPE> >(mat, DiagedMatrix<TYPE, GeneralMatrix<TYPE> >::DiagedType::diag_by_c);
    }

    // MatrixExpression
    template <typename TYPE>
    DiagedMatrix<TYPE, MatrixExpression<TYPE> > diag_by_col(const MatrixExpression<TYPE> & mat)
    {
        return DiagedMatrix<TYPE, MatrixExpression<TYPE> >(mat, DiagedMatrix<TYPE, MatrixExpression<TYPE> >::DiagedType::diag_by_c);
    }
}

#endif //DIAGED_MATRIX_H

