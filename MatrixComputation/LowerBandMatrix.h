#ifndef LOWERBAND_MATRIX_H
#define LOWERBAND_MATRIX_H

#include "BandMatrix.h"

namespace NewQuant
{
    /// Lower triangular band matrix.
    template<typename TYPE>
    class LowerBandMatrix : public BandMatrix < TYPE >
    {
    public:
        LowerBandMatrix() : BandMatrix<TYPE>() {}

        LowerBandMatrix(int n, int lbw) : BandMatrix<TYPE>(n, lbw, 0) {}// standard declaration

        LowerBandMatrix(const LowerBandMatrix<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::CopyMatrix(gm);
        }

        ~LowerBandMatrix() {}

        LowerBandMatrix<TYPE> & operator=(const BaseMatrix<TYPE> &);

        LowerBandMatrix<TYPE> & operator=(const BandMatrix<TYPE> &m)
        {
            assert(m.BandWidth().Upper() == 0);
            if (&m == this)
            {
                return *this;
            }
            GeneralMatrix<TYPE>::CopyMatrix(m);
            return *this;
        }

        LowerBandMatrix<TYPE> & operator=(const LowerBandMatrix<TYPE> &m)
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

        void Resize(const int &n, const int &lbw)             // change dimensions
        {
            BandMatrix<TYPE>::Resize(n, lbw, 0);
        }

        TYPE& operator()(const int &, const int &);

        TYPE operator()(const int &, const int &) const;

        void Swap(LowerBandMatrix<TYPE>& gm)
        {
            BandMatrix<TYPE>::Swap(gm);
        }

        void Swap(BandMatrix<TYPE>& gm);
    };

    template<typename TYPE>
    inline void Swap(LowerBandMatrix<TYPE>& A, LowerBandMatrix<TYPE>& B)
    {
        A.Swap(B);
    }
}
#include "LowerBandMatrix.cpp"

#endif //LOWERBAND_MATRIX_H

