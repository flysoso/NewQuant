#include "testBandMatrix.h"

void testBandMatrix()
{
    using namespace std;
    default_random_engine dre;
    normal_distribution<Type> nd;
    BandMatrix<Type> band1(10, 3, 2), band2(10, 1, 3);

    for (int i = 1; i <= band1.Nrows(); ++i)
    {
        for (int j = 1; j <= band1.Ncols(); ++j)
        {
            band1(i, j) = nd(dre);
        }
    }
    cout << "band1(10,3,2)" << endl;
    cout << setw(10) << band1 << endl;

    cout << "test band2(10,1,3) << band1" << endl;
    band2 << band1;
    cout << setw(10) << band2 << endl;

    cout << "test band2(10,1,3) = band2+band1" << endl;
    band2 = band2 + band1;
    cout << setw(10) << band2 << endl;

    cout << "test band2(10,1,3) << band1+band1" << endl;
    band2 << band1 + band1;
    cout << setw(10) << band2 << endl;

    cout << "test band2 = band1" << endl;
    band2 = band1;
    cout << setw(10) << band2 << endl;

    cout << "test band2 = band1+band1" << endl;
    band2 = band1 + band1;
    cout << setw(10) << band2 << endl;

    cout << "test band2 = 2.0*band1" << endl;
    Type two(2);
    band2 = two*band1;
    cout << setw(10) << band2 << endl;

    cout << "test band2 *= 2" << endl;
    band2 *= two;
    cout << setw(10) << band2 << endl;

    cout << "test band2 = band1*band1" << endl;
    band2 = band1*band1;
    cout << setw(10) << band2 << endl;

    cout << "test MakeInv()" << endl;
    cout << "band1.MakeInv() = " << endl;
    cout << setw(10) << *band1.MakeInv() << endl;
    cout << "band1.MakeInv() * band1" << endl;
    cout << setw(10) << (*band1.MakeInv())*band1 << endl;

    cout << "test band1.MakeInv() * band2 - band1" << endl;
    cout << setw(10) << *band1.MakeInv() * band2 - band1 << endl;

    cout << "Swap(band1,band2)" << endl;
    Swap(band1, band2);
    cout << "band1" << endl;
    cout << setw(10) << band1 << endl;
    cout << "band2" << endl;
    cout << setw(10) << band2 << endl;

    cout << "TEST IS OVER" << endl;
}


