#ifndef INVALID_ARGUMENT_H
#define INVALID_ARGUMENT_H

#include "LogicError.h"

class InvalidArgument : public LogicError
{
public:
    InvalidArgument(const char *a_what = NULL) : LogicError()
    {
        AddMessage("Invalid argument : -- ");
        AddMessage(a_what);
        if (a_what)
        {
            Singleton<Tracer>::Instance()->AddTrace(error);
        }
    }
};



#endif //INVALID_ARGUMENT_H
