#ifndef LU_SOLVER_H
#define LU_SOLVER_H

#include "LinearEquationSolver.h"
#include "LowerTriangularMatrix.h"
#include "UpperTriangularMatrix.h"
#include "PermuteMatrix.h"
#include "MatrixExpression.h"

namespace NewQuant
{
    template<typename T> class LUcombine;
    template<typename T> class LowerTriangularMatrix;
    template<typename T> class UpperTriangularMatrix;
    template<typename T> class PermuteMatrix;

    template<typename TYPE>
    class LUsolver : public LinearEquationSolver < TYPE >
    {
    protected:
        LowerTriangularMatrix<TYPE> lm;
        UpperTriangularMatrix<TYPE> um;
        PermuteMatrix<TYPE> left, right;
        TYPE epsilon;
        LUcombine<TYPE> combine;
        const BaseMatrix<TYPE> &mat;

        LUsolver(const BaseMatrix<TYPE> &, const TYPE &);
    public:
        ~LUsolver() {}

        void GetLowerPart(GeneralMatrix<TYPE> &out) const
        {
            out << lm;
        }

        void GetUpperPart(GeneralMatrix<TYPE> &out) const
        {
            out << um;
        }

        const LowerTriangularMatrix<TYPE> & Lower() const
        {
            return lm;
        }

        const UpperTriangularMatrix<TYPE> & Upper() const
        {
            return um;
        }

        const PermuteMatrix<TYPE> & Left() const
        {
            return left;
        }

        const PermuteMatrix<TYPE> & Right() const
        {
            return right;
        }

        virtual LogAndSign<TYPE> LogDeterminant() const = 0;
    };

    template<typename TYPE>
    class LUcombine : public MatrixExpression < TYPE >
    {
    private:
        LowerTriangularMatrix<TYPE> &l;
        UpperTriangularMatrix<TYPE> &u;
        int dim;

        void operator=(const LUcombine<TYPE> &);
    public:
        LUcombine(LowerTriangularMatrix<TYPE> &lm, UpperTriangularMatrix<TYPE> &um);

        int Search(const GeneralMatrix<TYPE> &m) const
        {
            return l.Search(m) + u.Search(m);
        }

        int Dim() const
        {
            return dim;
        }

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            mi.Clear();
            mi.Append(1, dim);
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            mi.Clear();
            mi.Append(1, dim);
        }

        TYPE operator () (const int &r, const int &c) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            if (r > c)
                return l(r, c);
            else
                return u(r, c);
        }

        TYPE & operator () (const int &r, const int &c)
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            if (r > c)
                return l(r, c);
            else
                return u(r, c);
        }

        void SwapRow(const int &r1, const int &r2)
        {
            assert(r1 > 0 && r1 <= MatrixExpression<TYPE>::nrows);
            assert(r2 > 0 && r2 <= MatrixExpression<TYPE>::nrows);
            TYPE t;
            for (int i = 1; i <= dim; ++i)
            {
                t = operator()(r1, i);
                operator()(r1, i) = operator()(r2, i);
                operator()(r2, i) = t;
            }
        }

        void SwapRow(const int &r1, const int &r2, const int &c1, const int &c2)
        {
            assert(r1 > 0 && r1 <= MatrixExpression<TYPE>::nrows);
            assert(r2 > 0 && r2 <= MatrixExpression<TYPE>::nrows);
            assert(c1 > 0 && c1 <= MatrixExpression<TYPE>::ncols);
            assert(c2 > 0 && c2 <= MatrixExpression<TYPE>::ncols);
            TYPE t;
            for (int i = c1; i <= c2; ++i)
            {
                t = operator()(r1, i);
                operator()(r1, i) = operator()(r2, i);
                operator()(r2, i) = t;
            }
        }

        void SwapCol(const int &c1, const int &c2)
        {
            assert(c1 > 0 && c1 <= MatrixExpression<TYPE>::ncols);
            assert(c2 > 0 && c2 <= MatrixExpression<TYPE>::ncols);
            TYPE t;
            for (int i = 1; i <= dim; ++i)
            {
                t = operator()(i, c1);
                operator()(i, c1) = operator()(i, c2);
                operator()(i, c2) = t;
            }
        }

        void SwapCol(const int &c1, const int &c2, const int &r1, const int &r2)
        {
            assert(r1 > 0 && r1 <= MatrixExpression<TYPE>::nrows);
            assert(r2 > 0 && r2 <= MatrixExpression<TYPE>::nrows);
            assert(c1 > 0 && c1 <= MatrixExpression<TYPE>::ncols);
            assert(c2 > 0 && c2 <= MatrixExpression<TYPE>::ncols);
            TYPE t;
            for (int i = r1; i <= r2; ++i)
            {
                t = operator()(i, c1);
                operator()(i, c1) = operator()(i, c2);
                operator()(i, c2) = t;
            }
        }
    };

}
#include "LUsolver.cpp"


#endif //LU_SOLVER_H
