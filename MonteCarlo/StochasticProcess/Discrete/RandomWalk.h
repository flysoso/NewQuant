#ifndef RandomWalk_HPP
#define RandomWalk_HPP

namespace NewQuant
{
    template<typename TYPE>
    class RandomWalk
    {
    private:
        TYPE initial_value;
        mutable TYPE temp;
        mutable bool first;
        mutable unsigned int steps;
    public:
        RandomWalk(const TYPE &iv) : initial_value(iv), temp(iv), first(true), steps(0){}

        RandomWalk& operator = (const RandomWalk<TYPE> &rw)
        {
            initial_value = rw.initial_value;
            temp = rw.temp;
            first = rw.first;
            steps = rw.steps;
            return *this;
        }

        void Restart(const TYPE &t)
        {
            initial_value = t;
            temp = t;
            first = true;
            steps = 0;
        }

        void Restart()
        {
            temp = initial_value;
            first = true;
            steps = 0;
        }

        template<typename RAND>
        TYPE operator () (RAND &random) const
        {
            if (first)
            {
                first = false;
                return temp;
            }
            else
            {
                temp += random();
                ++steps;
                return temp;
            }
        }
        template<typename RAND, typename TREND>
        TYPE operator () (RAND &random, TREND &trend) const
        {
            if (first)
            {
                first = false;
                return temp;
            }
            else
            {
                temp += random();
                temp += trend(steps, temp);
                ++steps;
                return temp;
            }
        }

    };

}

#endif

