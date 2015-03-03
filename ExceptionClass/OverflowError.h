#ifndef OVERFLOW_ERROR_H
#define OVERFLOW_ERROR_H

#include "RuntimeError.h"

class OverflowError : public RuntimeError
{
public:
    OverflowError(const char *a_what) : RuntimeError()
    {
        AddMessage("Overflow Error : -- ");
        AddMessage(a_what);
        if (a_what)
        {
            Singleton<Tracer>::Instance()->AddTrace(error);
        }
    }
};


#endif //OVERFLOW_ERROR_H
