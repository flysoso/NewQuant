#ifndef RUNTIME_ERROR_H
#define RUNTIME_ERROR_H

#include "BaseException.h"

namespace NewQuant
{
    class RuntimeError : public BaseException
    {
    protected:
        RuntimeError() : BaseException()
        {
            AddMessage("Runtime Error : -- ");
        }

    public:
        RuntimeError(const char *a_what) : BaseException()
        {
            AddMessage("Runtime Error : -- ");
            AddMessage(a_what);
            if (a_what)
            {
                Singleton<Tracer>::Instance()->AddTrace(error);
            }
        }
    };
}


#endif //RUNTIME_ERROR_H


