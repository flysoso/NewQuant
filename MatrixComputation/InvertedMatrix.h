#ifndef INVERTED_MATRIX_H
#define INVERTED_MATRIX_H


#include "MatrixExpression.h"

template<typename TYPE> class MatrixIndex;

/// Inverse of matrix.
template <typename TYPE, typename MATRIX>
class InvertedMatrix : public UnitaryMatrixExpression < TYPE, MATRIX >
{
private:
    std::shared_ptr<GeneralMatrix<TYPE> > inv_mat;
public:
    InvertedMatrix(const MATRIX &m) : UnitaryMatrixExpression<TYPE, MATRIX>(m)
    {
        inv_mat = m.MakeInv();
        MatrixExpression<TYPE>::nrows = m.Nrows();
        MatrixExpression<TYPE>::ncols = m.Ncols();
        MatrixExpression<TYPE>::band_width = inv_mat->BandWidth();
    }

    ~InvertedMatrix() {}

    void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
    {
        assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
        inv_mat->GetRowIndex(r, mi);
    }

    void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
    {
        assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
        inv_mat->GetColIndex(c, mi);
    }

    TYPE operator () (const int &r, const int &c) const
    {
        assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
        assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
        return (*inv_mat)(r, c);
    }
};

// GeneralMatrix
template <typename TYPE>
InvertedMatrix<TYPE, GeneralMatrix<TYPE> > inv(const GeneralMatrix<TYPE> & mat)
{
    assert(mat.Nrows() == mat.Ncols());
    return InvertedMatrix<TYPE, GeneralMatrix<TYPE> >(mat);
}

// MatrixExpression
template <typename TYPE>
InvertedMatrix<TYPE, MatrixExpression<TYPE> > inv(const MatrixExpression<TYPE> & mat)
{
    assert(mat.Nrows() == mat.Ncols());
    return InvertedMatrix<TYPE, MatrixExpression<TYPE> >(mat);
}

#endif //INVERTED_MATRIX_H

