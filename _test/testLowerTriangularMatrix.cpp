#include "testLowerTriangularMatrix.h"

void testLowerTriangularMatrix()
{
    using namespace std;
    using namespace NewQuant;
    default_random_engine dre;
    normal_distribution<Type> nd;
    LowerTriangularMatrix<Type> low_tr1(10), low_tr2(10);

    for (int i = 1; i <= low_tr1.Nrows(); ++i)
    {
        for (int j = 1; j <= low_tr1.Ncols(); ++j)
        {
            low_tr1(i, j) = nd(dre);
        }
    }

    cout << "low_tr1(10)" << endl;
    cout << setw(10) << low_tr1 << endl;

    cout << "test low_tr2(10) << low_tr1" << endl;
    low_tr2 << low_tr1;
    cout << setw(10) << low_tr2 << endl;

    cout << "test low_tr2 = low_tr1" << endl;
    low_tr2 = low_tr1;
    cout << setw(10) << low_tr2 << endl;

    cout << "test low_tr2 = low_tr1+low_tr1" << endl;
    low_tr2 = low_tr1 + low_tr1;
    cout << setw(10) << low_tr2 << endl;

    cout << "test low_tr2 = 2.0*low_tr1" << endl;
    Type two(2);
    low_tr2 = two*low_tr1;
    cout << setw(10) << low_tr2 << endl;

    cout << "test low_tr2 = low_tr1*low_tr1" << endl;
    low_tr2 = low_tr1*low_tr1;
    cout << setw(10) << low_tr2 << endl;

    cout << "test MakeInv()" << endl;
    cout << "low_tr1.MakeInv() = " << endl;
    cout << setw(10) << *low_tr1.MakeInv() << endl;
    cout << "low_tr1.MakeInv() * low_tr1" << endl;
    cout << setw(10) << (*low_tr1.MakeInv())*low_tr1 << endl;

    cout << "test low_tr1.MakeInv() * low_tr2 - low_tr1" << endl;
    cout << setw(10) << *low_tr1.MakeInv() * low_tr2 - low_tr1 << endl;

    cout << "Swap(low_tr1,low_tr2)" << endl;
    Swap(low_tr1, low_tr2);
    cout << "low_tr1" << endl;
    cout << setw(10) << low_tr1 << endl;
    cout << "low_tr2" << endl;
    cout << setw(10) << low_tr2 << endl;

    cout << "t(low_tr2)" << endl;
    cout << setw(10) << t(low_tr2) << endl;

    Type d(1);
    for (int i = 1; i <= low_tr1.Nrows(); ++i)
    {
        d *= low_tr2(i, i);
    }
    cout << "test Determinant" << endl;
    cout << d << " = " << low_tr2.LogDeterminant().Value() << endl;

    cout << "TEST IS OVER" << endl;
}


