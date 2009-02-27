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


require 'tree/binarytree'
require 'tree/interface/redblacktree'
require 'tree/generic/redblacktree'


module Algorithm
module Tree

    # Generic red-black tree node implementation.
    class RedBlackTreeNode < BinaryTreeNode
        include RedBlackTreeNodeInterface

        def initialize(kv, col, pnode, lnode = nil, rnode = nil)
            super(kv, pnode, lnode, rnode)
            col == RED || col == BLACK or raise "Expect only RED or BLACK color."
            @color = col
        end

        def red?
            return @color == RED
        end

        def black?
            return @color == BLACK
        end

        def set_color(col)
            col == RED || col == BLACK or raise "Expect only RED or BLACK color."
            @color = col
            return nil
        end

        def set_red
            @color = RED
            return nil
        end

        def set_black
            @color = BLACK
            return nil
        end

    public
        attr_reader :color
    end


    # Generic red-black tree implementation.
    class RedBlackTree
        include RedBlackTreeInterface

        def initialize
            @empty_node = create_black_node(nil, nil, nil, nil)
            @empty_node.parent = @empty_node
            @empty_node.left = @empty_node
            @empty_node.right = @empty_node
            @root = @empty_node
            @size = 0
        end

        include GenericRedBlackTree::Insert
        include GenericRedBlackTree::Remove
        include GenericRedBlackTree::Search
        include GenericRedBlackTree::MinMax
        include GenericRedBlackTree::Rotation

    private

        alias generic_insert insert
        alias generic_remove remove

    public

        attr_reader :size

        def insert(kv)
            generic_insert(kv)
            @size += 1
            return self
        end

        def remove(kv)
            result = generic_remove(kv)
            @size -= 1 if result
            return self
        end

        def clear
            @root = @empty_node
            @size = 0
            return self
        end

    private

        def root;               return @root;           end
        def root=(node);        return @root = node;    end
        def key_value(node);    return node.key_value   end
        def parent(node);       return node.parent;     end
        def left(node);         return node.left;       end
        def right(node);        return node.right;      end
        def color(node);        return node.color;      end
        def red?(node);         return node.red?;       end
        def black?(node);       return node.black?;     end

        def set_key_value(node, kv)
            node.key_value = kv
            return nil
        end

        def set_parent(node, pnode)
            node.parent = pnode
            return nil
        end

        def set_left(node, lnode)
            node.left = lnode
            return nil
        end

        def set_right(node, rnode)
            node.right = rnode
            return nil
        end

        def set_color(node, col)
            node.set_color(col)
            return nil
        end

        def set_red(node)
            node.set_red
            return nil
        end

        def set_black(node)
            node.set_black
            return nil
        end

        def create_node(kv, col, pnode, lnode = null_node, rnode = null_node)
            return RedBlackTreeNode.new(kv, col, pnode, lnode, rnode)
        end

        def create_red_node(kv, pnode, lnode = null_node, rnode = null_node)
            return create_node(kv, RedBlackTreeNodeInterface::RED, pnode, lnode, rnode)
        end

        def create_black_node(kv, pnode, lnode = null_node, rnode = null_node)
            return create_node(kv, RedBlackTreeNodeInterface::BLACK, pnode, lnode, rnode)
        end

        def null_node
            return @empty_node
        end

    end # class RedBlackTree

end # module Tree
end # module Algorithm
