#ifndef SQUARE_MATRIX_H
#define SQUARE_MATRIX_H

#include "Matrix.h"

/// Square matrix.
template <typename TYPE>
class SquareMatrix : public Matrix < TYPE >
{
public:
    SquareMatrix() : Matrix<TYPE>() {}

    explicit SquareMatrix(const int &);

    SquareMatrix(const SquareMatrix<TYPE>& gm)
    {
        GeneralMatrix<TYPE>::CopyMatrix(gm);
    }

    SquareMatrix(const Matrix<TYPE>&);

    ~SquareMatrix() {}

    SquareMatrix<TYPE> & operator=(const BaseMatrix<TYPE> &);

    SquareMatrix<TYPE> & operator=(const SquareMatrix<TYPE>& m)
    {
        if (&m == this)
        {
            return *this;
        }
        GeneralMatrix<TYPE>::CopyMatrix(m);
        return *this;
    }

    SquareMatrix<TYPE> & operator=(const Matrix<TYPE>&);

    void operator+=(const Matrix<TYPE>& M)
    {
        GeneralMatrix<TYPE>::PlusEqual(M);
    }

    void SP_eq(const Matrix<TYPE>& M)
    {
        GeneralMatrix<TYPE>::SP_Equal(M);
    }

    void operator-=(const Matrix<TYPE>& M)
    {
        GeneralMatrix<TYPE>::MinusEqual(M);
    }

    void operator+=(const TYPE &f)
    {
        GeneralMatrix<TYPE>::Add(f);
    }

    void operator-=(const TYPE &f)
    {
        GeneralMatrix<TYPE>::Add(-f);
    }

    MatrixType Type() const;

    void Resize(const int &);                            // change dimensions

    void Resize(const int &, const int &);                        // change dimensions

    void Swap(SquareMatrix<TYPE>& gm)
    {
        GeneralMatrix<TYPE>::Swap(gm);
    }

    void Swap(Matrix<TYPE>& gm);

};

template <typename TYPE>
inline void Swap(SquareMatrix<TYPE>& A, SquareMatrix<TYPE>& B)
{
    A.Swap(B);
}

#include "SquareMatrix.cpp"

#endif //SQUARE_MATRIX_H


