#include "testRegression.h"

void testRegression()
{
    using namespace std;
    using namespace NewQuant;

    default_random_engine dre;
    normal_distribution<Type> nd(0.0, 1.0), ndx(0.0, 1.0);

    int n = 30;
    ColumnVector<Type> X(n), Y(n), Z(n);
    for (int i = 1; i <= n; ++i)
    {
        X(i) = ndx(dre);
        Z(i) = ndx(dre);
        Y(i) = 1.20 + 0.5*X(i) + 1.2*Z(i) + 2.3*X(i)*Z(i) + nd(dre);
    }

    Constant<Type> c1(1.0), c2(2.0);
    Variable<Type> x1(1), x2(2);

    RegressionExpression<Type> regr;
    regr << c1 << x1 << x2 << x1*x2;

    RegressionData<Type> rd(Y, X | Z, regr);
    LinearRegression<Type> lr(rd);
    RidgeRegression<Type> rr(rd, 1.0);
    lr.ParameterTest(0.05);
    rr.ParameterTest(0.05);

    cout << "Y = 1.2 + 0.5X1 + 1.2X2 + 2.3X1X2 + e" << endl;
    cout << "Linear Regression :" << endl;
    cout << setprecision(5);
    cout << lr.ParameterInformation() << endl;
    cout << lr.R_Square() << endl;

    cout << "Ridge Regression :" << endl;
    cout << rr.ParameterInformation() << endl;
    cout << rr.R_Square() << endl;

    cout << "TEST IS OVER" << endl;

}
