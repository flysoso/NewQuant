#ifndef PARAMETRIC_REGRESSION_H
#define PARAMETRIC_REGRESSION_H

#include "RegressionData.h"
#include "ParameterInformation.h"
#include "../MatrixComputation/Array.h"
#include "../MatrixComputation/ColumnVector.h"
#include "../StatisticsComputation/F.h"
#include "../StatisticsComputation/Student.h"

namespace NewQuant
{
    template<typename TYPE>
    class ParametricRegression
    {
    protected:
        const RegressionData<TYPE> &data;
        ColumnVector<TYPE> parameter;
        ColumnVector<TYPE> residual;
        ParameterInformation<TYPE> para_inform;
        Array<TYPE> variable_var;
        TYPE r_square;

        void ComputeR_Square();
    public:
        ParametricRegression(const RegressionData<TYPE> &d) :
            data(d), parameter(d.VariableNum()),
            residual(d.SampleNum()), para_inform(d.VariableNum()),
            variable_var(d.VariableNum())
        {}

        virtual ~ParametricRegression(){}

        const RegressionData<TYPE> & Data() const
        {
            return data;
        }

        const ColumnVector<TYPE> & Parameter() const
        {
            return parameter;
        }

        const ColumnVector<TYPE> & Residual() const
        {
            return residual;
        }

        const ParameterInformation<TYPE> & ParameterInformation() const
        {
            return para_inform;
        }

        const TYPE & R_Square() const
        {
            return r_square;
        }

        void ParameterTest(const TYPE &);
    };

    template<typename TYPE>
    void ParametricRegression<TYPE>::ComputeR_Square()
    {
        static const TYPE one(1);
        TYPE s1 = Var(residual);
        TYPE s2 = Var(data.DependentVariable());
        r_square = one - Var(residual) / Var(data.DependentVariable());
    }

    template<typename TYPE>
    void ParametricRegression<TYPE>::ParameterTest(const TYPE &a)
    {
        static const TYPE one(1), two(2), zero(0);
        assert(zero < a&&a < one);
        static const F_Cdf<TYPE> F;
        static const StudentQuantile<TYPE> T;
        TYPE S = Norm2(residual);
        TYPE n(residual.Length()), p(parameter.Length());
        TYPE t;

        for (int i = 1; i <= para_inform.Size(); ++i)
        {
            para_inform(i).Value(parameter(i));

            t = parameter(i)*std::sqrt(n - p) / (std::sqrt(variable_var(i))*S);
            para_inform(i).T_Ratio(t);

            t = F(one, n - p, para_inform(i).F_Ratio());
            para_inform(i).P_Value(one - t);

            para_inform(i).Sd(std::sqrt(variable_var(i) / (n - p))*S);

            t = parameter(i) - std::sqrt(variable_var(i) / (n - p))*S*T(n - p, a / two);
            para_inform(i).Upper(t);

            t = parameter(i) - std::sqrt(variable_var(i) / (n - p))*S*T(n - p, one - a / two);
            para_inform(i).Lower(t);

            para_inform(i).Significance(para_inform(i).P_Value() < a);
        }
    }
}

#endif //PARAMETRIC_REGRESSION_H
