#ifndef NPD_EXCEPTION_H
#define NPD_EXCEPTION_H

#include "../ExceptionClass/RuntimeError.h"

namespace NewQuant
{
    template<typename TYPE> class BaseMatrix;

    /// Not positive definite exception.
    class NPDException : public RuntimeError
    {
    public:
        template<typename TYPE>
        NPDException(const BaseMatrix<TYPE>& A) : RuntimeError()
        {
            AddMessage("NPD Exception, Matrix Is Not Positive Definite : -- ");
            MatrixDetails(A, error);
            Singleton<Tracer>::Instance()->AddTrace(error);
        }

    };

}
#endif //NPD_EXCEPTION_H


