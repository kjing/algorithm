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

#ifndef WALLTIME_H
#define WALLTIME_H

#include <sys/times.h>
#include <unistd.h>

namespace algorithm
{
    typedef clock_t WallTime;

    /// Get the current wall clock time.
    /// \return The amount of wall clock time that have elapsed since
    ///         an arbitrary point in the past.
    WallTime get_wall_time(void);

    /// Get the elapsed wall clock time elapsed between <b>t1</b> and <b>t2</b>.
    /// \param t1 The start time.
    /// \param t2 The stop time.
    /// \return The number of seconds between <b>t1</b> and <b>t2</b>.
    double elapsed(WallTime t1, WallTime t2);
} // namespace algorithm


// ===================================================================
// Implementation
// ===================================================================

namespace algorithm
{
    inline WallTime get_wall_time(void)
    {
        struct tms buf;
        return times(&buf);
    }


    inline double elapsed(WallTime t1, WallTime t2)
    {
        long nticks = sysconf(_SC_CLK_TCK); // Number of clock ticks per second.
        return static_cast<double>(t2 - t1) / nticks;
    }
} // namespace algorithm

#endif // WALLTIME_H

