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

/*---------------*/

#include "../MathematicsExpresssion/ConstantAndVariable.h"
#include "../MathematicsExpresssion/BinaryExpression.h"
#include "../MathematicsExpresssion/UnitaryExpression.h"
#include "../MathematicsExpresssion/MathExpression.h"
/*
int main()
{
    using namespace std;
    using namespace NewQuant;
    Matrix<Type> m(2, 3);
    m(1, 1) = 1.25, m(1, 2) = 2.3, m(1, 3) = 3.0;
    m(2, 1) = 4.0, m(2, 2) = 5.0, m(2, 3) = 6.0;
    //cout << m << endl;
    Constant<Type> c(3.0);
    Variable<Type> x1(1), x2(2), x3(3);
    MathExpression<Type> expr(x1 + x2 + x3);

    cout << expr[para<Type>(c_row(m, 2))] << endl;
}
*/

int main()
{
    using namespace std;
    using namespace NewQuant;
    try
    {
        try
        {
            /*
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
            */
            testLeastSquareSolver();
        }
        catch (BaseException &be)
        {
            cout << be.what() << endl;
            Singleton<Tracer>::Instance()->PrintTrace();
        }
    }
    catch (exception e)
    {
        cout << e.what() << endl;
    }

    return 0;
}
