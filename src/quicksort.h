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

#ifndef QUICKSORT_H
#define QUICKSORT_H

#include <cassert>

namespace algorithm
{
    /// \brief Sort the \b length elements using the Quick Sort algorithm.
    /// \param T The data type of the elements.
    /// \param data The pointer to the list of elements.
    /// \param length The number of elements.
    template <typename T>
    void quick_sort(T* data, long length);

    /// \brief Sort the elements from \b istart to \b iend using the Quick Sort algorithm.
    /// \param T The data type of the elements.
    /// \param data The pointer to the list of elements.
    /// \param istart The index of the first elements to sort.
    /// \param iend The index of the last elements to sort.
    template <typename T>
    void quick_sort(T* data, long istart, long iend);
} // namespace algorithm


// ===================================================================
// Implementation
// ===================================================================

namespace algorithm
{
    template <typename T>
    void quick_sort(T* data, long length)
    {
        assert(length > 0);

        quick_sort(data, 0, length-1);
    }


    template <typename T>
    void quick_sort(T* data, long istart, long iend)
    {
        assert(istart <= iend);

        T pivot;
        T temp;
        long i, j, mid;

        // Select a pivot.
        mid = (istart + iend + 1) / 2;
        pivot = data[mid];

        // Swap the pivot with the first element.
        data[mid] = data[istart];
        data[istart] = pivot;

        // Partition.
        i = istart + 1;
        j = iend + 1;
        while (i < j) {
            if (data[i] <= pivot) {
                i++;
            } else {
                j--;
                temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
        data[istart] = data[j-1];
        data[j-1] = pivot;

        // Recursively sort the two partitions.
        if (istart < j-2) {
            quick_sort(data, istart, j-2);
        }
        if (j < iend) {
            quick_sort(data, j, iend);
        }
    }
} // namespace algorithm

#endif // QUICKSORT_H

