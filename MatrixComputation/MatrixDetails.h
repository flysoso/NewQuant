#ifndef MatrixDetails_H
#define MatrixDetails_H
#include <string>
#include "MatrixBandWidth.h"

namespace NewQuant
{
    template <typename TYPE> class BaseMatrix;

    template <typename TYPE>
    void MatrixDetails(const BaseMatrix<TYPE>& A, std::string &err_str)
    {
        // write matrix details to Exception buffer
        using namespace std;
        const MatrixBandWidth<TYPE> &bw = A.BandWidth();
        int ubw = bw.Upper();
        int lbw = bw.Lower();
        stringstream ss;
        ss << "\nMatrixType = ";
        ss << A.Type().Value();
        ss << "  # Rows = ";
        ss << A.Nrows();
        ss << "; # Cols = ";
        ss << A.Ncols();
        if (bw.Evalued())
        {
            ss << "; LowerBandWidth = ";
            ss << lbw;

            ss << "; UpperBandWidth = ";
            ss << ubw;
        }
        err_str.append(ss.str());
    }
}
#endif

