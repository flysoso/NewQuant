#ifndef RANGE_ERROR_H
#define RANGE_ERROR_H

#include "RuntimeError.h"

namespace NewQuant
{
    class RangeError : public RuntimeError
    {
    public:

        RangeError(const char *a_what) : RuntimeError()
        {
            AddMessage("Range error : --");
            AddMessage(a_what);
            if (a_what)
            {
                Singleton<Tracer>::Instance()->AddTrace(error);
            }
        }
    };
}

#endif //RANGE_ERROR_H

