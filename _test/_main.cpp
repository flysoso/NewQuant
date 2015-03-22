#include <fstream>

#include "testBandMatrix.h"
#include "testLowerBandMatrix.h"
#include "testUpperBandMatrix.h"
#include "testConstantMatrix.h"
#include "testDiagonalMatrix.h"
#include "testIdentityMatrix.h"
#include "testLowerTriangularMatrix.h"
#include "testUpperTriangularMatrix.h"
#include "testSymmetricMatrix.h"
#include "testSymmetricBandMatrix.h"
#include "testMatrix.h"
#include "testVector.h"
#include "testSquareMatrix.h"
#include "testPermuteMatrix.h"
#include "testTridiagonalMatrix.h"
#include "testLeastSquareSolver.h"
#include "testEigenSolver.h"
#include "testSVDsolver.h"
#include "testSDEandSP.h"
#include "testRegression.h"
/*---------------*/
/*
int main()
{
using namespace std;
using namespace NewQuant;

clock_t t1, t2;
default_random_engine dre;
dre.seed(102);
normal_distribution<Type> nd(0.0, 1.0), ndx(0.0, 1.0);

int n = 300;
ColumnVector<Type> X(n), Y(n), Z(n);
for (int i = 1; i <= n; ++i)
{
X(i) = ndx(dre);
Z(i) = ndx(dre);
Y(i) = 0.5*X(i) + 1.2*Z(i) + 2.3*X(i)*Z(i) + nd(dre);
}
//testSDEandSP();
Constant<Type> c1(1.0), c2(2.5);
Variable<Type> x1(1), x2(2);

RegressionExpression<Type> regr;
regr << x1 << x2 << x1*x2;
t1 = clock();
RegressionData<Type> rd(Y, X | Z, regr);
//cout << setw(10) << rd.Data() << endl;
//CyclicJacobiSolver<Type> jac(t(rd.Data())*rd.Data(), 0.00001);
//cout << setw(10) << jac.EigenValue() << endl;
LinearRegression<Type> lr(rd);
//RidgeRegression<Type> lr(rd, 200.0);
lr.ParameterTest(0.05);
t2 = clock();
cout << lr.Parameter() << endl;
cout << lr.ParameterInformation() << endl;
cout << lr.R_Square() << endl;

cout << t2 - t1 << endl;

return EXIT_SUCCESS;
}
*/


int main()
{
    using namespace std;
    using namespace NewQuant;

    try
    {
        /**/
        testSymmetricMatrix();
        testBandMatrix();
        testLowerBandMatrix();
        testUpperBandMatrix();
        testConstantMatrix();
        testDiagonalMatrix();
        testIdentityMatrix();
        testLowerTriangularMatrix();
        testUpperTriangularMatrix();
        testSymmetricBandMatrix();
        testMatrix();
        testVector();
        testSquareMatrix();
        testPermuteMatrix();
        testTridiagonalMatrix();
        testLeastSquareSolver();
        testEigenSolver();
        testSVDsolver();
        testSDEandSP();
        testRegression();
    }
    catch (BaseException &be)
    {
        cout << be.what() << endl;
        Singleton<Tracer>::Instance()->PrintTrace();
    }

    return EXIT_SUCCESS;
}


