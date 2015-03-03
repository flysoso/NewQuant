#include "testLowerBandMatrix.h"

void testLowerBandMatrix()
{
    using namespace std;
    default_random_engine dre;
    normal_distribution<Type> nd;
    LowerBandMatrix<Type> low_band1(10, 6), low_band2(10, 3);

    for (int i = 1; i <= low_band1.Nrows(); ++i)
    {
        for (int j = 1; j <= low_band1.Ncols(); ++j)
        {
            low_band1(i, j) = nd(dre);
        }
    }

    cout << "low_band1(10,6)" << endl;
    cout << setw(10) << low_band1 << endl;

    cout << "test low_band2(10,3) << low_band1" << endl;
    low_band2 << low_band1;
    cout << setw(10) << low_band2 << endl;

    cout << "test low_band2 = low_band1" << endl;
    low_band2 = low_band1;
    cout << setw(10) << low_band2 << endl;

    cout << "test low_band2 = low_band1+low_band1" << endl;
    low_band2 = low_band1 + low_band1;
    cout << setw(10) << low_band2 << endl;

    cout << "test low_band2 = 2.0*low_band1" << endl;
    Type two(2);
    low_band2 = two*low_band1;
    cout << setw(10) << low_band2 << endl;

    cout << "test low_band2 = low_band1*low_band1" << endl;
    low_band2 = low_band1*low_band1;
    cout << setw(10) << low_band2 << endl;

    cout << "test MakeInv()" << endl;
    cout << "low_band1.MakeInv() = " << endl;
    cout << setw(10) << *low_band1.MakeInv() << endl;
    cout << "low_band1.MakeInv() * low_band1" << endl;
    cout << setw(10) << (*low_band1.MakeInv())*low_band1 << endl;

    cout << "test low_band1.MakeInv() * low_band2 - low_band1" << endl;
    cout << setw(10) << *low_band1.MakeInv() * low_band2 - low_band1 << endl;

    cout << "Swap(low_band1,low_band2)" << endl;
    Swap(low_band1, low_band2);
    cout << "low_band1" << endl;
    cout << setw(10) << low_band1 << endl;
    cout << "low_band2" << endl;
    cout << setw(10) << low_band2 << endl;

    cout << "t(low_band2)" << endl;
    cout << setw(10) << t(low_band2) << endl;

    Type d(1);
    for (int i = 1; i <= low_band2.Nrows(); ++i)
    {
        d *= low_band2(i, i);
    }
    cout << "test Determinant" << endl;
    cout << d << " = " << low_band2.LogDeterminant().Value() << endl;

    cout << "TEST IS OVER" << endl;
}


