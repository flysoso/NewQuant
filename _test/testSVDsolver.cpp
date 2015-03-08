#include "testSVDsolver.h"

void testSVDsolver()
{
    using namespace std;
    using namespace NewQuant;

    default_random_engine dre;
    normal_distribution<Type> nd;


    int r = 20, c = 10;
    Matrix<Type> m1(r, c), m2(c, r);
    ConstantMatrix<Type> cmat1(r - c, c, 0.0), cmat2(c, r - c, 0.0);
    for (int i = 1; i <= m1.Nrows(); ++i)
    {
        for (int j = 1; j <= m1.Ncols(); ++j)
        {
            m1(i, j) = nd(dre);
        }
    }
    for (int i = 1; i <= m2.Nrows(); ++i)
    {
        for (int j = 1; j <= m2.Ncols(); ++j)
        {
            m2(i, j) = nd(dre);
        }
    }
    SVDsolver<Type> svd1(m1, 1e-7), svd2(m2, 1e-7);

    cout << "test1 :" << endl;
    cout << "V1" << endl;
    cout << setw(10) << svd1.V() << endl;
    cout << "U1" << endl;
    cout << setw(10) << svd1.U() << endl;
    cout << "Singular1" << endl;
    cout << setw(10) << svd1.SingularValue() << endl;
    cout << setw(10) << m1 - svd1.U()*(svd1.SingularValue() & cmat1)*t(svd1.V()) << endl;

    cout << "test2 :" << endl;
    cout << "V2" << endl;
    cout << setw(10) << svd2.V() << endl;
    cout << "U2" << endl;
    cout << setw(10) << svd2.U() << endl;
    cout << "Singular2" << endl;
    cout << setw(10) << svd2.SingularValue() << endl;
    cout << setw(10) << m2 - svd2.U()*(svd2.SingularValue() | cmat2)*t(svd2.V()) << endl;

    cout << "TEST IS OVER" << endl;
}

