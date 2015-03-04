#ifndef BAD_ALLOCATION_H
#define BAD_ALLOCATION_H

#include "BaseException.h"

namespace NewQuant
{
    class BadAllocation : public BaseException
    {
    protected:
        BadAllocation() : BaseException()
        {
            AddMessage("Bad Allocation : -- ");
        }
    public:
        BadAllocation(const char *a_what) : BaseException()
        {
            AddMessage("Bad Allocation : -- ");
            AddMessage(a_what);
            if (a_what)
            {
                Singleton<Tracer>::Instance()->AddTrace(error);
            }
        }
    };
}
#endif //BAD_ALLOCATION_H


