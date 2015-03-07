#ifndef UPPERTRIANULAR_MATRIX_H
#define UPPERTRIANULAR_MATRIX_H

#include <memory>
#include "GeneralMatrix.h"
#include "UpperTriangularSolver.h"

namespace NewQuant
{
    /// Upper triangular matrix.
    template<typename TYPE>
    class UpperTriangularMatrix : public GeneralMatrix < TYPE >
    {
    public:
        UpperTriangularMatrix();

        explicit UpperTriangularMatrix(const int &);

        UpperTriangularMatrix(const UpperTriangularMatrix<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::CopyMatrix(gm);
        }

        ~UpperTriangularMatrix() {}

        UpperTriangularMatrix<TYPE> & operator = (const BaseMatrix<TYPE> &);

        UpperTriangularMatrix<TYPE> & operator=(const UpperTriangularMatrix<TYPE>& m)
        {
            if (&m == this)
            {
                return *this;
            }
            GeneralMatrix<TYPE>::CopyMatrix(m);
            return *this;
        }

        void operator << (const BaseMatrix<TYPE> &);

        void operator<<(const TYPE &x)
        {
            GeneralMatrix<TYPE>::operator<<(x);
        }

        void operator<<(const int &x)
        {
            GeneralMatrix<TYPE>::operator<<(x);
        }

        TYPE& operator()(const int &, const int &);                  // access element

        TYPE operator()(const int &, const int &) const;             // access element

        MatrixType Type() const;

        std::shared_ptr<GeneralMatrix<TYPE> > MakeInv() const
        {
            int n = GeneralMatrix<TYPE>::nrows;
            std::shared_ptr<GeneralMatrix<TYPE> > inv(new UpperTriangularMatrix<TYPE>(n));
            IdentityMatrix<TYPE> imat(n);
            Solve(imat, *inv);
            return inv;
        }

        std::shared_ptr<LinearEquationSolver<TYPE> > MakeSolver() const
        {
            std::shared_ptr<LinearEquationSolver<TYPE> > solver(new UpperTriangularSolver<TYPE>(*this, Precision<TYPE>::GetPrecision()));
            return solver;
        }

        void Solve(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;

        void Resize(const int &);                       // change dimensions

        void SP_eq(const UpperTriangularMatrix<TYPE>& M)
        {
            GeneralMatrix<TYPE>::SP_Equal(M);
        }

        void operator+=(const UpperTriangularMatrix<TYPE>& M)
        {
            GeneralMatrix<TYPE>::PlusEqual(M);
        }

        void operator-=(const UpperTriangularMatrix<TYPE>& M)
        {
            GeneralMatrix<TYPE>::MinusEqual(M);
        }

        void Swap(UpperTriangularMatrix<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::Swap(gm);
        }

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= GeneralMatrix<TYPE>::nrows);
            mi.Clear();
            mi.Append(r, GeneralMatrix<TYPE>::ncols);
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= GeneralMatrix<TYPE>::ncols);
            mi.Clear();
            mi.Append(1, c);
        }
    };

    template<typename TYPE>
    inline void Swap(UpperTriangularMatrix<TYPE>& A, UpperTriangularMatrix<TYPE>& B)
    {
        A.Swap(B);
    }
}
#include "UpperTriangularMatrix.cpp"

#endif //UPPERTRIANULAR_MATRIX_H
