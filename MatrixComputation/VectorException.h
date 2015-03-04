#ifndef VECTOR_EXCEPTION_H
#define VECTOR_EXCEPTION_H

#include "../ExceptionClass/LogicError.h"

namespace NewQuant
{
    template <typename TYPE> class BaseMatrix;

    /// Cannot convert to vector exception.
    class VectorException : public LogicError
    {
    public:
        VectorException() : LogicError()
        {
            AddMessage("Vector Exception, Cannot Convert Matrix To Vector : -- ");
            Singleton<Tracer>::Instance()->AddTrace(error);
        }

        template <typename TYPE>
        VectorException(const BaseMatrix<TYPE>& A) : LogicError()
        {
            AddMessage("Vector Exception, Cannot Convert Matrix To Vector : -- ");
            MatrixDetails(A, error);
            Singleton<Tracer>::Instance()->AddTrace(error);
        }
    };
}

#endif //VECTOR_EXCEPTION_H


