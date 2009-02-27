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
module Tree

    module MinHeapInterface
        def insert(kv);                 raise NotImplementedError; end
        def extract_min;                raise NotImplementedError; end
        def clear;                      raise NotImplementedError; end
        def min;                        raise NotImplementedError; end
        def size;                       raise NotImplementedError; end

    private
        def key_value(node);            raise NotImplementedError; end
        def parent(node);               raise NotImplementedError; end
        def left(node);                 raise NotImplementedError; end
        def right(node);                raise NotImplementedError; end
        def set_key_value(node, kv);    raise NotImplementedError; end
        def build(kv_list);             raise NotImplementedError; end
        def build!(kv_list);            raise NotImplementedError; end
    end


    module MaxHeapInterface
        def insert(kv);                 raise NotImplementedError; end
        def extract_max;                raise NotImplementedError; end
        def clear;                      raise NotImplementedError; end
        def max;                        raise NotImplementedError; end
        def size;                       raise NotImplementedError; end

    private
        def key_value(node);            raise NotImplementedError; end
        def parent(node);               raise NotImplementedError; end
        def left(node);                 raise NotImplementedError; end
        def right(node);                raise NotImplementedError; end
        def set_key_value(node, kv);    raise NotImplementedError; end
        def build(kv_list);             raise NotImplementedError; end
        def build!(kv_list);            raise NotImplementedError; end
    end

end # module Tree
end # module Algorithm
