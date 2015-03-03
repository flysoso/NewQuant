#ifndef SOLVED_MATRIX_H
#define SOLVED_MATRIX_H


#include "MatrixExpression.h"
#include "InvertedMatrix.h"

template<typename TYPE> class MatrixIndex;

/// Inverted matrix multiplies matrix.
template <typename TYPE, typename MATRIX1, typename MATRIX2>
class SolvedMatrix : public BinaryMatrixExpression < TYPE, MATRIX1, MATRIX2 >
{
private:
    InvertedMatrix<TYPE, MATRIX2> inv_mat;
public:
    SolvedMatrix(const MATRIX1 &m1, const MATRIX2 &m2) : BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>(m1, m2), inv_mat(m2)
    {
        MatrixExpression<TYPE>::Set(mat1.Nrows(), mat2.Ncols());
        MatrixExpression<TYPE>::band_width = Mult(m1.BandWidth(), inv_mat.BandWidth(), MatrixExpression<TYPE>::nrows);
    }

    ~SolvedMatrix() {}

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
            int up = std::min(bw.Upper(), r - 1);
            int down = std::min(bw.Lower(), dim - r);

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
        MatrixIndex<TYPE> row, col, temp;
        BinaryMatrixExpression<TYPE, MATRIX1, MATRIX2>::mat1.GetRowIndex(r, row);
        inv_mat.GetColIndex(c, col);
        Intersect(row, col, temp);
        MatrixIndex<TYPE>::Iterator iter;
        TYPE sum(0);
        for (iter = temp.Begin(); iter != temp.End(); ++iter)
        {
            sum += mat1(r, *iter) * inv_mat(*iter, c);
        }
        reurn sum;
    }
};


// GeneralMatrix
template <typename TYPE>
SolvedMatrix<TYPE, GeneralMatrix<TYPE>, GeneralMatrix<TYPE> > operator / (const GeneralMatrix<TYPE> & mat1, const GeneralMatrix<TYPE> & mat2)
{
    assert(mat1.Ncols() == mat2.Nrows() && mat2.BandWidth().Evalued());
    return SolvedMatrix<TYPE, GeneralMatrix<TYPE>, GeneralMatrix<TYPE> >(mat1, mat2);
}

template <typename TYPE>
SolvedMatrix<TYPE, GeneralMatrix<TYPE>, MatrixExpression<TYPE> > operator / (const GeneralMatrix<TYPE> & mat1, const MatrixExpression<TYPE> & mat2)
{
    assert(mat1.Ncols() == mat2.Nrows() && mat2.BandWidth().Evalued());
    return SolvedMatrix<TYPE, GeneralMatrix<TYPE>, MatrixExpression<TYPE> >(mat1, mat2);
}

// MatrixExpression
template <typename TYPE>
SolvedMatrix<TYPE, MatrixExpression<TYPE>, GeneralMatrix<TYPE> > operator / (const MatrixExpression<TYPE> & mat1, const GeneralMatrix<TYPE> & mat2)
{
    assert(mat1.Ncols() == mat2.Nrows() && mat2.BandWidth().Evalued());
    return SolvedMatrix<TYPE, MatrixExpression<TYPE>, GeneralMatrix<TYPE> >(mat1, mat2);
}

template <typename TYPE>
SolvedMatrix<TYPE, MatrixExpression<TYPE>, MatrixExpression<TYPE> > operator / (const MatrixExpression<TYPE> & mat1, const MatrixExpression<TYPE> & mat2)
{
    assert(mat1.Ncols() == mat2.Nrows() && mat2.BandWidth().Evalued());
    return SolvedMatrix<TYPE, MatrixExpression<TYPE>, MatrixExpression<TYPE> >(mat1, mat2);
}

#endif //SOLVED_MATRIX_H

