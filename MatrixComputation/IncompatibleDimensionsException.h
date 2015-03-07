#ifndef INCOMPATIBLE_DIMENSIONS_EXCEPTION_H
#define INCOMPATIBLE_DIMENSIONS_EXCEPTION_H

#include "../ExceptionClass/LogicError.h"
#include "MatrixDetails.h"

namespace NewQuant
{
    template<typename TYPE> class BaseMatrix;

    /// Incompatible dimensions exception.
    class IncompatibleDimensionsException : public LogicError
    {
    public:
        IncompatibleDimensionsException() : LogicError()
        {
            AddMessage("Incompatible Dimensions : -- ");
            Singleton<Tracer>::Instance()->AddTrace(error);
        }

        template<typename TYPE>
        IncompatibleDimensionsException(const BaseMatrix<TYPE>& A) : LogicError()
        {
            AddMessage("Incompatible Dimensions : -- ");
            MatrixDetails(A, error);
            Singleton<Tracer>::Instance()->AddTrace(error);
        }

        template<typename TYPE>
        IncompatibleDimensionsException(const BaseMatrix<TYPE>& A, const BaseMatrix<TYPE>& B) : LogicError()
        {
            AddMessage("Incompatible Dimensions : -- ");
            MatrixDetails(A, error);
            MatrixDetails(B, error);
            Singleton<Tracer>::Instance()->AddTrace(error);
        }
    };
}
#endif //INCOMPATIBLE_DIMENSIONS_EXCEPTION_H


