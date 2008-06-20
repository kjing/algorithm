/*
# Copyright (c) 2007-2008 Chung Shin Yee <cshinyee@gmail.com>
#
#       http://github.com/xman
#       http://myxman.org
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License as
# published by the Free Software Foundation; either version 2 of the
# License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307
# USA.
#
# The GNU General Public License is contained in the file COPYING.
#
*/

#ifndef ARRAY2D_H
#define ARRAY2D_H

#include <cassert>

namespace algorithm
{
    template <typename T>
    class Array2D
    {
    public:
        Array2D(long nrow, long ncol);
        Array2D(const Array2D<T>& rhs);
        ~Array2D(void);

        T& operator()(long row, long col);
        const T& operator()(long row, long col) const;

        const Array2D<T>& operator=(const Array2D<T>& rhs);
        const Array2D<T>& operator=(const T& x);

        bool operator==(const Array2D<T>& rhs) const;
        bool operator!=(const Array2D<T>& rhs) const;

        long nrow(void) const;
        long ncol(void) const;

    private:
        T* m_data;
        long m_nrow;
        long m_ncol;
    };
} // namespace algorithm


// ===================================================================
// Implementation
// ===================================================================

namespace algorithm
{
    template <typename T>
    Array2D<T>::Array2D(long nrow, long ncol) : m_data(NULL), m_nrow(nrow), m_ncol(ncol)
    {
        assert(nrow > 0);
        assert(ncol > 0);
        assert(nrow * ncol > 0);

        long size = nrow * ncol;
        m_data = new T[size];

        assert(m_data != NULL);
    }


    template <typename T>
    Array2D<T>::Array2D(const Array2D<T>& rhs) : m_data(NULL), m_nrow(0), m_ncol(0)
    {
        assert(rhs.m_nrow > 0);
        assert(rhs.m_ncol > 0);
        assert(rhs.m_nrow * rhs.m_ncol > 0);
        assert(rhs.m_data != NULL);

        this->operator=(rhs);
    }


    template <typename T>
    Array2D<T>::~Array2D(void)
    {
        assert(m_data != NULL);

        delete[] m_data;
        m_data = NULL;
    }


    template <typename T>
    T& Array2D<T>::operator()(long row, long col)
    {
        return m_data[row*m_ncol + col];
    }


    template <typename T>
    const T& Array2D<T>::operator()(long row, long col) const
    {
        return m_data[row*m_ncol + col];
    }


    template <typename T>
    const Array2D<T>& Array2D<T>::operator=(const Array2D<T>& rhs)
    {
        long size;

        if (this == &rhs) return *this;

        size = rhs.m_nrow * rhs.m_ncol;
        if (m_nrow != rhs.m_nrow || m_ncol != rhs.m_ncol) {
            delete[] m_data;
            m_nrow = rhs.m_nrow;
            m_ncol = rhs.m_ncol;
            m_data = new T[size];

            assert(m_data != NULL);
        }

        for (long i = 0; i < size; i++) {
            m_data[i] = rhs.m_data[i];
        }
        return *this;
    }


    template <typename T>
    const Array2D<T>& Array2D<T>::operator=(const T& x)
    {
        long size = m_nrow * m_ncol;
        for (long i = 0; i < size; i++) {
            m_data[i] = x;
        }
        return *this;
    }


    template <typename T>
    bool Array2D<T>::operator==(const Array2D<T>& rhs) const
    {
        if (m_nrow != rhs.m_nrow || m_ncol != rhs.m_ncol) {
            return false;
        }

        assert(m_nrow == rhs.m_nrow && m_ncol == rhs.m_ncol);

        const Array2D<T>& lhs = *this;
        for (long i = 0; i < m_nrow; i++) {
            for (long k = 0; k < m_ncol; k++) {
                if (lhs(i ,k) != rhs(i ,k)) {
                    return false;
                }
            }
        }
        return true;
    }


    template <typename T>
    bool Array2D<T>::operator!=(const Array2D<T>& rhs) const
    {
        return !(this->operator==(rhs));
    }


    template <typename T>
    long Array2D<T>::nrow(void) const
    {
        return m_nrow;
    }


    template <typename T>
    long Array2D<T>::ncol(void) const
    {
        return m_ncol;
    }
} // namespace algorithm

#endif // ARRAY2D_H
