#ifndef MATED_MATRIX_H
#define MATED_MATRIX_H

#include "MatrixExpression.h"

namespace NewQuant
{
    template<typename TYPE> class MatrixIndex;

    /// Any type of matrix interpreted as a (rectangular) Matrix.
    template<typename TYPE, typename MATRIX>
    class MatedMatrix : public UnitaryMatrixExpression < TYPE, MATRIX >
    {
    public:
        enum MatedType { mated_by_r, mated_by_c };
    private:
        MatedType type;
    public:
        MatedMatrix(const MATRIX &m, int row, int col, const MatedType &t) : UnitaryMatrixExpression<TYPE, MATRIX>(m), type(t)
        {
            MatrixExpression<TYPE>::Set(row, col);
            if (row == col)
            {
                MatrixExpression<TYPE>::band_width.Set(row - 1, col - 1, false);
            }
            else
            {
                MatrixExpression<TYPE>::band_width.Set(-1, -1, false);
            }

        }

        ~MatedMatrix() {}

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
            int row, col, length;
            switch (type)
            {
            case mated_by_r:
                length = (r - 1)*MatrixExpression<TYPE>::ncols + c;
                row = (length - 1) / UnitaryMatrixExpression<TYPE, MATRIX>::mat.Ncols() + 1;
                col = (length - 1) % UnitaryMatrixExpression<TYPE, MATRIX>::mat.Ncols() + 1;
                return UnitaryMatrixExpression<TYPE, MATRIX>::mat(row, col);
                break;
            case mated_by_c:
                length = (c - 1)*MatrixExpression<TYPE>::nrows + r;
                row = (length - 1) % UnitaryMatrixExpression<TYPE, MATRIX>::mat.Nrows() + 1;
                col = (length - 1) / UnitaryMatrixExpression<TYPE, MATRIX>::mat.Nrows() + 1;
                return UnitaryMatrixExpression<TYPE, MATRIX>::mat(row, col);
                break;
            }
        }
    };


    // GeneralMatrix
    template<typename TYPE>
    MatedMatrix<TYPE, GeneralMatrix<TYPE> > as_mat_by_row(const GeneralMatrix<TYPE> & mat, int r, int c)
    {
        assert(r*c == mat.Nrows()*mat.Ncols());
        return MatedMatrix<TYPE, GeneralMatrix<TYPE> >(mat, r, c, MatedMatrix<TYPE, GeneralMatrix<TYPE> >::MatedType::mated_by_r);
    }

    // MatrixExpression
    template<typename TYPE>
    MatedMatrix<TYPE, MatrixExpression<TYPE> > as_mat_by_row(const MatrixExpression<TYPE> & mat, int r, int c)
    {
        assert(r*c == mat.Nrows()*mat.Ncols());
        return MatedMatrix<TYPE, MatrixExpression<TYPE> >(mat, r, c, MatedMatrix<TYPE, MatrixExpression<TYPE> >::MatedType::mated_by_r);
    }

    // GeneralMatrix
    template<typename TYPE>
    MatedMatrix<TYPE, GeneralMatrix<TYPE> > as_mat_by_col(const GeneralMatrix<TYPE> & mat, int r, int c)
    {
        assert(r*c == mat.Nrows()*mat.Ncols());
        return MatedMatrix<TYPE, GeneralMatrix<TYPE> >(mat, r, c, MatedMatrix<TYPE, GeneralMatrix<TYPE> >::MatedType::mated_by_c);
    }

    // MatrixExpression
    template<typename TYPE>
    MatedMatrix<TYPE, MatrixExpression<TYPE> > as_mat_by_col(const MatrixExpression<TYPE> & mat, int r, int c)
    {
        assert(r*c == mat.Nrows()*mat.Ncols());
        return MatedMatrix<TYPE, MatrixExpression<TYPE> >(mat, r, c, MatedMatrix<TYPE, MatrixExpression<TYPE> >::MatedType::mated_by_c);
    }
}

#endif //MATED_MATRIX_H

