#ifndef JACOBI_SOLVER_H
#define JACOBI_SOLVER_H

#include "EigenSolver.h"
#include "MatrixExpression.h"
#include "SquareMatrix.h"
#include "SymmetricMatrix.h"
#include "DiagonalMatrix.h"
#include "MultipliedMatrix.h"
#include "TransposedMatrix.h"

namespace NewQuant
{
    template<typename TYPE> class JacobiCombine;

    template<typename TYPE>
    class JacobiSolver :public EigenSolver < TYPE >
    {
    protected:
        SymmetricMatrix<TYPE> sym_mat;
        DiagonalMatrix<TYPE> eigen_value_mat;
        SquareMatrix<TYPE> eigen_vec_mat;
        JacobiCombine<TYPE> combine;
        TYPE epsilon;

        JacobiSolver(const BaseMatrix<TYPE> &, const TYPE &);

        void JacobiMatrix(const int &, const int &, TYPE &, TYPE &) const;

        void JacobiTransform(const int &, const int &, const TYPE &, const TYPE &);

        TYPE JacobiNorm() const;

        void ColJacobiTransform(const TYPE &, const TYPE &, const int &, const int &);
    public:
        ~JacobiSolver(){}

        const DiagonalMatrix<TYPE> & EigenValue()const
        {
            return eigen_value_mat;
        }

        const SquareMatrix<TYPE> & EigenVector()const
        {
            return eigen_vec_mat;
        }
    };

    template<typename TYPE>
    class JacobiCombine :public MatrixExpression < TYPE >
    {
    private:
        SymmetricMatrix<TYPE> &s_mat;
        DiagonalMatrix<TYPE> &d_mat;
    public:
        JacobiCombine(SymmetricMatrix<TYPE> &, DiagonalMatrix<TYPE> &);

        int Search(const GeneralMatrix<TYPE> &m) const
        {
            return s_mat.Search(m) + d_mat.Search(m);
        }

        void GetRowIndex(const int &r, MatrixIndex<TYPE> &mi) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            mi.Clear();
            mi.Append(1, MatrixExpression<TYPE>::ncols);
        }

        void GetColIndex(const int &c, MatrixIndex<TYPE> &mi) const
        {
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            mi.Clear();
            mi.Append(1, MatrixExpression<TYPE>::nrows);
        }

        TYPE operator () (const int &r, const int &c) const
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            if (r == c)
                return d_mat(r, c);
            else
                return s_mat(r, c);
        }

        TYPE & operator () (const int &r, const int &c)
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            if (r == c)
                return d_mat(r, c);
            else
                return s_mat(r, c);
        }
    };

    template<typename TYPE>
    JacobiSolver<TYPE>::JacobiSolver(const BaseMatrix<TYPE> &bm, const TYPE &e) :
        EigenSolver<TYPE>(),
        sym_mat(bm.Nrows()),
        eigen_value_mat(bm.Nrows()),
        eigen_vec_mat(bm.Nrows()),
        combine(sym_mat, eigen_value_mat),
        epsilon(e)
    {
        static const TYPE one(1), zero(0);
        for (int i = 1; i <= bm.Nrows(); ++i)
        {
            for (int j = 1; j <= i; ++j)
            {
                combine(i, j) = bm(i, j);
                if (i == j)
                {
                    eigen_vec_mat(i, j) = one;
                }
                else
                {
                    eigen_vec_mat(i, j) = zero;
                    eigen_vec_mat(j, i) = zero;
                }
            }
        }
    }

    template<typename TYPE>
    void JacobiSolver<TYPE>::JacobiMatrix(const int &p, const int &q, TYPE &c, TYPE &s) const
    {
        assert(0 < p&&p < q);
        static const TYPE zero(0), one(1), two(2);
        const JacobiCombine<TYPE> &A = combine;
        if (fabs(A(p, q)) <= epsilon)
        {
            c = one, s = zero;
        }
        else
        {
            TYPE tau = (A(q, q) - A(p, p)) / (two*A(p, q));
            TYPE t;
            if (tau >= zero)
            {
                t = one / (tau + std::sqrt(one + tau*tau));
            }
            else
            {
                t = -one / (-tau + std::sqrt(one + tau*tau));
            }
            c = one / std::sqrt(one + t*t);
            s = t*c;
        }
    }

    template<typename TYPE>
    void JacobiSolver<TYPE>::JacobiTransform(const int &p, const int &q, const TYPE &c, const TYPE &s)
    {
        assert(p < q);
        JacobiCombine<TYPE> &A = combine;
        TYPE tp, tq;
        TYPE tpp, tqq, tpq;
        tpp = A(p, p), tqq = A(q, q), tpq = A(p, q);
        static const TYPE two(2);
        for (int i = 1; i <= A.Nrows(); ++i)
        {
            if (i != p && i != q)
            {
                tp = A(i, p), tq = A(i, q);
                A(i, p) = c*tp - s*tq;
                A(i, q) = c*tq + s*tp;
            }
        }

        A(p, p) = c*c*tpp + s*s*tqq - two*c*s*tpq;
        A(q, q) = s*s*tpp + c*c*tqq + two*c*s*tpq;
        A(p, q) = (c*c - s*s)*tpq + c*s*(tpp - tqq);
    }

    template<typename TYPE>
    TYPE JacobiSolver<TYPE>::JacobiNorm() const
    {
        return Trace(t(sym_mat)*sym_mat);
    }

    template<typename TYPE>
    void JacobiSolver<TYPE>::ColJacobiTransform(const TYPE &c, const TYPE &s, const int &c1, const int &c2)
    {
        SquareMatrix<TYPE> &mat = JacobiSolver<TYPE>::eigen_vec_mat;
        int n = mat.Nrows();
        TYPE t1, t2;
        for (int i = 1; i <= n; ++i)
        {
            t1 = mat(i, c1), t2 = mat(i, c2);
            mat(i, c1) = c*t1 - s*t2;
            mat(i, c2) = s*t1 + c*t2;
        }
    }

    template<typename TYPE>
    JacobiCombine<TYPE>::JacobiCombine(SymmetricMatrix<TYPE> &s, DiagonalMatrix<TYPE> &i) :
        MatrixExpression<TYPE>(),
        s_mat(s),
        d_mat(i)
    {
        MatrixExpression<TYPE>::Set(s.Nrows(), s.Ncols());
        MatrixExpression<TYPE>::band_width.Set(s.Nrows() - 1, s.Ncols() - 1, true);
        static const TYPE zero(0);
        for (int i = 1; i <= s_mat.Nrows(); ++i)
        {
            s_mat(i, i) = zero;
        }
    }

}
#endif //JACOBI_SOLVER_H
