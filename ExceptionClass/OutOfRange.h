#ifndef OUT_OF_RANGE_H
#define OUT_OF_RANGE_H

#include "LogicError.h"

namespace NewQuant
{
    class OutOfRange : public LogicError
    {
    public:

        OutOfRange(const char *a_what) : LogicError()
        {
            AddMessage("Out of range : --");
            AddMessage(a_what);
            if (a_what)
            {
                Singleton<Tracer>::Instance()->AddTrace(error);
            }
        }
    };
}

#endif //OUT_OF_RANGE_H

