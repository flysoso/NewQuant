#ifndef GENERAL_MATRIX_CPP
#define GENERAL_MATRIX_CPP

#include "GeneralMatrix.h"

#include "../ExceptionClass/BadAllocation.h"

namespace NewQuant
{
    template<typename TYPE>
    const TYPE GeneralMatrix<TYPE>::zero(0);

    template<typename TYPE>
    GeneralMatrix<TYPE>::GeneralMatrix()
    {
        store = NULL;
        storage = 0;
        nrows = 0;
        ncols = 0;
        zero_buff = zero;
    }

    template<typename TYPE>
    GeneralMatrix<TYPE>::GeneralMatrix(const int &r, const int &c, const int &s, const MatrixBandWidth<TYPE> &mbw)
    {
        if (s == 0)
        {
            store = NULL;
        }
        else
        {
            store = new TYPE[s];
            if (store == NULL)
            {
                Singleton<Tracer>::Instance()->AddMessage("GeneralMatrix::GeneralResize(nr, nc, s)");
                throw BadAllocation("No Space for Matrix");
            }
        }
        storage = s;
        nrows = r;
        ncols = c;
        zero_buff = zero;
        band_width = mbw;
    }

    template<typename TYPE>
    GeneralMatrix<TYPE>::GeneralMatrix(const int &r, const int &c, const int &s)
    {
        if (s == 0)
        {
            store = NULL;
        }
        else
        {
            store = new TYPE[s];
            if (store == NULL)
            {
                Singleton<Tracer>::Instance()->AddMessage("GeneralMatrix::GeneralResize(nr, nc, s)");
                throw BadAllocation("No Space for Matrix");
            }
        }
        storage = s;
        nrows = r;
        ncols = c;
        zero_buff = zero;
    }

    template<typename TYPE>
    GeneralMatrix<TYPE>::~GeneralMatrix()
    {
        if (store)
        {
            delete[] store;
        }
    }

    template<typename TYPE>
    void GeneralMatrix<TYPE>::operator << (const TYPE &f)
    {
        int i = storage;
        TYPE* s = store;
        while (i--)
        {
            *s++ = f;
        }
    }

    template<typename TYPE>
    void GeneralMatrix<TYPE>::operator << (const int &f)
    {
        int i = storage;
        TYPE* s = store;
        while (i--)
        {
            *s++ = TYPE(f);
        }
    }

    template<typename TYPE>
    void GeneralMatrix<TYPE>::operator *= (const TYPE &r)
    {
        int i = storage;
        TYPE* s = store;
        while (i--)
        {
            *s++ *= r;
        }
    }

    template<typename TYPE>
    void GeneralMatrix<TYPE>::Add(const TYPE &f)
    {
        TYPE* s = store;
        int i = (storage >> 2);
        while (i--)
        {
            *s++ += f;
            *s++ += f;
            *s++ += f;
            *s++ += f;
        }
        i = storage & 3;
        while (i--)
        {
            *s++ += f;
        }
    }

    template<typename TYPE>
    void GeneralMatrix<TYPE>::NegAdd(const TYPE &f)
    {
        TYPE* s = store;
        int i = (storage >> 2);
        while (i--)
        {
            *s = f - *s;
            s++;
            *s = f - *s;
            s++;
            *s = f - *s;
            s++;
            *s = f - *s;
            s++;
        }
        i = storage & 3;
        while (i--)
        {
            *s = f - *s;
            s++;
        }
    }

    template<typename TYPE>
    void GeneralMatrix<TYPE>::Multiply(const TYPE &f)
    {
        TYPE* s = store;
        int i = (storage >> 2);
        while (i--)
        {
            *s++ *= f;
            *s++ *= f;
            *s++ *= f;
            *s++ *= f;
        }
        i = storage & 3;
        while (i--)
        {
            *s++ *= f;
        }
    }

    template<typename TYPE>
    void GeneralMatrix<TYPE>::Negate()
    {
        TYPE* s = store;
        int i = (storage >> 2);
        while (i--)
        {
            *s = -(*s);
            s++;
            *s = -(*s);
            s++;
            *s = -(*s);
            s++;
            *s = -(*s);
            s++;
        }
        i = storage & 3;
        while (i--)
        {
            *s = -(*s);
            s++;
        }
    }

    template<typename TYPE>
    void GeneralMatrix<TYPE>::ReverseElements()
    {
        // reversing in place
        int n = Storage();
        TYPE* x = Store();
        TYPE* rx = x + n;
        n /= 2;
        while (n--)
        {
            TYPE t = *(--rx);
            *rx = *x;
            *(x++) = t;
        }
    }

    template<typename TYPE>
    void GeneralMatrix<TYPE>::CopyMatrix(const GeneralMatrix<TYPE> &gmx)
    {
        if (&gmx == this)
        {
            return;
        }
        nrows = gmx.nrows;
        ncols = gmx.ncols;
        storage = gmx.storage;
        band_width = gmx.band_width;

        if (store != NULL)
        {
            delete[] store;
        }
        store = new TYPE[storage];
        NewQuantBlockCopy(storage, gmx.store, store);
    }

    template<typename TYPE>
    void GeneralMatrix<TYPE>::GeneralResize(const int &nr, const int &nc, const int &s)
    {
        if (s != 0)
        {
            if (s != storage)
            {
                if (store != NULL)
                {
                    delete[] store;
                }
                store = new TYPE[s];
                if (store == NULL)
                {
                    Singleton<Tracer>::Instance()->AddMessage("GeneralMatrix::GeneralResize(nr, nc, s)");
                    throw BadAllocation("No Space for Matrix");
                }
            }
        }
        else
        {
            if (store != NULL)
            {
                delete[] store;
            }
            store = NULL;
        }

        storage = s;
        nrows = nr;
        ncols = nc;

    }

    template<typename TYPE>
    void GeneralMatrix<TYPE>::PlusEqual(const GeneralMatrix<TYPE>& gm)
    {
        assert(nrows == gm.nrows && ncols == gm.ncols);
        AddTo(gm, *this);
    }

    template<typename TYPE>
    void GeneralMatrix<TYPE>::SP_Equal(const GeneralMatrix<TYPE>& gm)
    {
        assert(nrows == gm.nrows && ncols == gm.ncols);
        SP(this, &gm);
    }

    template<typename TYPE>
    void GeneralMatrix<TYPE>::MinusEqual(const GeneralMatrix<TYPE>& gm)
    {
        assert(nrows == gm.nrows && ncols == gm.ncols);
        SubtractFrom(this, &gm);
    }

    template<typename TYPE>
    void GeneralMatrix<TYPE>::Swap(GeneralMatrix<TYPE>& gm)
    {
        int t;
        t = nrows;
        nrows = gm.nrows;
        gm.nrows = t;
        t = ncols;
        ncols = gm.ncols;
        gm.ncols = t;
        t = storage;
        storage = gm.storage;
        gm.storage = t;

        TYPE* s = store;
        store = gm.store;
        gm.store = s;

        MatrixBandWidth<TYPE> mbw;
        mbw = band_width;
        band_width = gm.band_width;
        gm.band_width = mbw;
    }

    template<typename TYPE>
    bool GeneralMatrix<TYPE>::IsZero() const
    {
        TYPE* s = store;
        int i = storage >> 2;
        while (i--)
        {
            if (*s++)
            {
                return false;
            }
            if (*s++)
            {
                return false;
            }
            if (*s++)
            {
                return false;
            }
            if (*s++)
            {
                return false;
            }
        }
        i = storage & 3;
        while (i--)
        {
            if (*s++)
            {
                return false;
            }
        }
        return true;
    }

    template<typename TYPE>
    TYPE GeneralMatrix<TYPE>::Trace() const
    {
        assert(ncols == nrows);

        TYPE trace(0);
        for (int i = 1; i < nrows; ++i)
        {
            trace += (*this)(i, i);
        }
        return trace;
    }

    template<typename TYPE>
    std::ostream& operator<<(std::ostream& s, const GeneralMatrix<TYPE>& X)
    {
        using namespace std;
        ostream::fmtflags f = s.flags();
        if (f & ios::scientific)
        {
            s.setf(ios::scientific, ios::floatfield);
        }
        else
        {
            s.setf(ios::fixed, ios::floatfield);
        }

        std::streamsize w = s.width();
        int nr = X.Nrows(), nc = X.Ncols();
        MatrixIndex<TYPE> mi;
        for (int i = 1; i <= nr; ++i)
        {
            X.GetRowIndex(i, mi);
            for (int j = 1; j <= nc; ++j)
            {
                if (mi.HaveIndex(j))
                {
                    s.width(w);
                    s << X(i, j) << ' ';
                }
                else
                {
                    s.width(w);
                    s << ' ' << ' ';
                }
            }
            s << '\n';
        }
        s << flush;
        s.flags();
        return s;
    }
}
#endif //GENERAL_MATRIX_CPP
