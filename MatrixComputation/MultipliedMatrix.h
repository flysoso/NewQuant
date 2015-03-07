#ifndef MULTIPLIED_MATRIX_H
#define MULTIPLIED_MATRIX_H

#include "MatrixExpression.h"

namespace NewQuant
{
    template<typename TYPE> class MatrixIndex;

    /// Product of two matrices.
    template<typename TYPE, typename MATRIX1, typename MATRIX2>
    class MultipliedMatrix : public BinaryMatrixExpression < TYPE, MATRIX1, MATRIX2 >
    {
    private:
        int length;
    public:
        MultipliedMatrix(const MATRIX1 &m1, const MATRIX2 &m2) : BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>(m1, m2)
        {
            length = m1.Ncols();
            MatrixExpression<TYPE>::Set(m1.Nrows(), m2.Ncols());
            MatrixExpression<TYPE>::band_width = Mult(m1.BandWidth(), m2.BandWidth(), MatrixExpression<TYPE>::nrows);

            if (MatrixExpression<TYPE>::nrows != MatrixExpression<TYPE>::ncols)
            {
                MatrixExpression<TYPE>::band_width.Set(-1, -1, false);
            }
            else
            {
                if (!(m1.BandWidth().Evalued() && m2.BandWidth().Evalued()))
                {
                    MatrixExpression<TYPE>::band_width.Set(MatrixExpression<TYPE>::nrows - 1, MatrixExpression<TYPE>::ncols - 1, true);
                }
            }
        }
        ~MultipliedMatrix() {}

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            const MatrixBandWidth<TYPE> &bw = MatrixExpression<TYPE>::band_width;
            if (bw.Evalued())
            {
                int dim = MatrixExpression<TYPE>::nrows;
                int left = std::min(bw.Lower(), r - 1);
                int right = std::min(bw.Upper(), dim - r);

                mi.Clear();
                mi.Append(r - left, r + right);
            }
            else
            {
                mi.Clear();
                mi.Append(1, MatrixExpression<TYPE>::ncols);
            }
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            const MatrixBandWidth<TYPE> &bw = MatrixExpression<TYPE>::band_width;
            if (bw.Evalued())
            {
                int dim = MatrixExpression<TYPE>::nrows;
                int up = std::min(bw.Upper(), c - 1);
                int down = std::min(bw.Lower(), dim - c);

                mi.Clear();
                mi.Append(c - up, c + down);
            }
            else
            {
                mi.Clear();
                mi.Append(1, MatrixExpression<TYPE>::nrows);
            }
        }

        TYPE operator () (const int &r, const int &c) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            TYPE sum(0);
            for (int i = 1; i <= length; ++i)
            {
                sum += BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat1(r, i) * BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat2(i, c);
            }
            return sum;
        }
    };

    // GeneralMatrix
    template<typename TYPE>
    MultipliedMatrix<TYPE, GeneralMatrix<TYPE>, GeneralMatrix<TYPE> > operator * (const GeneralMatrix<TYPE> & mat1, const GeneralMatrix<TYPE> & mat2)
    {
        assert(mat1.Ncols() == mat2.Nrows());
        return MultipliedMatrix<TYPE, GeneralMatrix<TYPE>, GeneralMatrix<TYPE> >(mat1, mat2);
    }

    template<typename TYPE>
    MultipliedMatrix<TYPE, GeneralMatrix<TYPE>, MatrixExpression<TYPE> > operator * (const GeneralMatrix<TYPE> & mat1, const MatrixExpression<TYPE> & mat2)
    {
        assert(mat1.Ncols() == mat2.Nrows());
        return MultipliedMatrix<TYPE, GeneralMatrix<TYPE>, MatrixExpression<TYPE> >(mat1, mat2);
    }

    // MatrixExpression
    template<typename TYPE>
    MultipliedMatrix<TYPE, MatrixExpression<TYPE>, GeneralMatrix<TYPE> > operator * (const MatrixExpression<TYPE> & mat1, const GeneralMatrix<TYPE> & mat2)
    {
        assert(mat1.Ncols() == mat2.Nrows());
        return MultipliedMatrix<TYPE, MatrixExpression<TYPE>, GeneralMatrix<TYPE> >(mat1, mat2);
    }

    template<typename TYPE>
    MultipliedMatrix<TYPE, MatrixExpression<TYPE>, MatrixExpression<TYPE> > operator * (const MatrixExpression<TYPE> & mat1, const MatrixExpression<TYPE> & mat2)
    {
        assert(mat1.Ncols() == mat2.Nrows());
        return MultipliedMatrix<TYPE, MatrixExpression<TYPE>, MatrixExpression<TYPE> >(mat1, mat2);
    }

    // BaseMatrix
    template<typename TYPE>
    MultipliedMatrix<TYPE, BaseMatrix<TYPE>, BaseMatrix<TYPE> > operator * (const BaseMatrix<TYPE> & mat1, const BaseMatrix<TYPE> & mat2)
    {
        assert(mat1.Ncols() == mat2.Nrows());
        return MultipliedMatrix<TYPE, BaseMatrix<TYPE>, BaseMatrix<TYPE> >(mat1, mat2);
    }
}
#endif //MULTIPLIED_MATRIX_H


