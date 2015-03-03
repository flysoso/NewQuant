#ifndef OverflowException_H
#define OverflowException_H

#include "RuntimeError.h"
/// TYPE overflow exception.

class OverflowException : public RuntimeError
{
public:

    OverflowException(const char* c) : RuntimeError()
    {
        AddMessage("Overflow exception : -- ");
        AddMessage(c);
        if (c)
            Singleton<Tracer>::Instance()->AddTrace(error);
    }
};



#endif


