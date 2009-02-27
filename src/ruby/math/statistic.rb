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


require 'math/number'


module Algorithm
module Math

    def find_minmax(list)
        return list.min, list.max
    end


    def find_minmax_Simple(list)
        if list.length <= 0 then
            return nil, nil
        elsif list.length == 1 then
            return list[0], list[0]
        end

        min = list[0]
        max = list[0]
        for i in 1...list.length
            min = list[i] if list[i] < min
            max = list[i] if list[i] > max
        end
        return min, max
    end


    def find_minmax_Simultaneous(list)
        if list.length <= 2 then
            return find_minmax_Simple(list)
        end

        length = list.length
        even_length = (even?(length)) ? length : length-1

        min = list[0]
        max = list[1]
        (0...even_length).step(2) do |i|
            k = i + 1
            if list[i] <= list[k] then
                smaller = list[i]
                larger = list[k]
            else
                smaller = list[k]
                larger = list[i]
            end

            min = smaller if smaller < min
            max = larger if larger > max
        end

        if even_length != length then
            min = list[length-1] if list[length-1] < min
            max = list[length-1] if list[length-1] > max
        end
        return min, max
    end


    def randomized_partition!(list, first, last)
        list.length > 0 or raise "List is empty?"
        size = last - first + 1
        p = first + rand(size)
        pivot = list[p]
        list[first], list[p] = list[p], list[first]
        h = first + 1
        t = last + 1
        while h < t
            if list[h] <= pivot then
                h += 1
            else
                t -= 1
                list[h], list[t] = list[t], list[h]
            end
        end
        list[first] = list[t-1]
        list[t-1] = pivot
        return t-1
    end


    module_function :find_minmax
    module_function :find_minmax_Simple
    module_function :find_minmax_Simultaneous
    module_function :randomized_partition!

end # module Math
end # module Algorithm
