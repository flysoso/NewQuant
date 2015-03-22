#ifndef PARAMETER_INFORMATION_H
#define PARAMETER_INFORMATION_H

#include <vector>
#include <iostream>

namespace NewQuant
{
    template<typename TYPE> class ElementParameterInformation;

    template<typename TYPE>
    class ParameterInformation
    {
    private:
        std::vector<ElementParameterInformation<TYPE> > para;

    public:
        ParameterInformation(const int &n) :para(n){}

        ~ParameterInformation(){}

        ElementParameterInformation<TYPE> & operator () (const int &i)
        {
            return para[i - 1];
        }

        ElementParameterInformation<TYPE> operator () (const int &i) const
        {
            return para[i - 1];
        }

        int Size() const
        {
            return para.size();
        }
    };

    template<typename TYPE>
    std::ostream & operator << (std::ostream &out, const ParameterInformation<TYPE> &p)
    {
        for (int i = 1; i <= p.Size(); ++i)
        {
            out << p(i) << std::endl;
        }
        return out;
    }

    template<typename TYPE>
    class ElementParameterInformation
    {
    private:
        TYPE value;
        TYPE t_ratio;
        TYPE p_value;
        TYPE lower, upper;
        TYPE sd;
        bool significant;

    public:
        ElementParameterInformation(){}

        ~ElementParameterInformation(){}

        void Value(const TYPE &x)
        {
            value = x;
        }

        void T_Ratio(const TYPE &x)
        {
            t_ratio = x;
        }

        void P_Value(const TYPE &x)
        {
            p_value = x;
        }

        void Sd(const TYPE &x)
        {
            sd = x;
        }

        void Lower(const TYPE &x)
        {
            lower = x;
        }

        void Upper(const TYPE &x)
        {
            upper = x;
        }

        void Significance(const bool &x)
        {
            significant = x;
        }

        const TYPE & Value() const
        {
            return value;
        }

        const TYPE & T_Ratio() const
        {
            return t_ratio;
        }

        TYPE F_Ratio() const
        {
            return t_ratio*t_ratio;
        }

        const TYPE & P_Value() const
        {
            return p_value;
        }

        const TYPE & Sd() const
        {
            return sd;
        }

        const TYPE & Lower() const
        {
            return lower;
        }

        const TYPE & Upper() const
        {
            return upper;
        }

        const bool & Significance() const
        {
            return significant;
        }
    };

    template<typename TYPE>
    std::ostream & operator << (std::ostream &out, const ElementParameterInformation<TYPE> &p)
    {
        out << "value : " << p.Value() << '\t';
        out << "t_ratio : " << p.T_Ratio() << '\t';
        out << "sd : " << p.Sd() << '\t';
        out << "p_value : " << p.P_Value() << '\t';
        out << "lower : " << p.Lower() << '\t';
        out << "upper : " << p.Upper() << '\t';
        if (p.Significance())
        {
            out << "is significant : YES";
        }
        else
        {
            out << "is significant : NO";
        }

        return out;
    }
}


#endif //PARAMETER_INFORMATION_H

