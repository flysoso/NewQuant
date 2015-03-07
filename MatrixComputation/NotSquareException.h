#ifndef NOTSQUARE_EXCEPTION_H
#define NOTSQUARE_EXCEPTION_H

#include "../ExceptionClass/LogicError.h"
#include "MatrixDetails.h"

namespace NewQuant
{
    template<typename TYPE> class BaseMatrix;

    class NotSquareException : public LogicError
    {
    public:
        NotSquareException() : LogicError()
        {
            AddMessage("Not Square Exception, Matrix Is Not Square : -- ");
            Singleton<Tracer>::Instance()->AddTrace(error);
        }

        template<typename TYPE>
        NotSquareException(const BaseMatrix<TYPE>& A) : LogicError()
        {
            AddMessage("Not Square Exception, Matrix Is Not Square : -- ");
            MatrixDetails(A, error);
            Singleton<Tracer>::Instance()->AddTrace(error);
        }
    };
}
#endif //NOTSQUARE_EXCEPTION_H



