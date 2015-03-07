#ifndef BAND_MATRIX_H
#define BAND_MATRIX_H

#include "GeneralMatrix.h"

namespace NewQuant
{
    template<typename TYPE> class LUsolverPartialPivot;
    template<typename TYPE> class BandLUsolverPartialPivot;
    template<typename TYPE> class LowerTriangularSolver;
    template<typename TYPE> class UpperTriangularSolver;

    /// Band matrix.
    template<typename TYPE>
    class BandMatrix : public GeneralMatrix < TYPE >
    {
    protected:
        void CornerClear() const;                    // set unused elements to zero
    public:
        BandMatrix() : GeneralMatrix<TYPE>(1, 1, 1)
        {
            GeneralMatrix<TYPE>::band_width.Set(0, 0, true);
            CornerClear();
        }

        BandMatrix(const int &n, const int &lb, const int &ub);

        BandMatrix(const BandMatrix<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::CopyMatrix(gm);
        }

        ~BandMatrix() {}

        BandMatrix<TYPE> & operator=(const BaseMatrix<TYPE> &gm);

        BandMatrix<TYPE> & operator=(const BandMatrix<TYPE> &m)
        {
            if (&m == this)
            {
                return *this;
            }
            GeneralMatrix<TYPE>::CopyMatrix(m);
            return *this;
        }

        void operator<<(const BaseMatrix<TYPE> &gm);

        void operator<<(const TYPE &x)
        {
            GeneralMatrix<TYPE>::operator<<(x);
        }

        void operator<<(const int &x)
        {
            GeneralMatrix<TYPE>::operator<<(x);
        }

        MatrixType Type() const;

        TYPE& operator()(const int &, const int &);                  // access element

        TYPE operator()(const int &, const int &) const;             // access element

        std::shared_ptr<GeneralMatrix<TYPE> > MakeInv() const;

        std::shared_ptr<LinearEquationSolver<TYPE> > MakeSolver() const;

        void Solve(const BaseMatrix<TYPE>&, BaseMatrix<TYPE>&) const;

        virtual void Resize(const int &, const int &, const int &);             // change dimensions

        virtual void Swap(BandMatrix<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::Swap(gm);
        }

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= GeneralMatrix<TYPE>::nrows);
            const MatrixBandWidth<TYPE> &bw = GeneralMatrix<TYPE>::band_width;
            int dim = GeneralMatrix<TYPE>::nrows;
            int left = std::min(bw.Lower(), r - 1);
            int right = std::min(bw.Upper(), dim - r);

            mi.Clear();
            mi.Append(r - left, r + right);
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= GeneralMatrix<TYPE>::ncols);
            const MatrixBandWidth<TYPE> &bw = GeneralMatrix<TYPE>::band_width;
            int dim = GeneralMatrix<TYPE>::nrows;
            int up = std::min(bw.Upper(), c - 1);
            int down = std::min(bw.Lower(), dim - c);

            mi.Clear();
            mi.Append(c - up, c + down);
        }

    };

    template<typename TYPE>
    inline void Swap(BandMatrix<TYPE>& A, BandMatrix<TYPE>& B)
    {
        A.Swap(B);
    }

}

#include "BandMatrix.cpp"

#endif //BAND_MATRIX_H

