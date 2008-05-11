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

#ifndef CACHEOBLIVIOUS_H
#define CACHEOBLIVIOUS_H

#include <cassert>
#include "matrix2d.h"

namespace algorithm
{
    /// Compute matrix multiplication using the Cache-Oblivious Matrix Multiplication algorithm.<br>
    /// C = A x B.
    /// \param[in] a The matrix A.
    /// \param[in] b The matrix B.
    /// \param[out] c The matrix C.
    template <typename T>
    void co_multiply(const Matrix2D<T>& a, const Matrix2D<T>& b, Matrix2D<T>& c);

    /// Compute matrix multiplication using the Cache-Oblivious Matrix Multiplication algorithm.<br>
    /// C_mp = A_mn x B_np.
    /// \param[in] a The Matrix A.
    /// \param[in] b The Matrix B.
    /// \param[out] c The Matrix C.
    /// \param[in] mstart The index of the first row of the matrix A.
    /// \param[in] mend The index of the last row of the matrix A.
    /// \param[in] nstart The index of the first column of the matrix A.
    /// \param[in] nend The index of the last column of the matrix A.
    /// \param[in] pstart The index of the first column of the matrix B.
    /// \param[in] pend The index of the last column of the matrix B.
    template <typename T>
    void co_multiply(const Matrix2D<T>& a, const Matrix2D<T>& b, Matrix2D<T>& c,
                     long mstart, long mend, long nstart, long nend, long pstart, long pend);

    /// Compute matrix transposition using the Cache-Oblivious Matrix Transposition algorithm.<br>
    /// B = A'.
    /// \param[in] a The matrix A.
    /// \param[out] b The matrix B.
    template <typename T>
    void co_transpose(const Matrix2D<T>& a, Matrix2D<T>& b);

    /// Compute matrix transposition using the Cache-Oblivious Matrix Transposition algorithm.<br>
    /// B_nm = A_mn'
    /// \param[in] a The matrix A_mn.
    /// \param[out] b The matrix B_nm.
    /// \param[in] mstart The index of the first row of the matrix A.
    /// \param[in] mend The index of the last row of the matrix A.
    /// \param[in] nstart The index of the first column of the matrix A.
    /// \param[in] nend The index of the last column of the matrix A.
    template <typename T>
    void co_transpose(const Matrix2D<T>& a, Matrix2D<T>& b,
                      long mstart, long mend, long nstart, long nend);
} // namespace algorithm


// ===================================================================
// Implementation
// ===================================================================

namespace algorithm
{
    template <typename T>
    void co_multiply(const Matrix2D<T>& a, const Matrix2D<T>& b, Matrix2D<T>& c)
    {
        assert(a.ncol() == b.nrow());

        long msize = a.nrow();
        long nsize = a.ncol();
        long psize = b.ncol();

        c = T(0);
        co_multiply(a, b, c, 0L, msize-1, 0L, nsize-1, 0L, psize-1);
    }


    /// \par References:
    /// \li Harald Prokop. Cache-Oblivious Algorithms. Masters thesis, MIT. 1999.
    /// \li M. Frigo, C. E. Leiserson, H. Prokop, and S. Ramachandran. Cache-oblivious algorithms.
    ///     In Proceedings of the 40th IEEE Symposium on Foundations of Computer Science, 1999.
    template <typename T>
    void co_multiply(const Matrix2D<T>& a, const Matrix2D<T>& b, Matrix2D<T>& c,
                     long mstart, long mend, long nstart, long nend, long pstart, long pend)
    {
        const long threshold = 32*1024;
        // Cache-Oblivious Matrix Multiplication.
        // C_mp <- A_mn * B_np
        long msize = mend - mstart + 1;
        long nsize = nend - nstart + 1;
        long psize = pend - pstart + 1;
        if (msize*nsize + nsize*psize + msize*psize < threshold) {
            // Naive matrix multiplication.
            // C_mp <- A_mn * B_np
            for (long m = mstart; m <= mend; m++) {
                for (long n = nstart; n <= nend; n++) {
                    for (long p = pstart; p <= pend; p++) {
                        c(m, p) += a(m, n) * b(n, p);
                    }
                }
            }
        } else if (msize >= nsize && msize >= psize) {
            long mmid = (mstart + mend) / 2;
            co_multiply(a, b, c, mstart, mmid, nstart, nend, pstart, pend);
            co_multiply(a, b, c, mmid+1, mend, nstart, nend, pstart, pend);
        } else if (nsize >= psize) {
            long nmid = (nstart + nend) / 2;
            co_multiply(a, b, c, mstart, mend, nstart, nmid, pstart, pend);
            co_multiply(a, b, c, mstart, mend, nmid+1, nend, pstart, pend);
        } else {
            long pmid = (pstart + pend) / 2;
            co_multiply(a, b, c, mstart, mend, nstart, nend, pstart, pmid);
            co_multiply(a, b, c, mstart, mend, nstart, nend, pmid+1, pend);
        }
    }


    template <typename T>
    void co_transpose(const Matrix2D<T>& a, Matrix2D<T>& b)
    {
        assert(a.nrow() == b.ncol() && a.ncol() == b.nrow());

        long msize = a.nrow();
        long nsize = a.ncol();

        co_transpose(a, b, 0L, msize-1, 0L, nsize-1);
    }


    /// \par References:
    /// \li Harald Prokop. Cache-Oblivious Algorithms. Masters thesis, MIT. 1999.
    /// \li M. Frigo, C. E. Leiserson, H. Prokop, and S. Ramachandran. Cache-oblivious algorithms.
    ///     In Proceedings of the 40th IEEE Symposium on Foundations of Computer Science, 1999.
    template <typename T>
    void co_transpose(const Matrix2D<T>& a, Matrix2D<T>& b,
                      long mstart, long mend, long nstart, long nend)
    {
        const long threshold = 8*1024;

        // Cache-Oblivious Matrix Transposition.
        // B_nm = A_mn'
        long msize = mend - mstart + 1;
        long nsize = nend - nstart + 1;
        if (msize*nsize*2 < threshold) {
            // Naive matrix transposition.
            for (long m = mstart; m <= mend; m++) {
                for (long n = nstart; n <= nend; n++) {
                    b(n, m) = a(m, n);
                }
            }
        } else if (msize >= nsize) {
            long mmid = (mstart + mend) / 2;
            co_transpose(a, b, mstart, mmid, nstart, nend);
            co_transpose(a, b, mmid+1, mend, nstart, nend);
        } else {
            long nmid = (nstart + nend) / 2;
            co_transpose(a, b, mstart, mend, nstart, nmid);
            co_transpose(a, b, mstart, mend, nmid+1, nend);
        }
    }
} // namespace algorithm

#endif // CACHEOBLIVIOUS_H
