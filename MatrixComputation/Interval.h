#ifndef INTERVAL_H
#define INTERVAL_H

#include <algorithm>
#include <assert.h>
#include "Endpoint.h"

class Interval
{
private:
    Endpoint left, right;

public:
    Interval() : left(0, Endpoint::Location::Left), right(0, Endpoint::Location::Right){}

    Interval(const int &l, const int &r) : left(l, Endpoint::Location::Left), right(r, Endpoint::Location::Right){}

    Interval(const Endpoint &l, const Endpoint &r) : left(l), right(r){}

    Interval(const Interval &i) : left(i.left), right(i.right){}

    Interval & operator = (const Interval &i)
    {
        if (&i == this)
        {
            return *this;
        }
        left = i.left, right = i.right;
        return *this;
    }

    void Set(const int &l, const int &r)
    {
        assert(l <= r);
        left.SetPoint(l);
        right.SetPoint(r);
    }

    void SetLeft(const int &n)
    {
        left.SetPoint(n);
    }

    void SetRight(const int &n)
    {
        right.SetPoint(n);
    }

    const Endpoint & GetLeft()const
    {
        return left;
    }

    const Endpoint & GetRight()const
    {
        return right;
    }

    void Shift(const int &n)
    {
        left.Shift(n), right.Shift(n);
    }

    friend bool operator >  (const int &, const Interval &);
    friend bool operator >= (const int &, const Interval &);
    friend bool operator <  (const int &, const Interval &);
    friend bool operator <= (const int &, const Interval &);
    friend bool operator == (const int &, const Interval &);
    friend bool operator != (const int &, const Interval &);

    friend bool operator >  (const Interval &, const int &);
    friend bool operator >= (const Interval &, const int &);
    friend bool operator <  (const Interval &, const int &);
    friend bool operator <= (const Interval &, const int &);
    friend bool operator == (const Interval &, const int &);
    friend bool operator != (const Interval &, const int &);
};

inline void Intersect(const Interval &i1, const Interval &i2, Interval &i, bool &not_empty)
{
    int l = std::max(i1.GetLeft().GetPoint(), i1.GetLeft().GetPoint());
    int r = std::min(i1.GetRight().GetPoint(), i2.GetRight().GetPoint());

    if (l > r)
    {
        not_empty = false;
        return;
    }
    else
    {
        not_empty = true;
        i.Set(l, r);
    }
}

/*int vs Interval*/
inline bool operator >  (const int &x, const Interval &i)
{
    return x > i.right;
}

inline bool operator >= (const int &x, const Interval &i)
{
    return x >= i.left;
}

inline bool operator <  (const int &x, const Interval &i)
{
    return x < i.left;
}

inline bool operator <= (const int &x, const Interval &i)
{
    return x <= i.right;
}

inline bool operator == (const int &x, const Interval &i)
{
    return i.left <= x && x <= i.right;
}

inline bool operator != (const int &x, const Interval &i)
{
    return i.left > x || x > i.right;
}

/*Interval vs int*/
inline bool operator >  (const Interval &i, const int &x)
{
    return i.left > x;
}

inline bool operator >= (const Interval &i, const int &x)
{
    return i.right >= x;
}

inline bool operator <  (const Interval &i, const int &x)
{
    return i.right < x;
}

inline bool operator <= (const Interval &i, const int &x)
{
    return i.left <= x;
}

inline bool operator == (const Interval &i, const int &x)
{
    return i.left <= x && x <= i.right;;
}

inline bool operator != (const Interval &i, const int &x)
{
    return i.left > x || x > i.right;
}

#endif //INTERVAL_H
