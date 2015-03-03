#ifndef BaseException_H
#define BaseException_H

#include <string>
#include <sstream>

#include "Tracer.h"

class BaseException                          // The base exception class
{
protected:
    std::string error;

    BaseException()
    {
        AddMessage("An exception has been thrown : --");
    }
public:
    explicit BaseException(const char *a_what)
    {
        AddMessage("An exception has been thrown : --");
        AddMessage(a_what);
        if (a_what)
        {
            Singleton<Tracer>::Instance()->AddTrace(error);
        }
    }

    ~BaseException(){}

    const char* what() const
    {
        return error.c_str();
    }

    const char* What() const
    {
        return error.c_str();
    }

    void AddMessage(const char *a_what)
    {
        if (a_what)
        {
            error.append(a_what);
        }
    }

    void AddInt(int n)
    {
        std::stringstream ss;
        ss << n;
        error += ss.str();
    }

    static void clear(){}
};


#endif


