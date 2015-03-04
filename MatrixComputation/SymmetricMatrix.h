#ifndef SYMMETRIC_MATRIX_H
#define SYMMETRIC_MATRIX_H

#include "GeneralMatrix.h"
#include "IdentityMatrix.h"

#include "LUsolverPartialPivot.h"

namespace NewQuant
{
    /// Symmetric matrix.
    template <typename TYPE>
    class SymmetricMatrix : public GeneralMatrix < TYPE >
    {
    public:
        SymmetricMatrix();

        explicit SymmetricMatrix(const int &);

        SymmetricMatrix(const SymmetricMatrix<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::CopyMatrix(gm);
        }

        ~SymmetricMatrix() {}

        SymmetricMatrix<TYPE> & operator=(const BaseMatrix<TYPE>&);

        SymmetricMatrix<TYPE> & operator=(const SymmetricMatrix<TYPE>& m)
        {
            if (&m == this)
            {
                return *this;
            }
            GeneralMatrix<TYPE>::CopyMatrix(m);
            return *this;
        }

        void operator<<(const BaseMatrix<TYPE>&);

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
            std::shared_ptr<GeneralMatrix<TYPE> > inv(new SymmetricMatrix<TYPE>(n));
            IdentityMatrix<TYPE> imat(n);
            Solve(imat, *inv);
            return inv;
        }

        std::shared_ptr<LinearEquationSolver<TYPE> > MakeSolver() const
        {
            std::shared_ptr<LinearEquationSolver<TYPE> > solver(new LUsolverPartialPivot<TYPE>(*this, Precision<TYPE>::GetPrecision()));
            return solver;
        }

        void Solve(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;

        void Resize(const int &);                           // change dimensions

        void operator+=(const SymmetricMatrix<TYPE>& M)
        {
            GeneralMatrix<TYPE>::PlusEqual(M);
        }

        void SP_eq(const SymmetricMatrix<TYPE>& M)
        {
            GeneralMatrix<TYPE>::SP_Equal(M);
        }

        void operator-=(const SymmetricMatrix<TYPE>& M)
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

        void Swap(SymmetricMatrix<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::Swap(gm);
        }

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= GeneralMatrix<TYPE>::nrows);
            mi.Clear();
            mi.Append(1, GeneralMatrix<TYPE>::ncols);
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= GeneralMatrix<TYPE>::ncols);
            mi.Clear();
            mi.Append(1, GeneralMatrix<TYPE>::nrows);
        }
    };

    template <typename TYPE>
    inline void Swap(SymmetricMatrix<TYPE>& A, SymmetricMatrix<TYPE>& B)
    {
        A.Swap(B);
    }
}
#include "SymmetricMatrix.cpp"

#endif //SYMMETRIC_MATRIX_H


