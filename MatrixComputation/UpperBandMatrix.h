#ifndef UPPERBAND_MATRIX_H
#define UPPERBAND_MATRIX_H

#include "BandMatrix.h"

namespace NewQuant
{
    template<typename TYPE> class BandMatrix;

    /// Upper triangular band matrix.
    template<typename TYPE>
    class UpperBandMatrix : public BandMatrix < TYPE >
    {
    public:
        UpperBandMatrix() : BandMatrix<TYPE>() {}

        UpperBandMatrix(const int &n, const int &ubw) : BandMatrix<TYPE>(n, 0, ubw) {}// standard declaration

        UpperBandMatrix(const UpperBandMatrix<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::CopyMatrix(gm);
        }

        ~UpperBandMatrix() {}

        UpperBandMatrix<TYPE> & operator=(const BaseMatrix<TYPE> &);

        UpperBandMatrix<TYPE> & operator=(const UpperBandMatrix<TYPE>& m)
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

        void Resize(const int &n, const int &ubw)              // change dimensions
        {
            assert(n > 0 && n > ubw);
            BandMatrix<TYPE>::Resize(n, 0, ubw);
        }

        TYPE& operator()(const int &, const int &);

        TYPE operator()(const int &, const int &) const;

        void Swap(UpperBandMatrix<TYPE>& gm)
        {
            BandMatrix<TYPE>::Swap(gm);
        }

        void Swap(BandMatrix<TYPE>& gm);
    };

    template<typename TYPE>
    inline void Swap(UpperBandMatrix<TYPE>& A, UpperBandMatrix<TYPE>& B)
    {
        A.Swap(B);
    }
}
#include "UpperBandMatrix.cpp"

#endif //UPPERBAND_MATRIX_H

