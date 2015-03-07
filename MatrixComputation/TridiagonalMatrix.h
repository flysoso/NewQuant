#ifndef TRIDIAGONAL_MATRIX_H
#define TRIDIAGONAL_MATRIX_H

#include "BandMatrix.h"

namespace NewQuant
{
    /// Triangular band matrix.
    template<typename TYPE>
    class TridiagonalMatrix : public BandMatrix < TYPE >
    {
    public:
        TridiagonalMatrix() : BandMatrix<TYPE>() {}

        explicit TridiagonalMatrix(int n) : BandMatrix<TYPE>(n, 1, 1) {}// standard declaration

        TridiagonalMatrix(const TridiagonalMatrix<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::CopyMatrix(gm);
        }

        ~TridiagonalMatrix() {}

        TridiagonalMatrix<TYPE> & operator=(const BaseMatrix<TYPE> &);

        TridiagonalMatrix<TYPE> & operator=(const BandMatrix<TYPE> &m)
        {
            assert(m.BandWidth().Lower() == 1 && m.BandWidth().Upper() == 1);
            if (&m == this)
            {
                return *this;
            }
            GeneralMatrix<TYPE>::CopyMatrix(m);
            return *this;
        }

        TridiagonalMatrix<TYPE> & operator=(const TridiagonalMatrix<TYPE>& m)
        {
            if (&m == this)
            {
                return *this;
            }
            GeneralMatrix<TYPE>::CopyMatrix(m);
            return *this;
        }

        MatrixType Type() const;

        void Resize(const int &, const int &, const int &);             // change dimensions

        void Resize(const int &n)             // change dimensions
        {
            BandMatrix<TYPE>::Resize(n, 1, 1);
        }

        void Swap(TridiagonalMatrix<TYPE>& gm)
        {
            BandMatrix<TYPE>::Swap(gm);
        }

        void Swap(BandMatrix<TYPE>& gm);
    };

    template<typename TYPE>
    inline void Swap(TridiagonalMatrix<TYPE>& A, TridiagonalMatrix<TYPE>& B)
    {
        A.Swap(B);
    }
}
#include "TridiagonalMatrix.cpp"

#endif //TRIDIAGONAL_MATRIX_H

