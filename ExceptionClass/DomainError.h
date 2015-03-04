#ifndef DOMAIN_ERROE_H
#define DOMAIN_ERROE_H

#include "LogicError.h"

namespace NewQuant
{
    class DomainError : public LogicError
    {
    public:

        DomainError(const char *a_what) : LogicError()
        {
            AddMessage("Domain error : -- ");
            AddMessage(a_what);
            if (a_what)
            {
                Singleton<Tracer>::Instance()->AddTrace(error);
            }
        }
    };
}
#endif //DOMAIN_ERROE_H
