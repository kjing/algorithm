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

#ifndef LONGESTCOMMONSUBSEQUENCE_H
#define LONGESTCOMMONSUBSEQUENCE_H

#include <cassert>

namespace algorithm
{
    /// \brief Compute the longest common subsequence length of the two sequences.
    /// \param[in] x The pointer to the first element of the sequence <b>x</b>.
    /// \param[in] lx The number of elements in the sequence <b>x</b>.
    /// \param[in] y The pointer to the first element of the sequence <b>y</b>.
    /// \param[in] ly The number of elements in the sequence <b>y</b>.
    /// \return The length of the longest common subsequence of <b>x</b> and <b>y</b>.
    template <typename T>
    long lcs_length(const T* x, long lx, const T* y, long ly);
} // namespace algorithm


// ===================================================================
// Implementation
// ===================================================================

namespace algorithm
{
    /// Compute the LCS length using O(lx + ly) space and O(lx * ly) time.
    template <typename T>
    long lcs_length(const T* x, long lx, const T* y, long ly)
    {
        long length;
        long cik;
        long next_cik;

        if (lx == 0 || ly == 0) {
            return 0;
        }

        long* c = new long[ly + 1];
        assert(c != NULL);
        for (long i = 0; i < ly + 1; ++i) {
            c[i] = 0;
        }

        for (long i = 0; i < lx; ++i) {
            // k = 0, c[0] == 0
            next_cik = c[1];
            if (x[i] == y[0]) {
                c[1] = 1;
            }
            cik = next_cik;

            for (long k = 1; k < ly; ++k) {
                next_cik = c[k+1];
                if (x[i] == y[k]) {
                    c[k+1] = cik + 1;
                } else if (c[k] >= c[k+1]) {
                    c[k+1] = c[k];
                }
                cik = next_cik;
            }
        }

        length = c[ly];
        delete[] c;
        return length;
    }
} // namespace algorithm

#endif // LONGESTCOMMONSUBSEQUENCE_H
