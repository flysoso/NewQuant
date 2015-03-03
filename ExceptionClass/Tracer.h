#ifndef TRACER_H
#define TRACER_H

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <memory>

class BaseException;

class Tracer                             // linked list showing how
{
private:
    std::string entry;
    std::vector<std::string> entry_list;

public:
    Tracer() : entry("Global NewQuant Tracer : \n")
    {
        entry_list.push_back(entry);
    }

    Tracer(const char* e) : entry(e)
    {
        entry_list.push_back(entry);
    }

    ~Tracer(){}

    void PrintTrace()             // for printing trace
    {
        std::cout << "\n";
        std::vector<std::string>::const_iterator p;
        for (p = entry_list.begin(); p != entry_list.end(); ++p)
        {
            std::cout << "  * " << *p << "\n";
        }
    }

    void AddTrace(const std::string & trace)
    {
        time_t t = time(0);
        char t_str[30];
        strftime(t_str, 30, "%Y/%m/%d %X\t", localtime(&t));
        std::string ts;
        ts.assign(t_str);
        entry_list.push_back(ts + trace);
    }

    void AddMessage(const char *a_what)
    {
        std::string temp;
        temp.assign(a_what);
        entry_list.push_back(temp);
    }
};

template<typename TYPE>
class Singleton
{
private:
    static std::shared_ptr<TYPE> instance;
    Singleton();
public:
    static std::shared_ptr<TYPE> & Instance()
    {
        if (instance.get() == NULL)
        {
            instance.reset(new TYPE);
        }
        return instance;
    }
    ~Singleton(){}
};

template<typename TYPE>
std::shared_ptr<TYPE> Singleton<TYPE> ::instance;

#endif //TRACER_H



