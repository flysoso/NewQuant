#ifndef INCOMPATIBLE_BANDWIDTH_EXCEPTION_H
#define INCOMPATIBLE_BANDWIDTH_EXCEPTION_H

#include "../ExceptionClass/LogicError.h"

namespace NewQuant
{
    template <typename TYPE> class BaseMatrix;

    /// Incompatible band width exception.
    class IncompatibleBandWidthException : public LogicError
    {
    public:
        IncompatibleBandWidthException() : LogicError()
        {
            AddMessage("Incompatible Band Width : -- ");
            Singleton<Tracer>::Instance()->AddTrace(error);
        }

        template <typename TYPE>
        IncompatibleBandWidthException(const BaseMatrix<TYPE>& A) : LogicError()
        {
            AddMessage("Incompatible Band Width : -- ");
            MatrixDetails(A, error);
            Singleton<Tracer>::Instance()->AddTrace(error);
        }

        template <typename TYPE>
        IncompatibleBandWidthException(const BaseMatrix<TYPE>& A, const BaseMatrix<TYPE>& B) : LogicError()
        {
            AddMessage("Incompatible Band Width : -- ");
            MatrixDetails(A, error);
            MatrixDetails(B, error);
            Singleton<Tracer>::Instance()->AddTrace(error);
        }

    };
}

#endif //INCOMPATIBLE_BANDWIDTH_EXCEPTION_H


