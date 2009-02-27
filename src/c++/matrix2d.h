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

#ifndef MATRIX2D_H
#define MATRIX2D_H

#include <cassert>
#include <iostream>

namespace algorithm
{
    template <typename T>
    class Matrix2D
    {
    public:
        Matrix2D(long nrow, long ncol);
        Matrix2D(const Matrix2D<T>& rhs);
        ~Matrix2D(void);

        T& operator()(long row, long col);
        const T& operator()(long row, long col) const;

        const Matrix2D<T>& operator=(const Matrix2D<T>& rhs);
        const Matrix2D<T>& operator=(const T& x);

        const Matrix2D<T> operator+(const Matrix2D<T>& rhs) const;
        const Matrix2D<T> operator-(const Matrix2D<T>& rhs) const;
        const Matrix2D<T> operator*(const Matrix2D<T>& rhs) const;

        const Matrix2D<T>& operator+=(const Matrix2D<T>& rhs);
        const Matrix2D<T>& operator-=(const Matrix2D<T>& rhs);
        const Matrix2D<T>& operator*=(const Matrix2D<T>& rhs);

        bool operator==(const Matrix2D<T>& rhs);

        const Matrix2D<T> transpose(void) const;

        long nrow(void) const;
        long ncol(void) const;

        void print(void) const;

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
    Matrix2D<T>::Matrix2D(long nrow, long ncol) : m_data(NULL), m_nrow(nrow), m_ncol(ncol)
    {
        assert(nrow > 0);
        assert(ncol > 0);
        assert(nrow * ncol > 0);

        long size = nrow * ncol;
        m_data = new T[size];

        assert(m_data != NULL);
    }


    template <typename T>
    Matrix2D<T>::Matrix2D(const Matrix2D<T>& rhs) : m_data(NULL), m_nrow(0), m_ncol(0)
    {
        assert(rhs.m_nrow > 0);
        assert(rhs.m_ncol > 0);
        assert(rhs.m_nrow * rhs.m_ncol > 0);
        assert(rhs.m_data != NULL);

        this->operator=(rhs);
    }


    template <typename T>
    Matrix2D<T>::~Matrix2D(void)
    {
        assert(m_data != NULL);

        delete[] m_data;
        m_data = NULL;
    }


    template <typename T>
    T& Matrix2D<T>::operator()(long row, long col)
    {
        return m_data[row*m_ncol + col];
    }


    template <typename T>
    const T& Matrix2D<T>::operator()(long row, long col) const
    {
        return m_data[row*m_ncol + col];
    }


    template <typename T>
    const Matrix2D<T>& Matrix2D<T>::operator=(const Matrix2D<T>& rhs)
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
    const Matrix2D<T>& Matrix2D<T>::operator=(const T& x)
    {
        long size = m_nrow * m_ncol;
        for (long i = 0; i < size; i++) {
            m_data[i] = x;
        }
        return *this;
    }


    template <typename T>
    const Matrix2D<T> Matrix2D<T>::operator+(const Matrix2D<T>& rhs) const
    {
        assert(m_nrow == rhs.m_nrow && m_ncol == rhs.m_ncol);

        const Matrix2D<T>& lhs = *this;
        long size = m_nrow * m_ncol;
        Matrix2D<T> r(m_nrow, m_ncol);
        for (long i = 0; i < size; i++) {
            r.m_data[i] = lhs.m_data[i] + rhs.m_data[i];
        }
        return r;
    }


    template <typename T>
    const Matrix2D<T> Matrix2D<T>::operator-(const Matrix2D<T>& rhs) const
    {
        assert(m_nrow == rhs.m_nrow && m_ncol == rhs.m_ncol);

        const Matrix2D<T>& lhs = *this;
        long size = m_nrow * m_ncol;
        Matrix2D<T> r(m_nrow, m_ncol);
        for (long i = 0; i < size; i++) {
            r.m_data[i] = lhs.m_data[i] - rhs.m_data[i];
        }
        return r;
    }


    template <typename T>
    const Matrix2D<T> Matrix2D<T>::operator*(const Matrix2D<T>& rhs) const
    {
        assert(m_ncol == rhs.m_nrow);

        const Matrix2D<T>& lhs = *this;
        long msize = lhs.m_nrow;
        long nsize = lhs.m_ncol;
        long psize = rhs.m_ncol;

        Matrix2D<T> r(msize, psize);
        r = T(0);
        // Naive matrix multiplication.
        // R_mp <- LHS_mn * RHS_np
        for (long m = 0; m < msize; m++) {
            for (long n = 0; n < nsize; n++) {
                for (long p = 0; p < psize; p++) {
                    r(m, p) += lhs(m, n) * rhs(n, p);
                }
            }
        }
        return r;
    }


    template <typename T>
    const Matrix2D<T>& Matrix2D<T>::operator+=(const Matrix2D<T>& rhs)
    {
        assert(m_nrow == rhs.m_nrow && m_ncol == rhs.m_ncol);

        Matrix2D<T>& lhs = *this;
        long size = m_nrow * m_ncol;
        for (long i = 0; i < size; i++) {
            lhs.m_data[i] += rhs.m_data[i];
        }
        return *this;
    }


    template <typename T>
    const Matrix2D<T>& Matrix2D<T>::operator-=(const Matrix2D<T>& rhs)
    {
        assert(m_nrow == rhs.m_nrow && m_ncol == rhs.m_ncol);

        Matrix2D<T>& lhs = *this;
        long size = m_nrow * m_ncol;
        for (long i = 0; i < size; i++) {
            lhs.m_data[i] -= rhs.m_data[i];
        }
        return *this;
    }


    template <typename T>
    const Matrix2D<T>& Matrix2D<T>::operator*=(const Matrix2D<T>& rhs)
    {
        assert(m_ncol == rhs.m_nrow);

        *this = this->operator*(rhs);
        return *this;
    }


    template <typename T>
    bool Matrix2D<T>::operator==(const Matrix2D<T>& rhs)
    {
        if (m_nrow != rhs.m_nrow || m_ncol != rhs.m_ncol) {
            return false;
        }

        assert(m_nrow == rhs.m_nrow && m_ncol == rhs.m_ncol);

        const Matrix2D<T>& lhs = *this;
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
    const Matrix2D<T> Matrix2D<T>::transpose(void) const
    {
        const Matrix2D<T>& lhs = *this;
        long nrow = m_ncol;
        long ncol = m_nrow;
        Matrix2D<T> r(nrow, ncol);
        for (long i = 0; i < nrow; i++) {
            for (long k = 0; k < ncol; k++) {
                r(i, k) = lhs(k, i);
            }
        }
        return r;
    }


    template <typename T>
    long Matrix2D<T>::nrow(void) const
    {
        return m_nrow;
    }


    template <typename T>
    long Matrix2D<T>::ncol(void) const
    {
        return m_ncol;
    }


    template <typename T>
    void Matrix2D<T>::print(void) const
    {
        const Matrix2D<T>& lhs = *this;
        for (long i = 0; i < m_nrow; i++) {
            for (long j = 0; j < m_ncol; j++) {
                std::cout << lhs(i,j) << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }
} // namespace algorithm

#endif // MATRIX2D_H
