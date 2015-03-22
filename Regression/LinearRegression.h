#ifndef LINEAR_REGRESSION_H
#define LINEAR_REGRESSION_H

#include "ParametricRegression.h"
#include "../MatrixComputation/NormalEquationSolver.h"
#include "../MatrixComputation/SubtractedMatrix.h"

namespace NewQuant
{
    template<typename TYPE>
    class LinearRegression :public ParametricRegression < TYPE >
    {
    private:
        void Regression();
    public:
        LinearRegression(const RegressionData<TYPE> &d) :
            ParametricRegression<TYPE>(d)
        {
            Regression();
        }
        ~LinearRegression(){}
    };

    template<typename TYPE>
    void LinearRegression<TYPE>::Regression()
    {
        const Matrix<TYPE> &X = ParametricRegression<TYPE>::data.Data();
        const ColumnVector<TYPE> &Y = ParametricRegression<TYPE>::data.DependentVariable();
        ColumnVector<TYPE> &P = ParametricRegression<TYPE>::parameter;
        ColumnVector<TYPE> &R = ParametricRegression<TYPE>::residual;
        Array<TYPE> &V = ParametricRegression<TYPE>::variable_var;

        NormalEquationSolver<TYPE> nes(X, Precision<TYPE>::GetPrecision());

        nes.SolveLS(Y, P);

        std::shared_ptr<GeneralMatrix<TYPE>> inv = (t(X)*X).MakeInv();

        R = Y - X*P;

        for (int i = 1; i <= X.Ncols(); ++i)
        {
            V(i) = (*inv)(i, i);
        }

        ParametricRegression<TYPE>::ComputeR_Square();
    }
}



#endif //LINEAR_REGRESSION_H
