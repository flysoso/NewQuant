#ifndef LOGIC_ERROR_H
#define LOGIC_ERROR_H

#include "BaseException.h"

namespace NewQuant
{
    class LogicError : public BaseException
    {
    protected:
        LogicError() : BaseException()
        {
            AddMessage("Logic Error : -- ");
        }

    public:
        LogicError(const char *a_what) : BaseException()
        {
            AddMessage("Logic Error : -- ");
            AddMessage(a_what);
            if (a_what)
            {
                Singleton<Tracer>::Instance()->AddTrace(error);
            }
        }
    };

}

#endif //LOGIC_ERROR_H

