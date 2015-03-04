#ifndef MATRIX_H
#define MATRIX_H

#include "GeneralMatrix.h"
#include "IdentityMatrix.h"
#include "SquareMatrix.h"
#include "IdentityMatrix.h"

#include "LUsolverPartialPivot.h"

namespace NewQuant
{

    template<typename TYPE> class MatrixIndex;
    template<typename TYPE> class SquareMatrix;
    template<typename TYPE> class LUsolverPartialPivot;

    /// The usual rectangular matrix.
    template <typename TYPE>
    class Matrix : public GeneralMatrix < TYPE >
    {
    public:
        Matrix();

        Matrix(const int &, const int &);                            // standard declaration

        Matrix(const int &, const int &, const TYPE &);

        Matrix(const int &, const int &, const TYPE *);

        Matrix(const Matrix<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::CopyMatrix(gm);
        }

        ~Matrix() {}

        Matrix<TYPE> & operator=(const BaseMatrix<TYPE> &);

        Matrix<TYPE> & operator=(const Matrix<TYPE>& m)
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

        void operator<<(const BaseMatrix<TYPE> &);

        void operator<<(const TYPE &x)
        {
            GeneralMatrix<TYPE>::operator<<(x);
        }

        void operator<<(const int &x)
        {
            GeneralMatrix<TYPE>::operator<<(x);
        }

        MatrixType Type() const;

        TYPE& operator()(const int &, const int &);

        TYPE operator()(const int &, const int &) const;

        std::shared_ptr<GeneralMatrix<TYPE> > MakeInv() const
        {
            assert(GeneralMatrix<TYPE>::nrows == GeneralMatrix<TYPE>::ncols);
            int n = GeneralMatrix<TYPE>::nrows;
            std::shared_ptr<GeneralMatrix<TYPE> > inv(new SquareMatrix<TYPE>(n));
            IdentityMatrix<TYPE> imat(n);
            Solve(imat, *inv);
            return inv;
        }

        std::shared_ptr<LinearEquationSolver<TYPE> > MakeSolver() const
        {
            assert(GeneralMatrix<TYPE>::nrows == GeneralMatrix<TYPE>::ncols);
            std::shared_ptr<LinearEquationSolver<TYPE> > solver(new LUsolverPartialPivot<TYPE>(*this, Precision<TYPE>::GetPrecision()));
            return solver;
        }

        void Solve(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;

        virtual void Resize(const int &, const int &);           // change dimensions

        virtual void Swap(Matrix<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::Swap(gm);
        }

        void SwapRow(const int &, const int &);

        void SwapCol(const int &, const int &);

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
    inline void Swap(Matrix<TYPE>& A, Matrix<TYPE>& B)
    {
        A.Swap(B);
    }
}
#include "Matrix.cpp"


#endif //MATRIX_H

