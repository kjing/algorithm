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

#ifndef MERGESORT_H
#define MERGESORT_H

#include <cassert>

namespace algorithm
{
    /// \brief Sort the \b length elements using the Merge Sort algorithm.
    /// \param T The data type of the elements.
    /// \param[in,out] data The pointer to the list of elements.
    /// \param[in] length The number of elements.
    template <typename T>
    void merge_sort(T* data, long length);

    /// \brief Sort the elements from \b istart to \b iend using the Merge Sort algorithm.
    /// \param T The data type of the elements.
    /// \param[in,out] data The pointer to the list of elements.
    /// \param[in] istart The index of the first elements to sort.
    /// \param[in] iend The index of the last elements to sort.
    template <typename T>
    void merge_sort(T* data, long istart, long iend);
} // namespace algorithm


// ===================================================================
// Implementation
// ===================================================================

namespace algorithm
{
    template <typename T>
    static void merge(T* data, long istart, long mid, long iend);


    template <typename T>
    void merge_sort(T* data, long length)
    {
        assert(length > 0);

        merge_sort(data, 0, length-1);
    }


    /// \par References:
    /// Computer Algorithms Introduction to Design and Analysis - Sara Baase & Allen Van Gelder
    template <typename T>
    void merge_sort(T* data, long istart, long iend)
    {
        assert(iend - istart + 1 > 0);

        if (istart < iend) {
            long mid = (istart + iend) / 2;
            merge_sort(data, istart, mid);
            merge_sort(data, mid+1, iend);
            merge(data, istart, mid, iend);
        }
    }


    template <typename T>
    void merge(T* data, long istart, long mid, long iend)
    {
        long n = iend - istart + 1;
        long k = mid - istart + 1;
        long m = n - k;
        long ia = 0, ib = 0, ic = 0;

        T* a = &data[istart];
        T* b = &data[mid+1];
        T* c = new T[n];

        assert(c != NULL);

        while (ia < k && ib < m) {
            if (a[ia] <= b[ib]) {
                c[ic] = a[ia];
                ia++;
                ic++;
            } else {
                c[ic] = b[ib];
                ib++;
                ic++;
            }
        }
        if (ia >= k) {
            for (long i = 0; i < n - ic; i++) {
                c[ic + i] = b[ib + i];
            }
        } else {
            for (long i = 0; i < n - ic; i++) {
                c[ic + i] = a[ia + i];
            }
        }

        for (long i = 0; i < n; i++) {
            data[istart + i] = c[i];
        }

        delete[] c;
    }
} // namespace algorithm

#endif // MERGESORT_H

