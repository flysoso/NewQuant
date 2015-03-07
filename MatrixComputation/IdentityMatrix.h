#ifndef IDENTIFY_MATRIX_H
#define IDENTIFY_MATRIX_H

#include "GeneralMatrix.h"
#include "IdentitySolver.h"
#include "SingularException.h"

namespace NewQuant
{
    /// Identity matrix.
    template<typename TYPE>
    class IdentityMatrix : public GeneralMatrix < TYPE >
    {
    public:
        IdentityMatrix() : GeneralMatrix<TYPE>(1, 1, 1)
        {
            static const TYPE one(1);
            GeneralMatrix<TYPE>::band_width.Set(0, 0, true);
            GeneralMatrix<TYPE>::store[0] = one;
        }

        explicit IdentityMatrix(const int &n) : GeneralMatrix<TYPE>(n, n, 1)
        {
            static const TYPE one(1);
            GeneralMatrix<TYPE>::band_width.Set(0, 0, true);
            GeneralMatrix<TYPE>::store[0] = one;
        }

        IdentityMatrix(const int &n, const TYPE &x) : GeneralMatrix<TYPE>(n, n, 1)
        {
            GeneralMatrix<TYPE>::store[0] = x;
            GeneralMatrix<TYPE>::band_width.Set(0, 0, true);
        }

        IdentityMatrix(const IdentityMatrix<TYPE>& gm)
        {
            GeneralMatrix<TYPE>::CopyMatrix(gm);
        }

        ~IdentityMatrix() {}

        IdentityMatrix<TYPE> & operator=(const BaseMatrix<TYPE>&);

        IdentityMatrix<TYPE> & operator=(const IdentityMatrix<TYPE> &m)
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

        TYPE& operator()(const int &, const int &);          // access element

        TYPE& operator()(const int &);                       // access element

        TYPE operator()(const int &, const int &) const;     // access element

        TYPE operator()(const int &) const;                  // access element

        MatrixType Type() const;

        TYPE Trace() const;

        std::shared_ptr<GeneralMatrix<TYPE> > MakeInv() const
        {
            std::shared_ptr<GeneralMatrix<TYPE> > inv;
            TYPE x = GeneralMatrix<TYPE>::store[0];
            const static TYPE one(1);
            if (fabs(x) <= Precision<TYPE>::GetPrecision())
            {
                Singleton<Tracer>::Instance()->AddMessage("IdentityMatrix::MakeInv()");
                throw SingularException(*this);
            }
            else
            {
                inv.reset(new IdentityMatrix<TYPE>(GeneralMatrix<TYPE>::nrows, one / x));
            }
            return inv;
        }

        std::shared_ptr<LinearEquationSolver<TYPE> > MakeSolver() const
        {
            std::shared_ptr<LinearEquationSolver<TYPE> > solver(new IdentitySolver<TYPE>(*this, Precision<TYPE>::GetPrecision()));
            return solver;
        }

        void Solve(const BaseMatrix<TYPE>&, BaseMatrix<TYPE>&) const;

        void Resize(const int &);

        void Swap(IdentityMatrix<TYPE>& gm)
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
    inline void Swap(IdentityMatrix<TYPE>& A, IdentityMatrix<TYPE>& B)
    {
        A.Swap(B);
    }
}
#include "IdentityMatrix.cpp"

#endif //IDENTIFY_MATRIX_H


