#ifndef VECTOR_H
#define VECTOR_H

namespace NewQuant
{
    template<typename TYPE>
    class Vector
    {
    protected:
        int length;

        Vector(){}

        Vector(const int &l) : length(l) {}

        Vector(const Vector<TYPE> &v) : length(v.length){}

        void SetLength(const int &l)
        {
            length = l;
        }
    public:
        ~Vector() {}

        const int & Length() const
        {
            return length;
        }

        virtual void Resize(const int &) = 0;

        virtual TYPE operator () (const int &) const = 0;

        virtual TYPE & operator () (const int &) = 0;

    };
}

#endif // VECTOR_H
