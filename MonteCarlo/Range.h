#ifndef Range_H
#define Range_H

#include <vector>
#include "include.h"

namespace NewQuant
{
    template <typename TYPE>
    class Range
    {
    private:
        TYPE start;
        TYPE end;
        TYPE delta;
        int steps;
    public:

        // Constructors

        Range();
        Range(const TYPE &, const TYPE &, const int &);
        Range(const Range<TYPE> &);
        ~Range(){}

        // Modifier functions

        void SetStart(const TYPE& s)
        {
            start = s;
        }
        void SetEnd(const TYPE& e)
        {
            end = e;
        }
        void SetSteps(const int &n)
        {
            steps = n;
        }

        //Accessing functions

        TYPE GetStart() const
        {
            return start;
        }
        TYPE GetEnd() const
        {
            return end;
        }
        int GetSteps() const
        {
            return steps;
        };
        TYPE GetDelta() const
        {
            return delta;
        }
        TYPE GetSpread() const
        {
            return end - start;
        }

        bool AtLeft(const TYPE& value) const;
        bool AtRight(const TYPE& value) const;
        bool Contains(const TYPE& value) const;

        Range<TYPE>& operator = (const Range<TYPE> &);
        TYPE operator () (const int &) const;
    };

    // Constructors
    template <typename TYPE>
    Range<TYPE>::Range()
    { // Default constructor.	
        static const TYPE zero(0), one(1);
        start = zero;
        end = one;
        steps = 100;
        delta = (end - start) / static_cast<TYPE>(steps);
    }

    template <typename TYPE>
    Range<TYPE>::Range(const TYPE& s, const TYPE& e, const int &n)
    {
        assert(s < e);
        start = s;
        end = e;
        steps = n;
        delta = (end - start) / static_cast<TYPE>(steps);
    }

    template <typename TYPE>
    Range<TYPE>::Range(const Range<TYPE>& range)
    {
        start = range.start;
        end = range.end;
        steps = range.steps;
        delta = range.delta;
    }

    template <typename TYPE>
    bool Range<TYPE>::AtLeft(const TYPE& val) const
    { // Check if current value is to the left of the range
        if (val < start)
            return true;
        return false;
    }

    template <typename TYPE>
    bool Range<TYPE>::AtRight(const TYPE& val) const
    { // Check if current value is to the right of the range
        if (val > end)
            return true;
        return false;
    }

    template <typename TYPE>
    bool Range<TYPE>::Contains(const TYPE& t) const
    {// Does range contain t
        if ((start <= t) && (end >= t))
            return true;
        return false;
    }

    // Operator overloading
    template <typename TYPE>
    Range<TYPE>& Range<TYPE>::operator = (const Range<TYPE>& r2)
    { // Assignment operator
        end = r2.end;
        start = r2.start;
        steps = r2.steps;
        return *this;
    }

    template <typename TYPE>
    TYPE Range<TYPE>::operator () (const int &i) const
    {
        assert(i - 1 <= steps);
        return delta*static_cast<TYPE>(i - 1);
    }
}

#endif //RANGE_H
