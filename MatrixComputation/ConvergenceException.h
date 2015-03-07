#ifndef CONVERGENCE_EXCEPTION_H
#define CONVERGENCE_EXCEPTION_H

#include "../ExceptionClass/RuntimeError.h"
#include "MatrixDetails.h"

namespace NewQuant
{
    template<typename TYPE> class BaseMatrix;

    /// Covergence failure exception.
    class ConvergenceException : public RuntimeError
    {
    public:
        template<typename TYPE>
        ConvergenceException(const BaseMatrix<TYPE>& A) : RuntimeError()
        {
            AddMessage("Detected By NewQuant: Process Fails To Converge\n\n");
            MatrixDetails(A, error);
            Singleton<Tracer>::Instance()->AddTrace(error);
        }

        ConvergenceException(const char* c) : RuntimeError()
        {
            AddMessage("Convergence Exception : -- ");
            AddMessage(c);
            if (c)
            {
                Singleton<Tracer>::Instance()->AddTrace(error);
            }
        }
    };


}

#endif //CONVERGENCE_EXCEPTION_H


