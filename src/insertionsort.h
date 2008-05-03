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

#ifndef INSERTIONSORT_H
#define INSERTIONSORT_H

#include <cassert>

namespace algorithm
{
    /// \brief Sort the \b length elements using the Insertion Sort algorithm.
    /// \param T The data type of the elements.
    /// \param[in,out] data The pointer to the list of elements.
    /// \param[in] length The number of elements.
    template <typename T>
    void insertion_sort(T* data, long length);

    /// \brief Sort the elements from \b istart to \b iend using the Insertion Sort algorithm.
    /// \param T The data type of the elements.
    /// \param[in,out] data The pointer to the list of elements.
    /// \param[in] istart The index of the first elements to sort.
    /// \param[in] iend The index of the last elements to sort.
    template <typename T>
    void insertion_sort(T* data, long istart, long iend);
} // namespace algorithm


// ===================================================================
// Implementation
// ===================================================================

namespace algorithm
{
    template <typename T>
    static long shift_vacant(T* data, long xindex, T x);


    /// \par References:
    /// Computer Algorithms Introduction to Design and Analysis - Sara Baase & Allen Van Gelder
    template <typename T>
    void insertion_sort(T* data, long length)
    {
        assert(length > 0);

        for (long i = 0; i < length; i++) {
            T current = data[i];
            long xloc = shift_vacant(data, i, current);
            data[xloc] = current;
        }
    }


    template <typename T>
    void insertion_sort(T* data, long istart, long iend)
    {
        assert(iend - istart + 1 > 0);

        long length = iend - istart + 1;
        insertion_sort(data, length);
    }


    template <typename T>
    long shift_vacant(T* data, long xindex, T x)
    {
        long vacant, xloc;
        vacant = xindex;
        xloc = 0;
        while (vacant > 0) {
            if (data[vacant-1] <= x) {
                xloc = vacant;
                break;
            }
            data[vacant] = data[vacant-1];
            vacant--;
        }
        return xloc;
    }
} // namespace algorithm

#endif // INSERTIONSORT_H

