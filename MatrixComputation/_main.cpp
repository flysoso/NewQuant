#include <time.h>
#include <iostream>
#include <iomanip>
#include <typeinfo>
#include <set>
#include <vector>
#include <random>
#include <algorithm>
#include <random>
#include <assert.h>

#include "Matrix.h"
#include "ColumnVector.h"
#include "ConstantMatrix.h"



int main()
{
    using namespace std;
    using namespace NewQuant;
    std::default_random_engine dre;
    std::normal_distribution<double> nd;

    int r = 200, c = 100;
    Matrix<double> A(r, c);
    ColumnVector<double> b(r), x(c), y(c), z(c), w(c);
    ConstantMatrix<double> con(r - c, c, 0.0);
    for (int i = 1; i <= A.Nrows(); ++i)
    {
        for (int j = 1; j <= A.Ncols(); ++j)
        {
            A(i, j) = nd(dre);
        }
    }

    for (int i = 1; i <= b.Length(); ++i)
    {
        b(i) = nd(dre);
    }



    return EXIT_SUCCESS;
}


/*
int main()
{
using namespace std;

int r = 10, c = r;

IdentityMatrix<double> im(r);
im(1, 1) = 2.5;

DiagonalMatrix<double> dm(r);
dm(1, 1) = 1.0, dm(2, 2) = 2.0, dm(3, 3) = 3.0, dm(4, 4) = 4.0;

LowerTriangularMatrix<double> ltm(r);
for (int i = 1; i <= r; ++i)
{
for (int j = 1; j <= i; ++j)
ltm(i, j) = 1.0;
}

UpperTriangularMatrix<double> utm(r);
for (int i = 1; i <= r; ++i)
{
for (int j = i; j <= r; ++j)
utm(i, j) = 1.0;
}

BandMatrix<double> bm(r, 1, 2);
for (int i = 1; i <= r; ++i)
{
for (int j = 1; j <= r; ++j)
{
if (i == j)
bm(i, j) = 3.0;
else
bm(i, j) = 1.0;
}
}

LowerBandMatrix<double> lbm(r, 1);
for (int i = 1; i <= r; ++i)
{
for (int j = 1; j <= r; ++j)
{
if (i == j)
lbm(i, j) = 3.0;
else
lbm(i, j) = 1.0;
}
}

UpperBandMatrix<double> ubm(r, 2);
for (int i = 1; i <= r; ++i)
{
for (int j = 1; j <= r; ++j)
{
if (i == j)
ubm(i, j) = 3.0;
else
ubm(i, j) = 1.0;
}
}

SymmetricMatrix<double> sm(r);
for (int i = 1; i <= r; ++i)
{
for (int j = 1; j <= r; ++j)
{
if (i == j)
sm(i, j) = 5.0;
else
sm(i, j) = 1.0;
}
}

SymmetricBandMatrix<double> sbm(r, 1);
for (int i = 1; i <= r; ++i)
{
for (int j = 1; j <= r; ++j)
{
if (i == j)
sbm(i, j) = 3.0;
else
sbm(i, j) = 1.0;
}
}

Matrix<double> m(r, c);
for (int i = 1; i <= r; ++i)
{
for (int j = 1; j <= c; ++j)
{
if (i == j)
m(i, j) = 3.0;
else
m(i, j) = 1.0;
}
}

SquareMatrix<double> sqm(r);
for (int i = 1; i <= r; ++i)
{
for (int j = 1; j <= r; ++j)
{
if (i == j)
sqm(i, j) = 3.0;
else
sqm(i, j) = 1.0;
}
}

RowVector<double> rv(c);
for (int j = 1; j <= c; ++j)
{
rv(j) = 1.0;
}

ColumnVector<double> cv(r);
for (int j = 1; j <= r; ++j)
{
cv(j) = 1.0;
}


try
{
MatrixIndex<double> mi;
MatrixIndexIterator<double> mit1, mit2;
cout << (mit1 == mit2) << endl;
}
catch (BaseException &e)
{
cout << e.what() << endl;
}
return 0;
}

*/