#include "testMatrix.h"

void testMatrix()
{
    using namespace std;
    default_random_engine dre;
    normal_distribution<Type> nd;
    Matrix<Type> mat1(10, 10), mat2(10, 10);

    for (int i = 1; i <= mat1.Nrows(); ++i)
    {
        for (int j = 1; j <= mat1.Ncols(); ++j)
        {
            mat1(i, j) = nd(dre);
        }
    }
    cout << "mat1(10,10)" << endl;
    cout << setw(10) << mat1 << endl;

    cout << "test mat2(10,10) << mat1" << endl;
    mat2 << mat1;
    cout << setw(10) << mat2 << endl;

    cout << "test mat2 = mat2+mat1" << endl;
    mat2 = mat2 + mat1;
    cout << setw(10) << mat2 << endl;

    cout << "test mat2 << mat1+mat1" << endl;
    mat2 << mat1 + mat1;
    cout << setw(10) << mat2 << endl;

    cout << "test mat2 = mat1" << endl;
    mat2 = mat1;
    cout << setw(10) << mat2 << endl;

    cout << "test mat2 = mat1+mat1" << endl;
    mat2 = mat1 + mat1;
    cout << setw(10) << mat2 << endl;

    cout << "test mat2 = 2.0*mat1" << endl;
    Type two(2);
    mat2 = two*mat1;
    cout << setw(10) << mat2 << endl;

    cout << "test mat2 *= 2" << endl;
    mat2 *= two;
    cout << setw(10) << mat2 << endl;

    cout << "test mat2 = mat1*mat1" << endl;
    mat2 = mat1*mat1;
    cout << setw(10) << mat2 << endl;

    cout << "test MakeInv()" << endl;
    cout << "mat1.MakeInv() = " << endl;
    cout << setw(10) << *mat1.MakeInv() << endl;
    cout << "mat1.MakeInv() * mat1" << endl;
    cout << setw(10) << (*mat1.MakeInv())*mat1 << endl;

    cout << "test mat1.MakeInv() * mat2 - mat1" << endl;
    cout << setw(10) << *mat1.MakeInv() * mat2 - mat1 << endl;

    cout << "Swap(mat1,mat2)" << endl;
    Swap(mat1, mat2);
    cout << "mat1" << endl;
    cout << setw(10) << mat1 << endl;
    cout << "mat2" << endl;
    cout << setw(10) << mat2 << endl;

    cout << "TEST IS OVER" << endl;
}


