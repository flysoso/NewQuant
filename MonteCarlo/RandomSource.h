#ifndef RandomSource_H
#define RandomSource_H

namespace NewQuant
{
    template<typename TYPE, typename ENGINE, typename DISTRIBUTION>
    class RandomSource
    {
    public:
        ENGINE engine;
        DISTRIBUTION distribution;

    public:
        RandomSource(const ENGINE &eng, const DISTRIBUTION &dist) : engine(eng), distribution(dist) {}
        TYPE operator () ()
        {
            return distribution(engine);
        }

        ENGINE * GetEngine() const
        {
            return &engine;
        }

        DISTRIBUTION * GetDistribution() const
        {
            return &distribution;
        }
    };

}


#endif //RandomSource_H

