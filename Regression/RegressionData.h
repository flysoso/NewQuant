#ifndef REGRESSION_DATA_H
#define REGRESSION_DATA_H

#include "../MatrixComputation/Matrix.h"
#include "../MatrixComputation/ColumnVector.h"
#include "../MatrixComputation/ConstGetRowColMatrix.h"
#include "RegressionExpression.h"

namespace NewQuant
{
    template<typename TYPE>
    class RegressionData
    {
    private:
        Matrix<TYPE> data;
        ColumnVector<TYPE> dependent;

    public:
        RegressionData(const BaseMatrix<TYPE> &bv, const int &c) :
            data(bv.Nrows(), c)
        {
            dependent = bv;
        }

        RegressionData(const BaseMatrix<TYPE> &bv, const BaseMatrix<TYPE> &bm)
        {
            data = bm, dependent = bv;
        }

        RegressionData(const BaseMatrix<TYPE> &bv, const BaseMatrix<TYPE> &bm, const RegressionExpression<TYPE> &re)
        {
            dependent = bv;
            int r = bm.Nrows(), c = re.Size();
            data.Resize(r, c);

            for (int i = 1; i <= r; ++i)
            {
                for (int j = 1; j <= c; ++j)
                {
                    data(i, j) = re(j)[para<TYPE>(c_row(bm, i))];
                }
            }
        }

        RegressionData(const RegressionData<TYPE> &rd) :data(rd.data),dependent(rd.dependent){}

        ~RegressionData(){}

        Matrix<TYPE> & Data()
        {
            return data;
        }

        const Matrix<TYPE> & Data() const
        {
            return data;
        }

        ColumnVector<TYPE> & DependentVariable()
        {
            return dependent;
        }

        const ColumnVector<TYPE> & DependentVariable() const
        {
            return dependent;
        }

        TYPE & operator () (const int &r, const int &c)
        {
            return data(r, c);
        }

        TYPE operator () (const int &r, const int &c) const
        {
            return data(r, c);
        }

        TYPE & operator () (const int &r)
        {
            return dependent(r);
        }

        TYPE operator () (const int &r) const
        {
            return dependent(r);
        }

        int SampleNum() const
        {
            return data.Nrows();
        }

        int VariableNum() const
        {
            return data.Ncols();
        }
    };
}

#endif //REGRESSION_DATA_H
