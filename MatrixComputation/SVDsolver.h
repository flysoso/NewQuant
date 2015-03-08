#ifndef SVD_SOLVER_H
#define SVD_SOLVER_H

#include "Matrix.h"
#include "SquareMatrix.h"
#include "DiagonalMatrix.h"
#include "ColumnVector.h"
#include "RowVector.h"
#include "MatrixExpression.h"
#include "TransposedMatrix.h"
#include "GetSubMatrix.h"

namespace NewQuant
{
    template<typename TYPE> class SVDcombine;

    template<typename TYPE>
    class SVDsolver
    {
    protected:
        enum ShapeType{ row_long, col_long };
    protected:
        SquareMatrix<TYPE> um, vm;
        Matrix<TYPE> mat;
        DiagonalMatrix<TYPE> dm;
        SVDcombine<TYPE> combine;
        TYPE epsilon;
        ShapeType type;

        void Diagonalization();

        void HouseholderBidiagonalization();

        void HouseholderColVector(const MatrixExpression<TYPE> &, ColumnVector<TYPE> &, TYPE &) const;

        void HouseholderRowVector(const MatrixExpression<TYPE> &, RowVector<TYPE> &, TYPE &) const;

        void GolubKahanMethed(const int &, const int &);

        TYPE SpecificEigenValue(const TYPE &, const TYPE &, const TYPE &, const TYPE &) const;

        void GivensMatrix(const TYPE &, const TYPE &, TYPE &, TYPE &) const;

        void RowGivensTransform(const TYPE &, const TYPE &, const int &, const int &, const int &, const int &, BaseMatrix<TYPE> &);
        //mat = t(cs_mat)*mat, cs_mat=[c, s; -s, c]
        void RowGivensTransform(const TYPE &, const TYPE &, const int &, const int &, BaseMatrix<TYPE> &);
        //mat = t(cs_mat)*mat, cs_mat=[c, s; -s, c]
        void ColGivensTransform(const TYPE &, const TYPE &, const int &, const int &, BaseMatrix<TYPE> &);
        //mat = mat*cs_mat, cs_mat=[c, s; -s, c]
        void ColGivensTransform(const TYPE &, const TYPE &, const int &, const int &, const int &, const int &, BaseMatrix<TYPE> &);
        //mat = mat*cs_mat, cs_mat=[c, s; -s, c]
    public:
        SVDsolver(const BaseMatrix<TYPE> &, const TYPE &);

        const SquareMatrix<TYPE> & U() const
        {
            return um;
        }

        const SquareMatrix<TYPE> & V() const
        {
            return vm;
        }

        const DiagonalMatrix<TYPE> & SingularValue() const
        {
            return dm;
        }
    };

    template<typename TYPE>
    class SVDcombine :public MatrixExpression < TYPE >
    {
    private:
        Matrix<TYPE> &mat;
        DiagonalMatrix<TYPE> &diag;

    public:
        SVDcombine(Matrix<TYPE> &m, DiagonalMatrix<TYPE> &d, const int &r, const int c) :
            mat(m), diag(d)
        {
            if (r >= c)
            {
                MatrixExpression<TYPE>::Set(r, c);
            }
            else
            {
                MatrixExpression<TYPE>::Set(c, r);
            }
            if (r == c)
            {
                MatrixExpression<TYPE>::band_width.Set(r - 1, c - 1, true);
            }
            else
            {
                MatrixExpression<TYPE>::band_width.Set(-1, -1, false);
            }
        }

        void Set(Matrix<TYPE> &m, DiagonalMatrix<TYPE> &d)
        {
            mat = m, diag = d;
            MatrixExpression<TYPE>::Set(m.Nrows(), m.Ncols());
            if (m.Nrows() == m.Ncols())
            {
                MatrixExpression<TYPE>::band_width.Set(m.Nrows() - 1, m.Ncols() - 1, true);
            }
            else
            {
                MatrixExpression<TYPE>::band_width.Set(-1, -1, false);
            }
        }

        int Search(const GeneralMatrix<TYPE> &m) const
        {
            return mat.Search(m) + diag.Search(m);
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
                return diag(r, c);
            else
                return mat(r, c);
        }

        TYPE & operator () (const int &r, const int &c)
        {
            assert(r > 0 && r <= MatrixExpression<TYPE>::nrows);
            assert(c > 0 && c <= MatrixExpression<TYPE>::ncols);
            if (r == c)
                return diag(r, c);
            else
                return mat(r, c);
        }
    };

    template<typename TYPE>
    SVDsolver<TYPE>::SVDsolver(const BaseMatrix<TYPE> &bm, const TYPE &e) :
        epsilon(e), combine(mat, dm, bm.Nrows(), bm.Ncols())
    {
        int row = bm.Nrows(), col = bm.Ncols();
        if (row >= col)
        {
            um.Resize(row);
            vm.Resize(col);
            mat.Resize(row, col);
            dm.Resize(col);
            type = row_long;

            for (int i = 1; i <= row; ++i)
            {
                for (int j = 1; j <= col; ++j)
                {
                    combine(i, j) = bm(i, j);
                }
            }
            IdentityMatrix<Type> i1(row), i2(col);
            um << i1, vm << i2;
        }
        else
        {
            um.Resize(col);
            vm.Resize(row);
            mat.Resize(col, row);
            dm.Resize(row);
            type = col_long;

            for (int i = 1; i <= row; ++i)
            {
                for (int j = 1; j <= col; ++j)
                {
                    combine(j, i) = bm(i, j);
                }
            }
            IdentityMatrix<Type> i1(col), i2(row);
            um << i1, vm << i2;
        }

        HouseholderBidiagonalization();
        Diagonalization();
        if (type == col_long)
        {
            Swap(um, vm);
        }
    }

    template<typename TYPE>
    void SVDsolver<TYPE>::Diagonalization()
    {
        SVDcombine<TYPE> &B = combine;
        const TYPE &e = epsilon;
        static const TYPE zero(0);
        int p = 0, q = 0;
        int n = B.Ncols();

        while (q < n - 1)
        {
            for (int i = 1; i <= n - 1; ++i)
            {
                if (fabs(B(i, i + 1)) <= e*(fabs(B(i, i)) + fabs(B(i + 1, i + 1))))
                {
                    B(i, i + 1) = zero;
                }
            }
            p = 0, q = 0;
            for (int i = n; i >= 2; --i)
            {
                if (fabs(B(i - 1, i)) <= e)
                {
                    ++q;
                }
                else
                {
                    break;
                }
            }
            for (int i = 2; i <= n; ++i)
            {
                if (fabs(B(i - 1, i)) <= e)
                {
                    ++p;
                }
                else
                {
                    break;
                }
            }

            if (q < n)
            {
                bool has_zero = false;
                for (int i = p + 1; i <= n - q - 1; ++i)
                {
                    if (fabs(B(i, i)) <= e)
                    {
                        B(i, i + 1) = zero;
                        has_zero = true;
                    }
                }
                if (has_zero == false)
                {
                    GolubKahanMethed(p + 1, n - q);
                }
            }
        }
    }

    template<typename TYPE>
    void SVDsolver<TYPE>::HouseholderBidiagonalization()
    {
        SVDcombine<TYPE> &A = combine;
        SquareMatrix<TYPE> &U = um;
        SquareMatrix<TYPE> &V = vm;
        int m = A.Nrows(), n = A.Ncols();
        TYPE beta1, beta2;
        ColumnVector<TYPE> v1, v2;
        RowVector<TYPE> w1, w2;
        for (int i = 1; i <= n; ++i)
        {
            HouseholderColVector(sub(A, i, m, i, i), v1, beta1);
            w1 = t(v1)*sub(A, i, m, i, n);
            sub(A, i, m, i, n) -= beta1*v1*w1;

            if (i <= n - 2)
            {
                HouseholderRowVector(sub(A, i, i, i + 1, n), w2, beta2);
                v2 = sub(A, i, m, i + 1, n)*t(w2);
                sub(A, i, m, i + 1, n) -= beta2*v2*w2;
                v2 = sub(V, 1, n, i + 1, n)*t(w2);
                sub(V, 1, n, i + 1, n) -= beta2*v2*w2;
            }

            w1 = t(sub(U, 1, m, i, m)*v1);
            sub(U, 1, m, i, m) -= beta1*t(v1*w1);
        }
    }

    template<typename TYPE>
    void SVDsolver<TYPE>::HouseholderColVector(const MatrixExpression<TYPE> &x, ColumnVector<TYPE> &hv, TYPE &beta) const
    {
        assert(x.Ncols() == 1);
        static const TYPE one(1), zero(0), two(2);
        TYPE sigma = (t(x)*x)(1, 1) - x(1, 1)*x(1, 1);
        hv = x;
        hv(1) = one;

        const TYPE &e = SVDsolver<TYPE>::epsilon;

        if (sigma <= e)
        {
            beta = zero;
        }
        else
        {
            TYPE mu = std::sqrt(x(1, 1)*x(1, 1) + sigma), v;
            if (x(1, 1) <= zero)
            {
                hv(1) = x(1, 1) - mu;
            }
            else
            {
                hv(1) = -sigma / (x(1, 1) + mu);
            }
            v = hv(1);
            beta = two*v*v / (sigma + v*v);
            hv /= v;
        }
    }

    template<typename TYPE>
    void SVDsolver<TYPE>::HouseholderRowVector(const MatrixExpression<TYPE> &x, RowVector<TYPE> &hv, TYPE &beta) const
    {
        assert(x.Nrows() == 1);
        static const TYPE one(1), zero(0), two(2);
        TYPE sigma = (x*t(x))(1, 1) - x(1, 1)*x(1, 1);
        hv = x;
        hv(1) = one;

        const TYPE &e = SVDsolver<TYPE>::epsilon;

        if (sigma <= e)
        {
            beta = zero;
        }
        else
        {
            TYPE mu = std::sqrt(x(1, 1)*x(1, 1) + sigma), v;
            if (x(1, 1) <= zero)
            {
                hv(1) = x(1, 1) - mu;
            }
            else
            {
                hv(1) = -sigma / (x(1, 1) + mu);
            }
            v = hv(1);
            beta = two*v*v / (sigma + v*v);
            hv /= v;
        }
    }

    template<typename TYPE>
    void SVDsolver<TYPE>::GolubKahanMethed(const int &start, const int &end)
    {
        SVDcombine<TYPE> &B = combine;
        SquareMatrix<TYPE> &V = vm;
        SquareMatrix<TYPE> &U = um;
        TYPE mu;
        if (end >= 3)
        {
            mu = SpecificEigenValue(B(end - 2, end - 1), B(end - 1, end), B(end - 1, end - 1), B(end, end));
        }
        else if (end == 2)
        {
            static const TYPE zero(0);
            mu = SpecificEigenValue(zero, B(end - 1, end), B(end - 1, end - 1), B(end, end));
        }
        else
            return;
        TYPE t11 = B(start, start)*B(start, start);
        TYPE t12 = B(start, start)*B(start, start + 1);
        TYPE y = t11 - mu, z = t12;
        TYPE c, s;
        for (int k = start; k <= end - 1; ++k)
        {
            GivensMatrix(y, z, c, s);
            ColGivensTransform(c, s, start, k + 1, k, k + 1, B);
            ColGivensTransform(c, s, k, k + 1, V);

            y = B(k, k), z = B(k + 1, k);

            GivensMatrix(y, z, c, s);
            RowGivensTransform(c, s, k, k + 1, k, end, B);
            ColGivensTransform(c, s, k, k + 1, U);

            if (k < end - 1)
            {
                y = B(k, k + 1), z = B(k, k + 2);
            }

        }
    }

    template<typename TYPE>
    TYPE SVDsolver<TYPE>::SpecificEigenValue(const TYPE &blm, const TYPE &bmn, const TYPE &bmm, const TYPE &bnn) const
    {
        //m = n-1; l = m-1
        static const TYPE two(2), four(4);
        TYPE a = bmm*bmm + blm*blm;
        TYPE b = bmm*bmn;
        TYPE c = bnn*bnn + bmn*bmn;

        TYPE x1 = (a + c + std::sqrt((a - c)*(a - c) + four*b*b)) / two;
        TYPE x2 = (a + c - std::sqrt((a - c)*(a - c) + four*b*b)) / two;

        if (fabs(x1 - c) <= fabs(x2 - c))
        {
            return x1;
        }
        else
        {
            return x2;
        }
    }

    template<typename TYPE>
    void SVDsolver<TYPE>::GivensMatrix(const TYPE &a, const TYPE &b, TYPE &c, TYPE &s) const
    {
        static const TYPE one(1), zero(0);

        if (fabs(b) <= epsilon)
        {
            c = one, s = zero;
        }
        else
        {
            TYPE t;
            if (fabs(b) >= fabs(a))
            {
                t = -a / b;
                s = one / (std::sqrt(one + t*t)), c = t*s;
            }
            else
            {
                t = -b / a;
                c = one / (std::sqrt(one + t*t)), s = c*t;
            }
        }
    }

    template<typename TYPE>
    void SVDsolver<TYPE>::RowGivensTransform(const TYPE &c, const TYPE &s, const int &r1, const int &r2, const int &c1, const int &c2, BaseMatrix<TYPE> &mat)
    {
        assert(r1 + 1 == r2);
        TYPE t1, t2;
        for (int i = c1; i <= c2; ++i)
        {
            t1 = mat(r1, i), t2 = mat(r2, i);
            mat(r1, i) = c*t1 - s*t2;
            mat(r2, i) = s*t1 + c*t2;
        }
    }

    template<typename TYPE>
    void SVDsolver<TYPE>::RowGivensTransform(const TYPE &c, const TYPE &s, const int &r1, const int &r2, BaseMatrix<TYPE> &mat)
    {
        assert(r1 + 1 == r2);
        TYPE t1, t2;
        int n = mat.Ncols();
        for (int i = 1; i <= n; ++i)
        {
            t1 = mat(r1, i), t2 = mat(r2, i);
            mat(r1, i) = c*t1 - s*t2;
            mat(r2, i) = s*t1 + c*t2;
        }
    }

    template<typename TYPE>
    void SVDsolver<TYPE>::ColGivensTransform(const TYPE &c, const TYPE &s, const int &c1, const int &c2, BaseMatrix<TYPE> &mat)
    {
        assert(c1 + 1 == c2);
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
    void SVDsolver<TYPE>::ColGivensTransform(const TYPE &c, const TYPE &s, const int &r1, const int &r2, const int &c1, const int &c2, BaseMatrix<TYPE> &mat)
    {
        assert(c1 + 1 == c2);
        TYPE t1, t2;
        for (int i = r1; i <= r2; ++i)
        {
            t1 = mat(i, c1), t2 = mat(i, c2);
            mat(i, c1) = c*t1 - s*t2;
            mat(i, c2) = s*t1 + c*t2;
        }
    }

}

#endif //SVD_SOLVER_H
