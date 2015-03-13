#ifndef BrownianMotion_HPP
#define BrownianMotion_HPP

#include "../../Range.h"

namespace NewQuant
{
    template<typename TYPE>
    class BrownianMotion
    {
    private:
        Range<TYPE> range;
        TYPE delta_t;
        TYPE sqrt_delta_t;
        mutable TYPE temp;  //temp value for InfPath
        mutable bool first;     //first time to get InfPath ?
    public:
        BrownianMotion(const Range<TYPE> &r) : range(r), temp(0), first(true)
        {
            delta_t = range.GetDelta();
            sqrt_delta_t = std::sqrt(delta_t);
        }

        ~BrownianMotion(){}

        BrownianMotion<TYPE>& operator = (const BrownianMotion<TYPE> &bm)
        {
            range = bm.range;
            delta_t = bm.delta_t;
            sqrt_delta_t = bm.sqrt_delta_t;
            return *this;
        }

        void Mesh(unsigned int n)
        {
            range.Mesh(n);
        }

        //for std::vector and std::valarray
        template<typename CONTAIN, typename RAND>
        void GetPathForSTD(CONTAIN &contain, RAND &random) const
        {
            unsigned int start = 0;

            TYPE val(0);
            for (unsigned int i = start; i < range.GetSteps() + start + 1; ++i)
            {
                contain[i] = val;
                val += sqrt_delta_t * random();
            }

        }

        //VECTOR has operator(int) start by 1
        template<typename VECTOR, typename RAND>
        void GetPath(VECTOR &contain, RAND &random) const
        {
            unsigned int start = 1;

            TYPE val(0);
            for (unsigned int i = start; i < range.GetSteps() + start + 1; ++i)
            {
                contain(i) = val;
                val += sqrt_delta_t * random();
            }

        }

        //Get InfPath by delta_time = dt
        template<typename RAND>
        TYPE GetPathInf(RAND &random, const TYPE &dt) const
        {
            if (first)
            {
                first = false;
                return temp;
            }
            else
            {
                temp += random() * std::sqrt(dt);
                return temp;
            }
        }

        //change the state of object to restart at 0
        void ReStart() const
        {        
            temp=TYPE(0);
            first = true;
        }

        Range<TYPE> GetRange() const
        {
            return range;
        }

        TYPE Range(unsigned int i) const
        {
            return range(i);
        }

        unsigned int GetSteps()const
        {
            return range.GetSteps();
        }
    };

}


#endif


