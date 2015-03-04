#ifndef SINGULAR_EXCEPTION_H
#define SINGULAR_EXCEPTION_H

#include "../ExceptionClass/RuntimeError.h"
#include "MatrixDetails.h"

namespace NewQuant
{
    template <typename TYPE> class BaseMatrix;

    /// Singular matrix exception.
    class SingularException : public RuntimeError
    {
    public:
        template <typename TYPE>
        SingularException(const BaseMatrix<TYPE> &A) : RuntimeError()
        {
            AddMessage("Singular Exception, Matrix Is Singular : -- ");
            MatrixDetails(A, error);
            Singleton<Tracer>::Instance()->AddTrace(error);
        }
    };

}


#endif //SINGULAR_EXCEPTION_H

