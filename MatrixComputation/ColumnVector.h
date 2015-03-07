#ifndef COLUMN_VECTOR_H
#define COLUMN_VECTOR_H

#include "Matrix.h"
#include "Vector.h"

namespace NewQuant
{
    class MatrixType;

    /// Column vector.
    template<typename TYPE>
    class ColumnVector : public Matrix < TYPE >, public Vector < TYPE >
    {
    public:
        ColumnVector() : Matrix<TYPE>(), Vector<TYPE>() {}

        explicit ColumnVector(const int & n) : Matrix<TYPE>(n, 1), Vector<TYPE>(n) {}

        ColumnVector(const ColumnVector<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::CopyMatrix(gm);
        }

        ColumnVector(const TYPE &a, int m) : Matrix<TYPE>(a, m, 1), Vector<TYPE>(m) {}

        ColumnVector(const TYPE* a, int m) : Matrix<TYPE>(a, m, 1), Vector<TYPE>(m) {}

        ~ColumnVector() {}

        ColumnVector<TYPE> & operator=(const BaseMatrix<TYPE>&);

        ColumnVector<TYPE> & operator=(const ColumnVector<TYPE>& m)
        {
            if (&m == this)
            {
                return *this;
            }
            GeneralMatrix<TYPE>::CopyMatrix(m);
            return *this;
        }

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

        TYPE& operator()(const int &, const int &);          // access element

        TYPE& operator()(const int &);                       // access element

        TYPE operator()(const int &) const;                  // access element

        TYPE operator()(const int &, const int &) const;     // access element

        MatrixType Type() const;

        void Resize(const int &);                       // change dimensions

        void Resize(const int &, const int &);                   // in case access is matrix

        void Swap(ColumnVector<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::Swap(gm);
        }

        void Swap(Matrix<TYPE>& gm);
    };

    template<typename TYPE>
    inline void Swap(ColumnVector<TYPE>& A, ColumnVector<TYPE>& B)
    {
        A.Swap(B);
    }

}
#include "ColumnVector.cpp"


#endif //COLUMN_VECTOR_H


