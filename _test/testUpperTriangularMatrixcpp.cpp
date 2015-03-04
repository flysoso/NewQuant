#include "testUpperTriangularMatrix.h"

void testUpperTriangularMatrix()
{
    using namespace std;
    using namespace NewQuant;
    default_random_engine dre;
    normal_distribution<Type> nd;
    UpperTriangularMatrix<Type> up_tr1(10), up_tr2(10);

    for (int i = 1; i <= up_tr1.Nrows(); ++i)
    {
        for (int j = 1; j <= up_tr1.Ncols(); ++j)
        {
            up_tr1(i, j) = nd(dre);
        }
    }

    cout << "up_tr1(10)" << endl;
    cout << setw(10) << up_tr1 << endl;

    cout << "test up_tr2(10) << up_tr1" << endl;
    up_tr2 << up_tr1;
    cout << setw(10) << up_tr2 << endl;

    cout << "test up_tr2 = up_tr1" << endl;
    up_tr2 = up_tr1;
    cout << setw(10) << up_tr2 << endl;

    cout << "test up_tr2 = up_tr1+up_tr1" << endl;
    up_tr2 = up_tr1 + up_tr1;
    cout << setw(10) << up_tr2 << endl;

    cout << "test up_tr2 = 2.0*up_tr1" << endl;
    Type two(2);
    up_tr2 = two*up_tr1;
    cout << setw(10) << up_tr2 << endl;

    cout << "test up_tr2 = up_tr1*up_tr1" << endl;
    up_tr2 = up_tr1*up_tr1;
    cout << setw(10) << up_tr2 << endl;

    cout << "test MakeInv()" << endl;
    cout << "up_tr1.MakeInv() = " << endl;
    cout << setw(10) << *up_tr1.MakeInv() << endl;
    cout << "up_tr1.MakeInv() * up_tr1" << endl;
    cout << setw(10) << (*up_tr1.MakeInv())*up_tr1 << endl;

    cout << "test up_tr1.MakeInv() * up_tr2 - up_tr1" << endl;
    cout << setw(10) << *up_tr1.MakeInv() * up_tr2 - up_tr1 << endl;

    cout << "Swap(up_tr1,up_tr2)" << endl;
    Swap(up_tr1, up_tr2);
    cout << "up_tr1" << endl;
    cout << setw(10) << up_tr1 << endl;
    cout << "up_tr2" << endl;
    cout << setw(10) << up_tr2 << endl;

    cout << "t(up_tr2)" << endl;
    cout << setw(10) << t(up_tr2) << endl;

    Type d(1);
    for (int i = 1; i <= up_tr1.Nrows(); ++i)
    {
        d *= up_tr2(i, i);
    }
    cout << "test Determinant" << endl;
    cout << d << " = " << up_tr2.LogDeterminant().Value() << endl;

    cout << "TEST IS OVER" << endl;
}


