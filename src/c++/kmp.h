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

// The Knuth-Morris-Pratt algorithm for the string matching problem.

#ifndef KMP_H
#define KMP_H

#include <cassert>

namespace algorithm
{
    /// \brief Construct KMP failure links.
    /// \param[in] pattern The pattern string.
    /// \param[in] length The length of the pattern string.
    /// \param[out] failure_link The failure links for the pattern string.
    void kmp_setup(const char* pattern, long length, long* failure_link);

    /// \brief Scan the text string for the occurrence of the pattern string using the KMP algorithm.
    /// \param[in] pattern The pattern string.
    /// \param[in] text The null-terminated text string.
    /// \param[in] length The length of the pattern string.
    /// \param[in] failure_link The failure links for the pattern string.
    /// \return The index in \b text where a copy of \b pattern begins.
    /// \return -1 if no match for \b pattern is found.
    long kmp_scan(const char* pattern, const char* text, long length, const long* failure_link);
} // namespace algorithm


// ===================================================================
// Implementation
// ===================================================================

namespace algorithm
{
    void kmp_setup(const char* pattern, long length, long* failure_link)
    {
        assert(length > 0);

        failure_link[0] = -1;
        for (long k = 1; k < length; k++) {
            long s = failure_link[k-1];
            while (s >= 0) {
                if (pattern[s] == pattern[k-1]) {
                    break;
                }
                s = failure_link[s];
            }
            failure_link[k] = s + 1;
        }
    }


    /// \par References:
    /// Computer Algorithms Introduction to Design and Analysis - Sara Baase & Allen Van Gelder
    long kmp_scan(const char* pattern, const char* text, long length, const long* failure_link)
    {
        assert(length > 0);

        long match = -1;
        long j = 0;
        long k = 0;

        while (text[j] != '\0') {
            if (k == -1) {
                j++;
                k = 0;
            } else if (text[j] == pattern[k]) {
                j++;
                k++;
            } else {
                k = failure_link[k];
            }

            if (k >= length) {
                match = j - length;
                break;
            }
        }
        return match;
    }
} // namespace algorithm

#endif // KMP_H
