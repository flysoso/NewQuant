#ifndef CONSTGETSUB_MATRIX_H
#define CONSTGETSUB_MATRIX_H

#include "MatrixExpression.h"

namespace NewQuant
{
    template<typename TYPE> class MatrixIndex;

    /// A submatrix of a matrix.
    template <typename TYPE, typename MATRIX>
    class ConstGetSubMatrix : public UnitaryMatrixExpression < TYPE, MATRIX >
    {
    private:
        int row_skip;
        int col_skip;
        int row1, row2, col1, col2;
        /*
        row_skip:the number of row indexes to skip
        col_skip:the number of col indexes to skip
        row1:start of row index,row2:end of row index
        col1:start of col index,col2:end of col index
        */
    public:
        ConstGetSubMatrix(const MATRIX &m, const int &r1, const int &r2, const int &c1, const int &c2) : UnitaryMatrixExpression<TYPE, MATRIX>(m)
        {
            row_skip = r1 - 1;
            col_skip = c1 - 1;
            row1 = r1, row2 = r2, col1 = c1, col2 = c2;
            MatrixExpression<TYPE>::Set(r2 - r1 + 1, c2 - c1 + 1);

            if (MatrixExpression<TYPE>::nrows == MatrixExpression<TYPE>::ncols)
            {
                MatrixExpression<TYPE>::band_width.Set(MatrixExpression<TYPE>::nrows - 1, MatrixExpression<TYPE>::nrows - 1, true);
            }
            else
            {
                MatrixExpression<TYPE>::band_width.Set(-1, -1, false);
            }
        }

        ~ConstGetSubMatrix() {}

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            MatrixIndex<TYPE> mi1, mi2;
            UnitaryMatrixExpression<TYPE, MATRIX>::mat.GetRowIndex(r + row_skip, mi1);
            mi1.Shift(-col_skip);

            mi2.Append(1, MatrixExpression<TYPE>::ncols);

            Intersect(mi1, mi2, mi);
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            MatrixIndex<TYPE> mi1, mi2;
            UnitaryMatrixExpression<TYPE, MATRIX>::mat.GetRowIndex(c + col_skip, mi1);
            mi1.Shift(-row_skip);

            mi2.Append(1, MatrixExpression<TYPE>::nrows);

            Intersect(mi1, mi2, mi);
        }

        TYPE operator () (const int &r, const int &c) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            int row = r + row_skip;
            int col = c + col_skip;
            return UnitaryMatrixExpression<TYPE, MATRIX>::mat(row, col);
        }
    };


    // GeneralMatrix
    template <typename TYPE>
    ConstGetSubMatrix<TYPE, GeneralMatrix<TYPE> > c_sub(const GeneralMatrix<TYPE> & mat, const int &r1, const int &r2, const int &c1, const int &c2)
    {
        assert(r1 > 0 && r2 > 0 && c1 > 0 && c2 > 0 && r1 <= r2 && c1 <= c2);
        assert(r2 <= mat.Nrows() && c2 <= mat.Ncols());
        return ConstGetSubMatrix<TYPE, GeneralMatrix<TYPE> >(mat, r1, r2, c1, c2);
    }

    // MatrixExpression
    template <typename TYPE>
    ConstGetSubMatrix<TYPE, MatrixExpression<TYPE> > c_sub(const MatrixExpression<TYPE> & mat, const int &r1, const int &r2, const int &c1, const int &c2)
    {
        assert(r1 > 0 && r2 > 0 && c1 > 0 && c2 > 0 && r1 <= r2 && c1 <= c2);
        assert(r2 <= mat.Nrows() && c2 <= mat.Ncols());
        return ConstGetSubMatrix<TYPE, MatrixExpression<TYPE> >(mat, r1, r2, c1, c2);
    }

    // BaseMatrix
    template <typename TYPE>
    ConstGetSubMatrix<TYPE, BaseMatrix<TYPE> > c_sub(const BaseMatrix<TYPE> & mat, const int &r1, const int &r2, const int &c1, const int &c2)
    {
        assert(r1 > 0 && r2 > 0 && c1 > 0 && c2 > 0 && r1 <= r2 && c1 <= c2);
        assert(r2 <= mat.Nrows() && c2 <= mat.Ncols());
        return ConstGetSubMatrix<TYPE, BaseMatrix<TYPE> >(mat, r1, r2, c1, c2);
    }
}
#endif //CONSTGETSUB_MATRIX_H

