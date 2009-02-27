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


require 'tree/interface/heap'


module Algorithm
module Tree

    module HeapInternal; end


    # Generic min heap implementation.
    class MinHeap
        include MinHeapInterface
        include HeapInternal

        def initialize(kv_list = [], copy = true)
            copy ? build(kv_list) : build!(kv_list)
        end

    public

        def insert(kv)
            @node_list.push(nil)
            decrease_key(size-1, kv)
            return self
        end


        def extract_min
            size > 0 or raise "Heap underflow!"

            m = @node_list[0]
            @node_list[0] = @node_list.last
            @node_list.pop
            heapify(0)
            return m
        end

        def min;        return @node_list[0];       end

    private

        def heapify(nid)
            lid = left(nid)
            rid = right(nid)
            smallest_id = (lid < size && key_value(lid) < key_value(nid)) ? lid : nid
            if rid < size && key_value(rid) < key_value(smallest_id) then
                smallest_id = rid
            end
            if smallest_id != nid then
                swap_key_value(nid, smallest_id)
                heapify(smallest_id)
            end
            return nil
        end


        def decrease_key(nid, kv)
            x = key_value(nid)
            x.nil? || kv <= x or raise "New key is larger than current key."

            set_key_value(nid, kv)
            pid = parent(nid)
            while nid > 0 && key_value(pid) > key_value(nid)
                swap_key_value(nid, pid)
                nid = pid
                pid = parent(nid)
            end
            return nil
        end

    end # class MinHeap


    # Generic max heap implementation.
    class MaxHeap
        include MaxHeapInterface
        include HeapInternal

        def initialize(kv_list = [], copy = true)
            copy ? build(kv_list) : build!(kv_list)
        end

    public

        def insert(kv)
            @node_list.push(nil)
            increase_key(size-1, kv)
            return self
        end


        def extract_max
            size > 0 or raise "Heap underflow!"

            m = @node_list[0]
            @node_list[0] = @node_list.last
            @node_list.pop
            heapify(0)
            return m
        end


        def max;        return @node_list[0];       end

    private

        def heapify(nid)
            lid = left(nid)
            rid = right(nid)
            largest_id = (lid < size && key_value(lid) > key_value(nid)) ? lid : nid
            if rid < size && key_value(rid) > key_value(largest_id) then
                largest_id = rid
            end
            if largest_id != nid then
                swap_key_value(nid, largest_id)
                heapify(largest_id)
            end
            return nil
        end


        def increase_key(nid, kv)
            x = key_value(nid)
            x.nil? || kv >= x or raise "New key is smaller than current key."

            set_key_value(nid, kv)
            pid = parent(nid)
            while nid > 0 && key_value(pid) < key_value(nid)
                swap_key_value(nid, pid)
                nid = pid
                pid = parent(nid)
            end
            return nil
        end

    end # class MaxHeap


    module HeapInternal

    public

        def clear
            @node_list = []
            return self
        end

        def size;       return @node_list.size;     end

    private

        def key_value(nid);    return @node_list[nid];      end
        def parent(nid);       return (nid+1)/2-1;          end
        def left(nid);         return (nid+1)*2-1;          end
        def right(nid);        return (nid+1)*2;            end


        def set_key_value(nid, kv)
            @node_list[nid] = kv
            return nil
        end


        def build(kv_list)
            @node_list = kv_list.dup
            build_heapify
            return self
        end


        def build!(kv_list)
            @node_list = kv_list
            build_heapify
            return self
        end


        def build_heapify
            (size/2-1).downto(0) do |i|
                heapify(i)
            end
            return nil
        end


        def swap_key_value(xid, yid)
            kv = key_value(xid)
            set_key_value(xid, key_value(yid))
            set_key_value(yid, kv)
            return nil
        end

    end # module HeapInternal

end # module Tree
end # module Algorithm
