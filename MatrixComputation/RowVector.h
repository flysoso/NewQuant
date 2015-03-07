#ifndef ROW_VECTOR_H
#define ROW_VECTOR_H

#include "Matrix.h"
#include "Vector.h"

namespace NewQuant
{
    /// Row vector.
    template<typename TYPE>
    class RowVector : public Matrix < TYPE >, public Vector < TYPE >
    {
    public:
        RowVector() : Matrix<TYPE>(), Vector<TYPE>() {}

        explicit RowVector(const int &n) : Matrix<TYPE>(1, n), Vector<TYPE>(n) {}

        RowVector(const RowVector<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::CopyMatrix(gm);
        }

        RowVector(const TYPE &a, int n) : Matrix<TYPE>(a, 1, n), Vector<TYPE>(n) {}

        RowVector(const TYPE* a, int n) : Matrix<TYPE>(a, 1, n), Vector<TYPE>(n) {}

        ~RowVector() {}

        RowVector<TYPE>& operator=(const BaseMatrix<TYPE>&);

        RowVector<TYPE>& operator=(const RowVector<TYPE>& m)
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

        TYPE & operator()(const int &);                       // access element

        TYPE & operator()(const int &, const int &);          // access element

        TYPE operator()(const int &) const;                  // access element

        TYPE operator()(const int &, const int &) const;     // access element

        MatrixType Type() const;

        void Resize(const int &);                       // change dimensions

        void Resize(const int &, const int &);                   // in case access is matrix

        void Swap(RowVector<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::Swap(gm);
        }

        void Swap(Matrix<TYPE>&);

    };

    template<typename TYPE>
    inline void Swap(RowVector<TYPE>& A, RowVector<TYPE>& B)
    {
        A.Swap(B);
    }
}
#include "RowVector.cpp"


#endif //ROW_VECTOR_H

