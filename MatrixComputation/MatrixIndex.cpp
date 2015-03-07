#ifndef MATRIX_INDEX_CPP
#define MATRIX_INDEX_CPP

#include <stack>
#include "MatrixIndex.h"

namespace NewQuant
{
    template<typename TYPE>
    void Union(const MatrixIndex<TYPE> &mi1, const MatrixIndex<TYPE> &mi2, MatrixIndex<TYPE> &mi)
    {
        using namespace std;
        mi.Clear();
        int s1 = mi1.Size(), s2 = mi2.Size();
        vector<Endpoint> endpoint_v(2 * (s1 + s2));

        for (int i = 0; i < s1; ++i)
        {
            endpoint_v[2 * i] = mi1.GetIndexList()[i].GetLeft();
            endpoint_v[2 * i + 1] = mi1.GetIndexList()[i].GetRight();
        }

        for (int i = 0; i < s2; ++i)
        {
            endpoint_v[2 * s1 + 2 * i] = mi2.GetIndexList()[i].GetLeft();
            endpoint_v[2 * s1 + 2 * i + 1] = mi2.GetIndexList()[i].GetRight();
        }

        sort(endpoint_v.begin(), endpoint_v.end());

        stack<Endpoint> endpoint_s;
        Endpoint t;
        for (int i = 0; i < endpoint_v.size(); ++i)
        {
            if (endpoint_v[i].IsLeft())
            {
                endpoint_s.push(endpoint_v[i]);
            }
            else
            {
                t = endpoint_s.top();
                endpoint_s.pop();
                if (endpoint_s.empty())
                {
                    mi.Append(t, endpoint_v[i]);
                }
            }
        }
    }

    template<typename TYPE>
    void Intersect(const MatrixIndex<TYPE> &mi1, const MatrixIndex<TYPE> &mi2, MatrixIndex<TYPE> &mi)
    {
        mi.Clear();
        int s1 = mi1.Size(), s2 = mi2.Size();
        Interval t;
        bool not_empty;

        for (int i = 0; i < s1; ++i)
        {
            for (int j = 0; j < s2; ++j)
            {
                Intersect(mi1.GetIndexList()[i], mi2.GetIndexList()[j], t, not_empty);
                if (not_empty)
                {
                    mi.Append(t);
                }
            }
        }
    }
}
#endif //MATRIX_INDEX_CPP
