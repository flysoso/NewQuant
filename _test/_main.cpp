
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

/*---------------*/

#include "../MathematicsExpresssion/ConstantAndVariable.h"
#include "../MathematicsExpresssion/BinaryExpression.h"
#include "../MathematicsExpresssion/UnitaryExpression.h"
#include "../MathematicsExpresssion/MathExpression.h"

#include "../SpecialFunction/Gamma.h"
#include "../SpecialFunction/LnGamma.h"
#include "../SpecialFunction/Beta.h"
#include "../SpecialFunction/IncompleteGamma.h"
#include "../SpecialFunction/IncompleteBeta.h"
#include "../SpecialFunction/ErrorFunction.h"
#include "../SpecialFunction/ComplementErrorFunction.h"

#include "../StatisticsComputation/Normal.h"
#include "../StatisticsComputation/Gamma.h"
#include "../StatisticsComputation/Beta.h"
#include "../StatisticsComputation/Cauchy.h"
#include "../StatisticsComputation/Student.h"

int main()
{
    using namespace std;
    using namespace NewQuant;

    default_random_engine dre;
    normal_distribution<Type> nd;

    Gamma<Type> gamma;
    Beta<Type> beta;
    IncompleteGamma<Type> igamma;
    IncompleteBeta<Type> ibeta;
    ErrorFunction<Type> error_f;
    InvErrorFunction<Type> ie;
    ComplementErrorFunction<Type> com_error;
    InvComplementErrorFunction<Type> inv_com_error;

    NormalPdf<Type> norm_pdf;
    NormalCdf<Type> norm_cdf;
    NormalQuantile<Type> norm_q;

    GammaPdf<Type> gamma_pdf;
    GammaCdf<Type> gamma_cdf;
    GammaQuantile<Type> gamma_q;

    BetaPdf<Type> beta_pdf;
    BetaCdf<Type> beta_cdf;
    BetaQuantile<Type> beta_q;

    StudentPdf<Type> t_pdf;
    StudentCdf<Type> t_cdf;
    StudentQuantile<Type> t_q;

    //cout << Pi<Type>::value() << endl;
    //cout << setw(25) << scientific << setprecision(20) << g(4.53) << endl;
    //cout << setw(25) << scientific << setprecision(20) << g(13) << endl;
    //cout << setw(25) << scientific << setprecision(20) << beta(2.3, 5.6) << endl;
    //cout << setw(25) << scientific << setprecision(20) << beta(5.0, 5.0) << endl;
    //cout << setw(25) << scientific << setprecision(20) << ib(5.0, 5.0, 0.2) << endl;
    //cout << setw(25) << scientific << setprecision(20) << error_f(ie(-0.192)) << endl;
    //cout << setw(25) << scientific << setprecision(20) << std::erf(ie(-0.192)) << endl;
    //cout << setw(25) << scientific << setprecision(20) << norm_pdf(-0.23, 1.5, 0.64) << endl;
    //cout << setw(25) << scientific << setprecision(20) << norm_cdf(-0.23, 1.5, 0.64) << endl;
    //cout << setw(25) << scientific << setprecision(20) << ie(0.952) << endl;
    //cout << setw(25) << scientific << setprecision(20) << error_f(ie(0.62)) << endl;
    //cout << setw(25) << scientific << setprecision(20) << beta_pdf(20.56, 30.23, 0.5) << endl;
    //cout << setw(25) << scientific << setprecision(20) << beta_cdf(20.56, 30.23, 0.5) << endl;
    //cout << setw(25) << scientific << setprecision(20) << beta_q(20.56, 30.23, 0.5) << endl;
    //cout << setw(25) << scientific << setprecision(20) << norm_q(20.56, 30.23, 0.235) << endl;
    //cout << setw(25) << scientific << setprecision(20) << norm_cdf(0.0, 1.0, norm_q(0.0, 1.0, 1e-2)) << endl;
    //cout << setw(25) << scientific << setprecision(20) << t_cdf(55.0, 2.0, 1.0, t_q(55.0, 2.0, 1.0, 0.05992)) << endl;


    return EXIT_SUCCESS;
}


/*
int main()
{
using namespace std;
using namespace NewQuant;
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
testLeastSquareSolver();
testEigenSolver();
testSVDsolver();

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

*/
