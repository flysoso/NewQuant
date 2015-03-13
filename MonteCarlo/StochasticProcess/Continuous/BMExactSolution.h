#ifndef BMExactSolution_HPP
#define BMExactSolution_HPP

#include "../../Range.h"
#include "BrownianMotion.h"

namespace NewQuant
{
    template <typename TYPE, typename FUNCTION>
    class BMExactSolution
    {
    private:
        mutable FUNCTION func;//has operator(t, bm)

        BrownianMotion<TYPE> * bm;

        mutable TYPE time;  //temp value for InfPath
        mutable bool first;     //first time to get InfPath ?

    public:
        BMExactSolution(const Range<TYPE> r, const FUNCTION f) : func(f), first(true)
        {
            bm = new BrownianMotion<TYPE> (r);
            time = r(1);
        }
        ~BMExactSolution()
        {
            delete bm;
        }
        BMExactSolution<TYPE, FUNCTION>& operator = (const BMExactSolution<TYPE, FUNCTION> &sp)
        {
            range = sp.range;
            delta_t = sp.delta_t;
            sqrt_delta_t = sp.sqrt_delta_t;
            func = sp.func;
            return *this;
        }

        void Mesh(unsigned int n)
        {
            bm->Mesh(n);
        }

        //for std::vector and std::valarray
        template<typename CONTAIN, typename RAND>
        void GetPathForSTD(CONTAIN &contain, RAND &random) const
        {
            unsigned int start = 0;

            bm->GetPathForSTD(contain, random);
            for (unsigned int i = start; i < bm->GetSteps() +start + 1; ++i)
            {
                contain[i] = func(bm->Range(i+1), contain[i]);
            }
        }

        //VECTOR has operator(int) start by 1
        template<typename VECTOR, typename RAND>
        void GetPath(VECTOR &contain, RAND &random) const
        {
            unsigned int start = 1;

            bm->GetPath(contain, random);
            for (unsigned int i = start; i < bm->GetSteps() +start + 1; ++i)
            {
                contain(i) = func(bm->Range(i), contain(i));
            }

        }

        //Get InfPath by delta_time = dt
        template<typename RAND>
        TYPE GetPathInf(RAND &random, const TYPE &dt) const
        {
            if (first)
            {
                first = false;
                return func(time, bm->GetPathInf(random, dt));
            }
            else
            {
                time += dt;
                return func(time, bm->GetPathInf(random, dt));
            }
        }

        //change the state of object to restart at 0
        void ReStart() const
        {
            time = bm->Range(1);
            first = true;
            bm->ReStart();
        }

        Range<TYPE> GetRange() const
        {
            return bm->Range();
        }

        TYPE Range(unsigned int i) const
        {
            return bm->Range(i);
        }

        //change the function
        FUNCTION & Func()const
        {
            return func;
        }
    };

}


#endif

