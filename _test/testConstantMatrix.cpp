#include "testConstantMatrix.h"

void testConstantMatrix()
{
    using namespace std;
    using namespace NewQuant;
    Type one(1), one_half(1.5), two(2);
    ConstantMatrix<Type> c1(5, 3, one), c2(1, 3, one), c3(3, 5, two), c4, c5(1, one_half);

    cout << "c1" << endl;
    cout << setw(10) << c1 << endl;

    cout << "c2" << endl;
    cout << setw(10) << c2 << endl;

    cout << "c3" << endl;
    cout << setw(10) << c3 << endl;

    cout << "c4=c1*c3" << endl;
    c4 = c1*c3;
    cout << setw(10) << c4 << endl;

    cout << "c4=t(c1)" << endl;
    c4 = t(c1);
    cout << setw(10) << c4 << endl;

    c4.Resize(1, 3);
    c5.Solve(c2, c4);
    cout << setw(10) << c4 << endl;

    cout << "TEST IS OVER" << endl;
}
