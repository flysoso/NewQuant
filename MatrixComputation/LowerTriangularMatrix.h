#ifndef LOWERTRIANULAR_MATRIX_H
#define LOWERTRIANULAR_MATRIX_H

#include "GeneralMatrix.h"
#include "IdentityMatrix.h"
#include "LowerTriangularSolver.h"

namespace NewQuant
{
    /// Lower triangular matrix.
    template <typename TYPE>
    class LowerTriangularMatrix : public GeneralMatrix < TYPE >
    {
    public:
        LowerTriangularMatrix();

        explicit LowerTriangularMatrix(const int &);

        LowerTriangularMatrix(const LowerTriangularMatrix<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::CopyMatrix(gm);
        }

        ~LowerTriangularMatrix() {}

        LowerTriangularMatrix<TYPE> & operator = (const BaseMatrix<TYPE> &);

        LowerTriangularMatrix<TYPE> & operator=(const LowerTriangularMatrix<TYPE>& m)
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
            std::shared_ptr<GeneralMatrix<TYPE> > inv;
            inv.reset(new LowerTriangularMatrix<TYPE>(n));
            IdentityMatrix<TYPE> imat(n);
            Solve(imat, *inv);
            return inv;
        }

        std::shared_ptr<LinearEquationSolver<TYPE> > MakeSolver() const
        {
            std::shared_ptr<LinearEquationSolver<TYPE> > solver(new LowerTriangularSolver<TYPE>(*this, Precision<TYPE>::GetPrecision()));
            return solver;
        }

        void Solve(const BaseMatrix<TYPE>&, BaseMatrix<TYPE>&) const;

        void operator+=(const LowerTriangularMatrix<TYPE>& M)
        {
            GeneralMatrix<TYPE>::PlusEqual(M);
        }

        void SP_eq(const LowerTriangularMatrix<TYPE>& M)
        {
            GeneralMatrix<TYPE>::SP_Equal(M);
        }

        void operator-=(const LowerTriangularMatrix<TYPE>& M)
        {
            GeneralMatrix<TYPE>::MinusEqual(M);
        }
        void Resize(const int &);                       // change dimensions

        void Swap(LowerTriangularMatrix<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::Swap(gm);
        }

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= GeneralMatrix<TYPE>::nrows);
            mi.Clear();
            mi.Append(1, r);
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= GeneralMatrix<TYPE>::ncols);
            mi.Clear();
            mi.Append(c, GeneralMatrix<TYPE>::ncols);
        }
    };

    template <typename TYPE>
    inline void Swap(LowerTriangularMatrix<TYPE>& A, LowerTriangularMatrix<TYPE>& B)
    {
        A.Swap(B);
    }
}
#include "LowerTriangularMatrix.cpp"

#endif //LOWERTRIANULAR_MATRIX_H
