#ifndef LENGTH_ERROR_H
#define LENGTH_ERROR_H

#include "LogicError.h"


class LengthError : public LogicError
{
public:

    LengthError(const char *a_what) : LogicError()
    {
        AddMessage("Length error : -- ");
        AddMessage(a_what);
        if (a_what)
        {
            Singleton<Tracer>::Instance()->AddTrace(error);
        }
    }

};


#endif //LENGTH_ERROR_H

