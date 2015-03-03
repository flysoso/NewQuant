#ifndef NOT_DEFINED_EXCEPTION_H
#define NOT_DEFINED_EXCEPTION_H

#include "LogicError.h"

/// Not defined exception.
class NotDefinedException : public LogicError
{
public:

    NotDefinedException(const char* op, const char* x) : LogicError()
    {
        AddMessage("Not defined exception : -- ");
        AddMessage(op);
        AddMessage("is not defined for ");
        AddMessage(x);
        Singleton<Tracer>::Instance()->AddTrace(error);
    }
};



#endif //NOT_DEFINED_EXCEPTION_H

