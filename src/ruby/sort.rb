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

    module InsertionSortInternal; end
    module MergeSortInternal; end


    def assert_sorted(list, first = 0, last = list.length-1)
        for i in first..last-1
            list[i] <= list[i+1] or raise "Assert sorted failed!"
        end
        return true
    end


    def insertion_sort(list, first = 0, last = list.length-1)
        include InsertionSortInternal

        for i in first..last
            current = list[i]
            xloc = shift_vacant(list, i, current, first)
            list[xloc] = current
        end

        assert_sorted(list, first, last) if $DEBUG
        return nil
    end


    def merge_sort(list, first = 0, last = list.length-1)
        include MergeSortInternal

        if first < last then
            mid = (first + last) / 2
            merge_sort(list, first, mid)
            merge_sort(list, mid+1, last)
            merge(list, first, mid, last)
        end

        assert_sorted(list, first, last) if $DEBUG
        return nil
    end


    def quick_sort(list, first = 0, last = list.length-1)
        # Select a pivot.
        mid = (first + last + 1) / 2
        pivot = list[mid]

        # Swap the pivot with the first element.
        list[mid], list[first] = list[first], pivot

        # Partition into [<= pivot] and [> pivot].
        i = first + 1
        k = last + 1
        while i < k
            if list[i] <= pivot then
                i += 1
            else
                k -= 1
                list[i], list[k] = list[k], list[i]
            end
        end
        list[first] = list[k-1]
        list[k-1] = pivot

        # Recursively sort the two partitions.
        if first < k-2 then
            quick_sort(list, first, k-2)
        end
        if k < last then
            quick_sort(list, k, last)
        end

        assert_sorted(list, first, last) if $DEBUG
        return nil
    end


    module_function :insertion_sort
    module_function :merge_sort
    module_function :quick_sort

end # module Algorithm


######################################################################
# Internal
######################################################################

module Algorithm

    module InsertionSortInternal

        def shift_vacant(list, xindex, x, first = 0)
            vacant = xindex
            xloc = first
            while vacant > first
                if list[vacant-1] <= x then
                    xloc = vacant
                    break
                end
                list[vacant] = list[vacant-1]
                vacant -= 1
            end
            return xloc
        end

    end


    module MergeSortInternal

        def merge(list, first, mid, last)
            n = last - first + 1
            k = mid - first + 1
            m = n - k
            ia = ib = ic = 0
            sa = first
            sb = mid + 1
            c = []

            while ia < k && ib < m
                if list[sa + ia] <= list[sb + ib] then
                    c[ic] = list[sa + ia]
                    ia += 1
                    ic += 1
                else
                    c[ic] = list[sb + ib]
                    ib += 1
                    ic += 1
                end
            end
            if ia >= k then
                for i in 0...n-ic
                    c[ic + i] = list[sb + ib + i]
                end
            else
                for i in 0...n-ic
                    c[ic + i] = list[sa + ia + i]
                end
            end

            for i in 0...n
                list[first + i] = c[i]
            end

            return nil
        end

    end

end # module Algorithm
