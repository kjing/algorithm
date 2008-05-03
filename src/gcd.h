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

#ifndef GCD_H
#define GCD_H

#include "gcd/euclid.h"

namespace algorithm
{
    /// \brief Compute the greatest common divisor of two numbers.
    /// \param T The data type of the numbers.
    /// \param[in] a The first number.
    /// \param[in] b The second number.
    /// \return The greatest common divisor of the two numbers.
    template <typename T>
    const T gcd(const T& a, const T& b);
} // namespace algorithm


// ===================================================================
// Implementation
// ===================================================================

namespace algorithm
{
    template <typename T>
    inline const T gcd(const T& a, const T& b)
    {
        return euclid(a, b);
    }
} // namespace algorithm

#endif // GCD_H

