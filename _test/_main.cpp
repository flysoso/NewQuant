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

/*---------------*/

#include "../MathematicsExpresssion/ConstantAndVariable.h"
#include "../MathematicsExpresssion/BinaryExpression.h"
#include "../MathematicsExpresssion/UnitaryExpression.h"
#include "../MathematicsExpresssion/MathExpression.h"

#include "../MatrixComputation/ClassicalJacobiSolver.h"
#include "../MatrixComputation/CyclicJacobiSolver.h"
#define NDEBUG


int main()
{
    using namespace std;
    using namespace NewQuant;
    try
    {
        try
        {

            /*testSymmetricMatrix();
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
            */
            testEigenSolver();
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

