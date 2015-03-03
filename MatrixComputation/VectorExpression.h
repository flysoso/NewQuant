#ifndef VECTOR_EXPRESSION_H
#define VECTOR_EXPRESSION_H

#include "../ExceptionClass/NotDefinedException.h"

template <typename TYPE> class GeneralMatrix;

template <typename TYPE>
class VectorExpression
{
protected:
    int length;

    VectorExpression(){}

    VectorExpression(const int &l) : length(l) {}

    VectorExpression(const VectorExpression<TYPE> &v) : length(v.length){}

    void SetLength(const int &l)
    {
        length = l;
    }
public:
    virtual int Search(const GeneralMatrix<TYPE> &) const = 0;

    ~VectorExpression() {}

    int Length() const
    {
        return length;
    }

    virtual TYPE operator () (const int &i) const = 0;

    virtual TYPE & operator () (const int &i)
    {
        Singleton<Tracer>::Instance()->AddMessage("TYPE & VectorExpression::operator () (r, c)");
        throw NotDefinedException("TYPE & operator () (i)", "VectorExpression");
    }
};


#endif // VECTOR_EXPRESSION_H
