#ifndef SUBMATRIX_DIMENSION_EXCEPTION_H
#define SUBMATRIX_DIMENSION_EXCEPTION_H

#include "../ExceptionClass/LogicError.h"

class SubMatrixDimensionException : public LogicError
{
public:
    SubMatrixDimensionException() : LogicError()
    {
        AddMessage("SubMatrix Dimension Exception, Incompatible Submatrix Dimension : -- ");
        Singleton<Tracer>::Instance()->AddTrace(error);
    }
};


#endif //SUBMATRIX_DIMENSION_EXCEPTION_H

