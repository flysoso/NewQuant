#ifndef HOUSEHOLDER_QR_H
#define HOUSEHOLDER_QR_H

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
    class HouseholderQR :public QRsolver < TYPE >
    {
    private:
        void HouseholderVector(const MatrixExpression<TYPE> &, ColumnVector<TYPE> &, TYPE &) const;

        void HouseholderTransform();
    public:
        HouseholderQR(const BaseMatrix<TYPE> &bm, const TYPE &e) :
            QRsolver<TYPE>(bm, e)
        {
            for (int i = 1; i <= QRsolver<TYPE>::combine.Nrows(); ++i)
            {
                for (int j = 1; j <= QRsolver<TYPE>::combine.Ncols(); ++j)
                {
                    QRsolver<TYPE>::combine(i, j) = bm(i, j);
                }
            }
            HouseholderTransform();
        }

        ~HouseholderQR(){}

        void SolveLS(const BaseMatrix<TYPE> &, BaseMatrix<TYPE> &) const;
    };

    template<typename TYPE>
    void HouseholderQR<TYPE>::HouseholderVector(const MatrixExpression<TYPE> &x, ColumnVector<TYPE> &hv, TYPE &beta) const
    {
        assert(x.Ncols() == 1);
        static const TYPE one(1), zero(0), two(2);
        TYPE sigma = (t(x)*x)(1, 1) - x(1, 1)*x(1, 1);
        hv = x;
        hv(1) = one;

        const TYPE &e = QRsolver<TYPE>::epsilon;

        if (sigma <= e)
        {
            beta = zero;
        }
        else
        {
            TYPE mu = sqrt(x(1, 1)*x(1, 1) + sigma), v;
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
    void HouseholderQR<TYPE>::HouseholderTransform()
    {
        QRcombine<TYPE> &A = QRsolver<TYPE>::combine;
        SquareMatrix<TYPE> &Q = QRsolver<TYPE>::qr_q;
        const TYPE &e = QRsolver<TYPE>::epsilon;
        int m = A.Nrows(), n = A.Ncols();
        TYPE beta;
        ColumnVector<TYPE> v;
        RowVector<TYPE> w;
        for (int i = 1; i <= n; ++i)
        {
            HouseholderVector(sub(A, i, m, i, i), v, beta);
            w = t(v)*sub(A, i, m, i, n);
            sub(A, i, m, i, n) -= beta*v*w;
            if (fabs(A(i, i)) <= e)
            {
                LeastSquareSolver<TYPE>::fail = true;
                return;
            }
            w = t(sub(Q, 1, m, i, m)*v);

            sub(Q, 1, m, i, m) -= beta*t(v*w);
        }
    }

    template<typename TYPE>
    void HouseholderQR<TYPE>::SolveLS(const BaseMatrix<TYPE> &in, BaseMatrix<TYPE> &out) const
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
#endif //HOUSEHOLDER_QR_H
