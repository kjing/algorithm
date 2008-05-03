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

#ifndef LINEARCONGRUENTIAL_H
#define LINEARCONGRUENTIAL_H

namespace algorithm
{
    template <typename T>
    class LinearCongruential
    {
    public:
        /// \brief Construct a linear congruential random number generator.<br>
        ///        \f$ X_{n+1} = (aX_n + c) \bmod m \f$
        /// \param[in] a The multiplier.
        /// \param[in] x0 The starting value.
        /// \param[in] c The increment.
        /// \param[in] m The modulus.
        LinearCongruential(const T& a, const T& x0, const T& c, const T& m);
        ~LinearCongruential(void);

        /// \brief Return the next number in the sequence.
        /// \return The next number in the sequence.
        const T& next(void);

    private:
        T m_a; ///< The multiplier.
        T m_x; ///< The current value.
        T m_c; ///< The increment.
        T m_m; ///< The modulus.
    };
} // namespace algorithm


// ===================================================================
// Implementation
// ===================================================================

namespace algorithm
{
    template <typename T>
    LinearCongruential<T>::LinearCongruential(const T& a, const T& x0, const T& c, const T& m) :
        m_a(a), m_x(x0), m_c(c), m_m(m)
    {
    }


    template <typename T>
    LinearCongruential<T>::~LinearCongruential(void)
    {
    }


    /// \par References:
    /// The Art of Computer Programming Volume 2: Seminumerical Algorithms - Donald E. Knuth
    template <typename T>
    const T& LinearCongruential<T>::next(void)
    {
        m_x = (m_a * m_x + m_c) % m_m;
        return m_x;
    }
} // namespace algorithm

#endif // LINEARCONGRUENTIAL_H

