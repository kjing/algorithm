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


require 'tree/interface/binarytree'


module Algorithm
module Tree

    module RedBlackTreeNodeInterface
        include BinaryTreeNodeInterface
        RED = 0
        BLACK = 1
        def color;              raise NotImplementedError; end
        def red?;               raise NotImplementedError; end
        def black?;             raise NotImplementedError; end
        def set_color(col);     raise NotImplementedError; end
        def set_red;            raise NotImplementedError; end
        def set_black;          raise NotImplementedError; end
    end


    module RedBlackTreeInterface
        include BinaryTreeInterface

    private
        def create_node(kv, col, pnode, lnode = nil, rnode = nil);      raise NotImplementedError; end
        def create_red_node(kv, pnode, lnode = nil, rnode = nil);       raise NotImplementedError; end
        def create_black_node(kv, pnode, lnode = nil, rnode = nil);     raise NotImplementedError; end

        def color(node);            raise NotImplementedError; end
        def red?(node);             raise NotImplementedError; end
        def black?(node);           raise NotImplementedError; end
        def set_color(node, col);   raise NotImplementedError; end
        def set_red(node);          raise NotImplementedError; end
        def set_black(node);        raise NotImplementedError; end
    end

end # module Tree
end # module Algorithm
