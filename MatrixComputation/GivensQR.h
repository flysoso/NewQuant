#ifndef GIVENS_QR_H
#define GIVENS_QR_H

#include "QRsolver.h"
#include "ColumnVector.h"
#include "RowVector.h"
#include "GetSubMatrix.h"
#include "ConstGetSubMatrix.h"
#include "TransposedMatrix.h"
#include "ProgramException.h"

namespace NewQuant
{
    template<typename TYPE> class BaseMatrix;
    template<typename TYPE> class GeneralMatrix;

    template<typename TYPE>
    class GivensQR :public QRsolver < TYPE >
    {
    private:
        void GivensMatrix(const TYPE &, const TYPE &, TYPE &, TYPE &) const;

        void GivensTransform();

        void RowGivensTransform(const TYPE &, const TYPE &, const int &, const int &, const int &, const int &);
        //mat = t(cs_mat)*mat, cs_mat=[c, s; -s, c]
        void ColGivensTransform(const TYPE &, const TYPE &, const int &, const int &);
        //mat = mat*cs_mat, cs_mat=[c, s; -s, c]
    public:
        GivensQR(const BaseMatrix<TYPE> &bm, const TYPE &e) :
            QRsolver<TYPE>(bm, e)
        {
            for (int i = 1; i <= QRsolver<TYPE>::combine.Nrows(); ++i)
            {
                for (int j = 1; j <= QRsolver<TYPE>::combine.Ncols(); ++j)
                {
                    QRsolver<TYPE>::combine(i, j) = bm(i, j);
                }
            }
            GivensTransform();
        }

        ~GivensQR(){}

        void SolveLS(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;
    };

    template<typename TYPE>
    void GivensQR<TYPE>::GivensMatrix(const TYPE &a, const TYPE &b, TYPE &c, TYPE &s) const
    {
        static const TYPE one(1), zero(0);

        if (fabs(b) <= QRsolver<TYPE>::epsilon)
        {
            c = one, s = zero;
        }
        else
        {
            TYPE t;
            if (fabs(b) >= fabs(a))
            {
                t = -a / b;
                s = one / (sqrt(one + t*t)), c = t*s;
            }
            else
            {
                t = -b / a;
                c = one / (sqrt(one + t*t)), s = c*t;
            }
        }
    }


    template<typename TYPE>
    void GivensQR<TYPE>::GivensTransform()
    {
        QRcombine<TYPE> &A = QRsolver<TYPE>::combine;
        SquareMatrix<TYPE> &Q = QRsolver<TYPE>::qr_q;
        const TYPE &e = QRsolver<TYPE>::epsilon;
        int m = A.Nrows(), n = A.Ncols();

        SquareMatrix<TYPE> givens_mat(2);
        Matrix<TYPE> temp;
        TYPE c, s;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = m; j >= i + 1; --j)
            {
                GivensMatrix(A(j - 1, i), A(j, i), c, s);
                RowGivensTransform(c, s, j - 1, j, i, n);
                ColGivensTransform(c, s, j - 1, j);
            }
            if (fabs(A(i, i)) <= e)
            {
                LeastSquareSolver<TYPE>::fail = true;
                return;
            }
        }
    }

    template<typename TYPE>
    void GivensQR<TYPE>::RowGivensTransform(const TYPE &c, const TYPE &s, const int &r1, const int &r2, const int &c1, const int &c2)
    {
        assert(r1 + 1 == r2);
        QRcombine<TYPE> &mat = QRsolver<TYPE>::combine;
        TYPE t1, t2;
        for (int i = c1; i <= c2; ++i)
        {
            t1 = mat(r1, i), t2 = mat(r2, i);
            mat(r1, i) = c*t1 - s*t2;
            mat(r2, i) = s*t1 + c*t2;
        }
    }

    template<typename TYPE>
    void GivensQR<TYPE>::ColGivensTransform(const TYPE &c, const TYPE &s, const int &c1, const int &c2)
    {
        assert(c1 + 1 == c2);
        SquareMatrix<TYPE> &mat = QRsolver<TYPE>::qr_q;
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
    void GivensQR<TYPE>::SolveLS(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const
    {
        const SquareMatrix<TYPE> &Q = QRsolver<TYPE>::qr_q;
        const UpperTriangularMatrix<TYPE> &R = QRsolver<TYPE>::qr_r;
        assert(in.Nrows() == Q.Nrows());
        assert(in.Ncols() == out.Ncols());
        assert(out.Nrows() == R.Ncols());

        if (LeastSquareSolver<TYPE>::IsFailed())
        {
            throw ProgramException("This Matrix Is Column Rank Deficiency", QRsolver<TYPE>::mat);
        }
        int m = in.Ncols(), n = R.Ncols();
        R.Solve(c_sub(t(Q)*in, 1, n, 1, m), out);
    }
}
#endif //GIVENS_QR_H
