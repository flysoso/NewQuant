#include "testVector.h"

void testVector()
{
    using namespace std;
    default_random_engine dre;
    normal_distribution<Type> nd;
    RowVector<Type> rvec1(10), rvec2(10);
    ColumnVector<Type> cvec1(10), cvec2(10);

    for (int i = 1; i <= rvec1.Nrows(); ++i)
    {
        for (int j = 1; j <= rvec1.Ncols(); ++j)
        {
            rvec1(i, j) = nd(dre);
            cvec1(j, i) = nd(dre);
        }
    }

    cout << "rvec1(10,10)" << endl;
    cout << setw(10) << rvec1 << endl;

    cout << "test rvec2(10,10) << rvec1" << endl;
    rvec2 << rvec1;
    cout << setw(10) << rvec2 << endl;

    cout << "test rvec2 = rvec2+rvec1" << endl;
    rvec2 = rvec2 + rvec1;
    cout << setw(10) << rvec2 << endl;

    cout << "test rvec2 << rvec1+rvec1" << endl;
    rvec2 << rvec1 + rvec1;
    cout << setw(10) << rvec2 << endl;

    cout << "test rvec2 = rvec1" << endl;
    rvec2 = rvec1;
    cout << setw(10) << rvec2 << endl;

    cout << "test rvec2 = rvec1+rvec1" << endl;
    rvec2 = rvec1 + rvec1;
    cout << setw(10) << rvec2 << endl;

    cout << "test rvec2 = 2.0*rvec1" << endl;
    Type two(2);
    rvec2 = two*rvec1;
    cout << setw(10) << rvec2 << endl;

    cout << "test rvec2 *= 2" << endl;
    rvec2 *= two;
    cout << setw(10) << rvec2 << endl;

    cout << "test rvec2 = sp(rvec1, rvec1)" << endl;
    rvec2 = sp(rvec1, rvec1);
    cout << setw(10) << rvec2 << endl;


    cout << "cvec1(10,10)" << endl;
    cout << setw(10) << cvec1 << endl;

    cout << "test cvec2(10,10) << cvec1" << endl;
    cvec2 << cvec1;
    cout << setw(10) << cvec2 << endl;

    cout << "test cvec2 = cvec2+cvec1" << endl;
    cvec2 = cvec2 + cvec1;
    cout << setw(10) << cvec2 << endl;

    cout << "test cvec2 << cvec1+cvec1" << endl;
    cvec2 << cvec1 + cvec1;
    cout << setw(10) << cvec2 << endl;

    cout << "test cvec2 = cvec1" << endl;
    cvec2 = cvec1;
    cout << setw(10) << cvec2 << endl;

    cout << "test cvec2 = cvec1+cvec1" << endl;
    cvec2 = cvec1 + cvec1;
    cout << setw(10) << cvec2 << endl;

    cout << "test cvec2 = 2.0*cvec1" << endl;
    cvec2 = two*cvec1;
    cout << setw(10) << cvec2 << endl;

    cout << "test cvec2 *= 2" << endl;
    cvec2 *= two;
    cout << setw(10) << cvec2 << endl;

    cout << "test cvec2 = sp(cvec1, cvec1)" << endl;
    cvec2 = sp(cvec1, cvec1);
    cout << setw(10) << cvec2 << endl;

    cout << "test cvec1 * rvec1" << endl;
    cout << setw(10) << cvec1 * rvec1 << endl;

    cout << "test rvec1 * cvec1" << endl;
    cout << setw(10) << rvec1 * cvec1 << endl;

    cout << "test MakeInv()" << endl;
    cout << "(rvec1*cvec1).MakeInv() = " << endl;
    cout << setw(10) << *(rvec1 * cvec1).MakeInv() << endl;

    cout << "test rvec1 = t(cvec1)" << endl;
    rvec1 = t(cvec1);
    cout << setw(10) << rvec1 << endl;
    cout << setw(10) << cvec1 << endl;

    cout << "TEST IS OVER" << endl;
}


