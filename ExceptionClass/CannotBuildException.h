#ifndef CANNOT_BUILD_EXCEPTION_H
#define CANNOT_BUILD_EXCEPTION_H

#include "LogicError.h"

class CannotBuildException : public LogicError
{
public:
    CannotBuildException(const char *a_what) : LogicError()
    {
        AddMessage("Cannot Build Exception : -- ");
        AddMessage(a_what);
        if (a_what)
        {
            Singleton<Tracer>::Instance()->AddTrace(error);
        }
    }
};

#endif //CANNOT_BUILD_EXCEPTION_H

