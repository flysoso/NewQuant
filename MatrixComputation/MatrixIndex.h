#ifndef MATRIX_INDEX_H
#define MATRIX_INDEX_H

#include <vector>
#include <memory>
#include "Interval.h"

template <typename TYPE> class MatrixIndexIterator;

template <typename TYPE>
class MatrixIndex
{
private:
    std::vector<Interval> index;    //store the positions, where the positions are evalued
    //by non-zero numbers theoreticaly
public:
    typedef MatrixIndexIterator<TYPE> Iterator;

    MatrixIndex(){}

    MatrixIndex(const int &n) : index(n) {}

    MatrixIndex(const int &l, const int &r)
    {
        assert(l <= r);
        index.push_back(Interval(l, r));
    }

    MatrixIndex(const MatrixIndex<TYPE> &mi) : index(mi.index) {}

    ~MatrixIndex(){}

    MatrixIndex<TYPE> & operator = (const MatrixIndex<TYPE> &mi)
    {
        if (&mi == this)
        {
            return *this;
        }
        index = mi.index;
        return *this;
    }

    void Append(const Interval &i)
    {
        index.push_back(i);
    }

    void Append(const Endpoint &l, const Endpoint &r)
    {
        assert(l <= r);
        index.push_back(Interval(l, r));
    }

    void Append(const int &l, const int &r)
    {
        assert(l <= r);
        index.push_back(Interval(l, r));
    }

    void Clear()
    {
        index.clear();
    }

    int Size() const
    {
        return index.size();
    }

    void Resize(const int &n)
    {
        index.resize(n);
    }

    bool IsEmpty() const
    {
        return index.size() == 0;
    }

    Interval operator () (const int &i) const
    {
        assert(i - 1 <= index.size());
        return index[i - 1];
    }

    const std::vector<Interval> & GetIndexList() const
    {
        return index;
    }

    std::vector<Interval> & GetIndexList()
    {
        return index;
    }

    void Shift(const int &n)
    {
        for (int i = 0; i < index.size(); ++i)
        {
            index[i].Shift(n);
        }
    }

    bool HaveIndex(const int &idx) const
    {
        for (int i = 0; i < index.size(); ++i)
        {
            if (idx == index[i])
            {
                return true;
            }
        }
        return false;
    }

    Iterator Begin()
    {
        if (IsEmpty())
        {
            Iterator i(*this, 0, 0);
            return i;
        }
        else
        {
            int idx = GetIndexList()[0].GetLeft().GetPoint();
            Iterator i(*this, idx, 0);
            return i;
        }
    }

    Iterator End()
    {
        if (IsEmpty())
        {
            Iterator i(*this, 0, 0);
            return i;
        }
        else
        {
            int idx = GetIndexList()[Size() - 1].GetRight().GetPoint() + 1;
            Iterator i(*this, idx, Size());
            return i;
        }
    }



};

template <typename TYPE>
class MatrixIndexIterator
{
private:
    std::shared_ptr<MatrixIndex<TYPE> > mat_idx;
    int index;
    int step;
public:
    MatrixIndexIterator() :mat_idx(new MatrixIndex<TYPE>), index(0), step(0){}

    MatrixIndexIterator(MatrixIndex<TYPE> &mi, const int &i, const int &s) : mat_idx(&mi), index(i), step(s){}

    MatrixIndexIterator(const MatrixIndexIterator &i) : mat_idx(i.mat_idx), index(i.index), step(i.step){}

    ~MatrixIndexIterator(){}

    MatrixIndexIterator & operator = (const MatrixIndexIterator<TYPE> &i)
    {
        if (&i == this)
        {
            return *this;
        }
        mat_idx.reset(const_cast<MatrixIndex<TYPE> *>(i.mat_idx.get()));
        index = i.index, step = i.step;
        return *this;
    }

    int operator * ()const
    {
        return index;
    }

    MatrixIndexIterator & operator ++ ()
    {
        int i;
        if (step == mat_idx->Size() - 1)
        {
            i = index + 1;
            if (i == mat_idx->GetIndexList()[step])
            {
                ++index;
            }
            else
            {
                index = mat_idx->GetIndexList()[step].GetRight().GetPoint() + 1;
                ++step;
            }
        }
        else
        {
            i = index + 1;
            if (i == mat_idx->GetIndexList()[step])
            {
                ++index;
            }
            else
            {
                ++step;
                index = mat_idx->GetIndexList()[step].GetLeft().GetPoint();
            }
        }
        return *this;
    }

    MatrixIndexIterator operator ++ (int)
    {
        MatrixIndexIterator t(*this);
        ++(*this);
        return t;
    }

    template <typename T>
    friend bool operator == (const MatrixIndexIterator<T> &i1, const MatrixIndexIterator<T> &i2);

    template <typename T>
    friend bool operator != (const MatrixIndexIterator<T> &i1, const MatrixIndexIterator<T> &i2);
};

template <typename TYPE>
void Union(const MatrixIndex<TYPE> &, const MatrixIndex<TYPE> &, MatrixIndex<TYPE> &);

template <typename TYPE>
void Intersect(const MatrixIndex<TYPE> &, const MatrixIndex<TYPE> &, MatrixIndex<TYPE> &);

template <typename TYPE>
bool operator == (const MatrixIndexIterator<TYPE> &i1, const MatrixIndexIterator<TYPE> &i2)
{
    return (i1.mat_idx.get() == i2.mat_idx.get()) && (i1.index == i2.index) && (i1.step == i2.step);
}

template <typename TYPE>
bool operator != (const MatrixIndexIterator<TYPE> &i1, const MatrixIndexIterator<TYPE> &i2)
{
    return !(i1 == i2);
}

#include "MatrixIndex.cpp"

#endif //MATRIX_INDEX_H
