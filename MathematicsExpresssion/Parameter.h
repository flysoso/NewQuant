#ifndef PARAMETER_H
#define PARAMETER_H

namespace NewQuant
{
    template<typename TYPE>
    class Parameter
    {
    public:
        Parameter(){}

        ~Parameter(){}

        virtual TYPE operator()(const int &)const = 0;
    };

    template<typename TYPE, typename ELEMENT>
    class ParameterWrapper :public Parameter < TYPE >
    {
    private:
        const ELEMENT &element;
    public:
        ParameterWrapper(const ELEMENT &e) :Parameter<TYPE>(), element(e){}

        TYPE operator()(const int &i)const
        {
            return element(i);
        }
    };

    template<typename TYPE, typename ELEMENT>
    ParameterWrapper<TYPE, ELEMENT> para(const ELEMENT &e)
    {
        return ParameterWrapper<TYPE, ELEMENT>(e);
    }
}

#endif //PARAMETER_H
