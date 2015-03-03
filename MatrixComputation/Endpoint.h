#ifndef ENDPOINT_H
#define ENDPOINT_H

#include <iostream>

class Endpoint
{
public:
    enum Location { Left, Right };
private:
    int point;
    Location location;
public:
    Endpoint(){}

    Endpoint(const int &p, const Endpoint::Location &l) : point(p), location(l){}

    Endpoint(const Endpoint &e) : point(e.point), location(e.location){}

    Endpoint & operator = (const Endpoint &e)
    {
        if (&e == this)
        {
            return *this;
        }
        point = e.point, location = e.location;
        return *this;
    }

    void Set(const int &p, const Endpoint::Location &l)
    {
        point = p; location = l;
    }

    void Set(const Endpoint &e)
    {
        point = e.point; location = e.location;
    }

    const int & GetPoint() const
    {
        return point;
    }

    const Endpoint::Location & GetLocaton() const
    {
        return location;
    }

    void SetPoint(const int &p)
    {
        point = p;
    }

    void SetLocation(const Endpoint::Location &l)
    {
        location = l;
    }

    bool IsLeft() const
    {
        switch (location)
        {
        case Location::Left:
            return true;
        case Location::Right:
            return false;
        default:
            return true;
        }
    }

    bool IsRight() const
    {
        switch (location)
        {
        case Location::Left:
            return false;
        case Location::Right:
            return true;
        default:
            return true;
        }
    }

    void Shift(const int &n)
    {
        point += n;
    }

    friend std::ostream & operator << (std::ostream &, const Endpoint &);

    friend bool operator >  (const Endpoint &, const Endpoint &);
    friend bool operator >= (const Endpoint &, const Endpoint &);
    friend bool operator <  (const Endpoint &, const Endpoint &);
    friend bool operator <= (const Endpoint &, const Endpoint &);
    friend bool operator == (const Endpoint &, const Endpoint &);
    friend bool operator != (const Endpoint &, const Endpoint &);

    friend bool operator >  (const Endpoint &, const int &);
    friend bool operator >= (const Endpoint &, const int &);
    friend bool operator <  (const Endpoint &, const int &);
    friend bool operator <= (const Endpoint &, const int &);
    friend bool operator == (const Endpoint &, const int &);
    friend bool operator != (const Endpoint &, const int &);

    friend bool operator >  (const int &, const Endpoint &);
    friend bool operator >= (const int &, const Endpoint &);
    friend bool operator <  (const int &, const Endpoint &);
    friend bool operator <= (const int &, const Endpoint &);
    friend bool operator == (const int &, const Endpoint &);
    friend bool operator != (const int &, const Endpoint &);
};

inline std::ostream & operator << (std::ostream &out, const Endpoint &e)
{
    if (e.location == Endpoint::Location::Left)
    {
        out << '(' << e.point << ", L)";
    }
    else
    {
        out << '(' << e.point << ", R)";
    }
    return out;
}

/*Endpoint vs Endpoint*/

inline bool operator >  (const Endpoint &e1, const Endpoint &e2)
{
    if (e1.point > e2.point)
    {
        return true;
    }
    else if (e1.point < e2.point)
    {
        return false;
    }
    else
    {
        return e1.location > e2.location;
    }
}

inline bool operator >= (const Endpoint &e1, const Endpoint &e2)
{
    bool t = e1 < e2;
    return !t;
}

inline bool operator <  (const Endpoint &e1, const Endpoint &e2)
{
    if (e1.point < e2.point)
    {
        return true;
    }
    else if (e1.point > e2.point)
    {
        return false;
    }
    else
    {
        return e1.location < e2.location;
    }
}

inline bool operator <= (const Endpoint &e1, const Endpoint &e2)
{
    bool t = e1 > e2;
    return !t;
}

inline bool operator == (const Endpoint &e1, const Endpoint &e2)
{
    bool t = (e1 >= e2) && (e1 <= e2);
    return t;
}

inline bool operator != (const Endpoint &e1, const Endpoint &e2)
{
    bool t = e1 == e2;
    return !t;
}

/*Endpoint vs int*/

inline bool operator >  (const Endpoint &e, const int &p)
{
    return e.point > p;
}

inline bool operator >= (const Endpoint &e, const int &p)
{
    return e.point >= p;
}

inline bool operator <  (const Endpoint &e, const int &p)
{
    return e.point < p;
}

inline bool operator <= (const Endpoint &e, const int &p)
{
    return e.point <= p;
}

inline bool operator == (const Endpoint &e, const int &p)
{
    return e.point == p;
}

inline bool operator != (const Endpoint &e, const int &p)
{
    return e.point != p;
}

/*int vs Endpoint*/

inline bool operator >  (const int &p, const Endpoint &e)
{
    return p > e.point;
}

inline bool operator >= (const int &p, const Endpoint &e)
{
    return p >= e.point;
}

inline bool operator <  (const int &p, const Endpoint &e)
{
    return p < e.point;
}

inline bool operator <= (const int &p, const Endpoint &e)
{
    return p <= e.point;
}

inline bool operator == (const int &p, const Endpoint &e)
{
    return p == e.point;
}

inline bool operator != (const int &p, const Endpoint &e)
{
    return p != e.point;
}

#endif //ENDPOINT_H
