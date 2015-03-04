#ifndef PROGRAM_EXCETION_H
#define PROGRAM_EXCETION_H

#include "../ExceptionClass/LogicError.h"
#include "MatrixType.h"

namespace NewQuant
{
    template <typename TYPE> class BaseMatrix;

    /// Miscellaneous exception (details in character string).
    class ProgramException : public LogicError
    {
    protected:
        ProgramException();
    public:
        ProgramException(const char* c) : LogicError()
        {
            AddMessage("Program Exception : -- ");
            AddMessage(c);
            if (c)
            {
                Singleton<Tracer>::Instance()->AddTrace(error);
            }
        }

        template <typename TYPE>
        ProgramException(const char* c, const BaseMatrix<TYPE>& A) : LogicError()
        {
            AddMessage("Program Exception : -- ");
            AddMessage(c);
            MatrixDetails(A, error);
            if (c)
            {
                Singleton<Tracer>::Instance()->AddTrace(error);
            }
        }

        template <typename TYPE>
        ProgramException(const char* c, const BaseMatrix<TYPE>& A, const BaseMatrix<TYPE>& B) : LogicError()
        {
            AddMessage("Program Exception : -- ");
            AddMessage(c);
            MatrixDetails(A, error);
            MatrixDetails(B, error);
            if (c)
            {
                Singleton<Tracer>::Instance()->AddTrace(error);
            }
        }

        ProgramException(const char* c, const MatrixType &a, const MatrixType &b) : LogicError()
        {
            AddMessage("Program Exception : -- ");
            AddMessage(c);
            AddMessage("\nMatrixTypes = ");
            AddMessage(a.Value());
            AddMessage("; ");
            AddMessage(b.Value());
            if (c)
            {
                Singleton<Tracer>::Instance()->AddTrace(error);
            }
        }
    };

}
#endif //PROGRAM_EXCETION_H

