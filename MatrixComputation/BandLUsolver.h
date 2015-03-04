#ifndef BAND_LU_SOLVER_H
#define BAND_LU_SOLVER_H

#include "LinearEquationSolver.h"
#include "MatrixExpression.h"
#include "PermutedMatrix.h"

namespace NewQuant
{
    template<typename TYPE> class MatrixIndex;
    template <typename T> class BaseMatrix;
    template <typename T> class LowerBandMatrix;
    template <typename T> class UpperBandMatrix;
    template <typename T> class LowerTriangularMatrix;

    template <typename T> class BandLUcombine_LbUb;
    template <typename T> class BandLUcombine_LtUb;

    template <typename TYPE>
    class BandLUsolver : public LinearEquationSolver < TYPE >
    {
    protected:
        int lbw, ubw;
        TYPE epsilon;
        PermuteMatrix<TYPE> left, right;
        const BaseMatrix<TYPE> &mat;

        BandLUsolver(const BaseMatrix<TYPE> &, const TYPE &);

        BandLUsolver(const BaseMatrix<TYPE> &, const int &, const int &, const TYPE &);
    public:
        ~BandLUsolver() {}

        int LowerBandWidth() const
        {
            return lbw;
        }

        int UpperBandWidth() const
        {
            return ubw;
        }

        const PermuteMatrix<TYPE> & Left() const
        {
            return left;
        }

        const PermuteMatrix<TYPE> & Right() const
        {
            return right;
        }

        virtual void GetLowerPart(GeneralMatrix<TYPE> &) const = 0;

        virtual void GetUpperPart(GeneralMatrix<TYPE> &) const = 0;

        virtual LogAndSign<TYPE> LogDeterminant() const = 0;
    };

    template <typename TYPE>
    class BandLUcombine_LbUb : public MatrixExpression < TYPE >
    {
    private:
        LowerBandMatrix<TYPE> &l;
        UpperBandMatrix<TYPE> &u;
        int dim;

        void operator=(const BandLUcombine_LbUb<TYPE> &);
    public:
        BandLUcombine_LbUb(LowerBandMatrix<TYPE> &lm, UpperBandMatrix<TYPE> &um);

        int Search(const GeneralMatrix<TYPE> &m) const
        {
            return 0;
        }

        int Dim() const
        {
            return dim;
        }

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            const MatrixBandWidth<TYPE> &bw = MatrixExpression<TYPE>::band_width;
            int left = std::min(bw.Lower(), r - 1);
            int right = std::min(bw.Upper(), dim - r);

            mi.Clear();
            mi.Append(r - left, r + right);
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            const MatrixBandWidth<TYPE> &bw = MatrixExpression<TYPE>::band_width;
            int up = std::min(bw.Upper(), c - 1);
            int down = std::min(bw.Lower(), dim - c);

            mi.Clear();
            mi.Append(c - up, c + down);
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

        template <typename FDTYPE> friend class BandLUsolver;

    };

    template <typename TYPE>
    class BandLUcombine_LtUb : public MatrixExpression < TYPE >
    {
    private:
        LowerTriangularMatrix<TYPE> &l;
        UpperBandMatrix<TYPE> &u;
        int dim;

        void operator=(const BandLUcombine_LtUb<TYPE> &);
    public:
        BandLUcombine_LtUb(LowerTriangularMatrix<TYPE> &lm, UpperBandMatrix<TYPE> &um);

        int Search(const GeneralMatrix<TYPE> &m) const
        {
            return 0;
        }

        int Dim() const
        {
            return dim;
        }

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            const MatrixBandWidth<TYPE> &bw = MatrixExpression<TYPE>::band_width;
            int left = std::min(bw.Lower(), r - 1);
            int right = std::min(bw.Upper(), dim - r);

            mi.Clear();
            mi.Append(r - left, r + right);
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            const MatrixBandWidth<TYPE> &bw = MatrixExpression<TYPE>::band_width;
            int up = std::min(bw.Upper(), c - 1);
            int down = std::min(bw.Lower(), dim - c);

            mi.Clear();
            mi.Append(c - up, c + down);
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

        template <typename FDTYPE> friend class BandLUsolver;

    };
}

#include "BandLUsolver.cpp"


#endif //BAND_LU_SOLVER_H
