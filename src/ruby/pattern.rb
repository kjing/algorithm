#---------------------------------------------------------------------
#
# Copyright (c) 2009 Chung Shin Yee <cshinyee@gmail.com>
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
#---------------------------------------------------------------------


module Algorithm

    def lcs_length(listx, listy,
                   firstx = 0, lastx = listx.length-1,
                   firsty = 0, lasty = listy.length-1)

        lx = lastx - firstx + 1
        ly = lasty - firsty + 1

        if lx == 0 || ly == 0 then
            return 0
        end

        z = Array.new(ly+1, 0)

        for i in 0...lx
            # k = 0, z[0] == 0
            next_zik = z[1]
            if listx[firstx + i] == listy[firsty] then
                z[1] = 1
            end
            zik = next_zik

            for k in 1...ly
                next_zik = z[k+1]
                if listx[firstx + i] == listy[firsty + k] then
                    z[k+1] = zik + 1
                elsif z[k] >= z[k+1] then
                    z[k+1] = z[k]
                end
                zik = next_zik
            end
        end

        length = z[ly]
        return length
    end


    module_function :lcs_length

end # module Algorithm
