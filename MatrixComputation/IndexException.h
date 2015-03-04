#ifndef INDEX_EXCEPTION_H
#define INDEX_EXCEPTION_H

#include "../ExceptionClass/LogicError.h"

namespace NewQuant
{
    template <typename TYPE> class BaseMatrix;

    /// Index exception.
    class IndexException : public LogicError
    {
    public:
        template <typename TYPE>
        IndexException(int i, const BaseMatrix<TYPE>& A) : LogicError()
        {
            AddMessage("Index Excetopn, Requested Index = ");
            AddInt(i);
            MatrixDetails(A, error);
            Singleton<Tracer>::Instance()->AddTrace(error);
        }

        template <typename TYPE>
        IndexException(int i, int j, const BaseMatrix<TYPE>& A) : LogicError()
        {
            AddMessage("Index Excetopn, Requested Indices = ");
            AddInt(i);
            AddMessage(", ");
            AddInt(j);
            MatrixDetails(A, error);
            Singleton<Tracer>::Instance()->AddTrace(error);
        }


    };

}
#endif //INDEX_EXCEPTION_H
