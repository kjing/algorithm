/*
# Copyright (c) 2008 Chung Shin Yee <cshinyee@gmail.com>
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

#ifndef EUCLID_H
#define EUCLID_H

#include <cassert>

namespace algorithm
{
    /// \brief Compute the greatest common divisor of two numbers using the Euclid's algorithm.
    /// \param T The data type of the numbers.
    /// \param[in] a The first number.
    /// \param[in] b The second number.
    /// \return The greatest common divisor of the two numbers.
    template <typename T>
    T euclid(const T& a, const T& b);

    /// \brief Compute the greatest common divisor of two numbers and its coefficients
    ///        using the Extended Euclid's algorithm.
    /// \param T The data type of the numbers.
    /// \param[in] a The first number.
    /// \param[in] b The second number.
    /// \param[out] x The first coefficient.
    /// \param[out] y The second coefficient.
    /// \return The greatest common divisor of the two numbers.
    template <typename T>
    T euclid(const T& a, const T& b, T* x, T* y);
} // namespace algorithm


// ===================================================================
// Implementation
// ===================================================================

namespace algorithm
{
    /// \par References:
    /// Introduction to Algorithms - T. H. Cormen, C. E. Leiserson, R. L. Rivest & C. Stein
    template <typename T>
    T euclid(const T& a, const T& b)
    {
        assert(a >= T(0));
        assert(b >= T(0));

        if (b == T(0)) {
            return a;
        } else {
            return euclid(b, a % b);
        }
    }


    /// \note gcd(a,b) = ax + by
    /// \par References:
    /// Introduction to Algorithms - T. H. Cormen, C. E. Leiserson, R. L. Rivest & C. Stein
    template <typename T>
    T euclid(const T& a, const T& b, T* x, T* y)
    {
        assert(a >= T(0));
        assert(b >= T(0));

        if (b == T(0)) {
            *x = T(1);
            *y = T(0);
            return a;
        }
        T x2;
        T y2;
        T d = euclid(b, a%b, &x2, &y2);
        *x = y2;
        *y = x2 - (a/b)*y2;
        return d;
    }
} // namespace algorithm

#endif // EUCLID_H

