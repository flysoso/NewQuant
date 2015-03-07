#ifndef DIAGONAL_MATRIX_H
#define DIAGONAL_MATRIX_H

#include "GeneralMatrix.h"
#include "IdentityMatrix.h"
#include "DiagonalSolver.h"

namespace NewQuant
{
    template<typename TYPE> class IdentityMatrix;

    /// Diagonal matrix.
    template<typename TYPE>
    class DiagonalMatrix : public GeneralMatrix < TYPE >
    {
    public:
        DiagonalMatrix();

        DiagonalMatrix(const int &);

        DiagonalMatrix(const DiagonalMatrix<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::CopyMatrix(gm);
        }

        ~DiagonalMatrix() {}

        DiagonalMatrix<TYPE> & operator=(const BaseMatrix<TYPE> &);

        DiagonalMatrix<TYPE> & operator=(const DiagonalMatrix<TYPE>& m)
        {
            if (&m == this)
            {
                return *this;
            }
            GeneralMatrix<TYPE>::CopyMatrix(m);
            return *this;
        }

        void operator<<(const BaseMatrix<TYPE> &);

        void operator<<(const TYPE &x)
        {
            GeneralMatrix<TYPE>::operator<<(x);
        }

        void operator<<(const int &x)
        {
            GeneralMatrix<TYPE>::operator<<(x);
        }

        void operator+=(const DiagonalMatrix<TYPE> &M)
        {
            GeneralMatrix<TYPE>::PlusEqual(M);
        }

        void SP_eq(const DiagonalMatrix<TYPE> &M)
        {
            GeneralMatrix<TYPE>::SP_Equal(M);
        }

        void operator-=(const DiagonalMatrix<TYPE>& M)
        {
            GeneralMatrix<TYPE>::MinusEqual(M);
        }

        TYPE& operator()(const int &, const int &);

        TYPE& operator()(const int &);

        TYPE operator()(const int &, const int &) const;

        TYPE operator()(const int &) const;

        MatrixType Type() const;

        TYPE Trace() const;

        std::shared_ptr<GeneralMatrix<TYPE> > MakeInv() const
        {
            int n = GeneralMatrix<TYPE>::nrows;
            std::shared_ptr<GeneralMatrix<TYPE> > inv(new DiagonalMatrix<TYPE>(n));
            IdentityMatrix<TYPE> imat(n);
            Solve(imat, *inv);
            return inv;
        }

        std::shared_ptr<LinearEquationSolver<TYPE> > MakeSolver() const
        {
            std::shared_ptr<LinearEquationSolver<TYPE> > solver(new DiagonalSolver<TYPE>(*this, Precision<TYPE>::GetPrecision()));
            return solver;
        }

        void Solve(const BaseMatrix<TYPE>&, BaseMatrix<TYPE>&) const;

        void Resize(const int &);                       // change dimensions

        void Swap(DiagonalMatrix<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::Swap(gm);
        }

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= GeneralMatrix<TYPE>::nrows);
            mi.Clear();
            mi.Append(r, r);
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= GeneralMatrix<TYPE>::ncols);
            mi.Clear();
            mi.Append(c, c);
        }
    };

    template<typename TYPE>
    inline void Swap(DiagonalMatrix<TYPE>& A, DiagonalMatrix<TYPE>& B)
    {
        A.Swap(B);
    }
}
#include "DiagonalMatrix.cpp"

#endif //DIAGONAL_MATRIX_H


