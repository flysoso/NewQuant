#ifndef RIDGE_REGRESSION_H
#define RIDGE_REGRESSION_H

#include "ParametricRegression.h"
#include "../MatrixComputation/SymmetricMatrix.h"
#include "../MatrixComputation/TransposedMatrix.h"
#include "../MatrixComputation/MultipliedMatrix.h"
#include "../MatrixComputation/SubtractedMatrix.h"
#include "../MatrixComputation/CholeskySolver.h"

namespace NewQuant
{
    template<typename TYPE>
    class RidgeRegression :public ParametricRegression < TYPE >
    {
    private:
        SymmetricMatrix<TYPE> ridge_mat;
        TYPE ridge;
        void Regression();
    public:
        RidgeRegression(const RegressionData<TYPE> &d,const TYPE &r) :
            ParametricRegression<TYPE>(d), ridge(r)
        {
            Regression();
        }

        ~RidgeRegression(){}
    };

    template<typename TYPE>
    void RidgeRegression<TYPE>::Regression()
    {
        const Matrix<TYPE> &X = ParametricRegression<TYPE>::data.Data();
        ridge_mat = t(X)*X;
        for (int i = 1; i <= ridge_mat.Nrows(); ++i)
        {
            ridge_mat(i, i) += ridge;
        }
        const ColumnVector<TYPE> &Y = ParametricRegression<TYPE>::data.DependentVariable();
        ColumnVector<TYPE> &P = ParametricRegression<TYPE>::parameter;
        ColumnVector<TYPE> &R = ParametricRegression<TYPE>::residual;
        Array<TYPE> &V = ParametricRegression<TYPE>::variable_var;

        CholeskySolver<TYPE> ch(ridge_mat, Precision<TYPE>::GetPrecision());
        ch.Solve(t(X)*Y, P);

        R = Y - X*P;

        std::shared_ptr<GeneralMatrix<TYPE>> inv = ridge_mat.MakeInv();
        for (int i = 1; i <= X.Ncols(); ++i)
        {
            V(i) = (*inv)(i, i);
        }

        ParametricRegression<TYPE>::ComputeR_Square();
    }
}



#endif //RIDGE_REGRESSION_H
