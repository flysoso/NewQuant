#ifndef INERTNAL_EXCEPTION_H
#define INERTNAL_EXCEPTION_H

#include "LogicError.h"

namespace NewQuant
{
    class InternalException : public LogicError
    {
    public:

        InternalException(const char* a_what) : LogicError()
        {
            AddMessage("Internal Exception, please inform author : -- ");
            AddMessage(a_what);
            if (a_what)
            {
                Singleton<Tracer>::Instance()->AddTrace(error);
            }
        }

    };
}


#endif //INERTNAL_EXCEPTION_H


