#include "testUpperBandMatrix.h"

void testUpperBandMatrix()
{
    using namespace std;
    using namespace NewQuant;
    default_random_engine dre;
    normal_distribution<Type> nd;
    UpperBandMatrix<Type> up_band1(10, 6), up_band2(10, 3);

    for (int i = 1; i <= up_band1.Nrows(); ++i)
    {
        for (int j = 1; j <= up_band1.Ncols(); ++j)
        {
            up_band1(i, j) = nd(dre);
        }
    }

    cout << "up_band1(10,6)" << endl;
    cout << setw(10) << up_band1 << endl;

    cout << "test up_band2(10,3) << up_band1" << endl;
    up_band2 << up_band1;
    cout << setw(10) << up_band2 << endl;

    cout << "test up_band2 = up_band1" << endl;
    up_band2 = up_band1;
    cout << setw(10) << up_band2 << endl;

    cout << "test up_band2 = up_band1+up_band1" << endl;
    up_band2 = up_band1 + up_band1;
    cout << setw(10) << up_band2 << endl;

    cout << "test up_band2 = 2.0*up_band1" << endl;
    Type two(2);
    up_band2 = two*up_band1;
    cout << setw(10) << up_band2 << endl;

    cout << "test up_band2 = up_band1*up_band1" << endl;
    up_band2 = up_band1*up_band1;
    cout << setw(10) << up_band2 << endl;

    cout << "test MakeInv()" << endl;
    cout << "up_band1.MakeInv() = " << endl;
    cout << setw(10) << *up_band1.MakeInv() << endl;
    cout << "up_band1.MakeInv() * up_band1" << endl;
    cout << setw(10) << (*up_band1.MakeInv())*up_band1 << endl;

    cout << "test up_band1.MakeInv() * up_band2 - up_band1" << endl;
    cout << setw(10) << *up_band1.MakeInv() * up_band2 - up_band1 << endl;

    cout << "Swap(up_band1,up_band2)" << endl;
    Swap(up_band1, up_band2);
    cout << "up_band1" << endl;
    cout << setw(10) << up_band1 << endl;
    cout << "up_band2" << endl;
    cout << setw(10) << up_band2 << endl;

    cout << "t(up_band2)" << endl;
    cout << setw(10) << t(up_band2) << endl;


    Type d(1);
    for (int i = 1; i <= up_band1.Nrows(); ++i)
    {
        d *= up_band2(i, i);
    }
    cout << "test Determinant" << endl;
    cout << d << " = " << up_band2.LogDeterminant().Value() << endl;

    cout << "TEST IS OVER" << endl;
}


