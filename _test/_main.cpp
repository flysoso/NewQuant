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
/*---------------*/
#include "../MatrixComputation/Matrix.h"
#include "../MatrixComputation/ColumnVector.h"
#include "../MatrixComputation/ConstantMatrix.h"

#include "../MatrixComputation/NormalEquationSolver.h"
#include "../MatrixComputation/HouseholderQR.h"
#include "../MatrixComputation/HouseholderQRpivot.h"

#include "../MatrixComputation/SubtractedMatrix.h"
#include "../MatrixComputation/StackedMatrix.h"
#include "../MatrixComputation/InvScaledMatrix.h"
#include "../MatrixComputation/GivensQR.h"



int main()
{
    using namespace std;
    try
    {
        try
        {
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
