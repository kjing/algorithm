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


require 'forwardable'
require 'tree/keyvalue'
require 'tree/interface/binarytree'
require 'tree/generic/binarytree'


module Algorithm
module Tree

    # Generic binary tree node implementation.
    class BinaryTreeNode
        include BinaryTreeNodeInterface
        extend Forwardable

        def initialize(kv, pnode, lnode = nil, rnode = nil)
            @key_value = kv
            @parent = pnode
            @left = lnode
            @right = rnode
        end

        def_delegators :@key_value, :key, :value

    public
        attr_accessor :key_value, :parent, :left, :right
    end


    # Generic binary tree implementation.
    class BinaryTree
        include BinaryTreeInterface

        def initialize
            @root = nil
            @size = 0
        end

        include GenericBinaryTree::Insert
        include GenericBinaryTree::Remove
        include GenericBinaryTree::Search
        include GenericBinaryTree::MinMax

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

        def remove(k)
            result = generic_remove(k)
            @size -= 1 if result
            return self
        end

        def clear
            @root = nil
            @size = 0
            return self
        end

    private

        def root;               return @root;           end
        def root=(node);        return @root = node;    end
        def key(node);          return node.key;        end
        def value(node);        return node.value;      end
        def key_value(node);    return node.key_value;  end
        def parent(node);       return node.parent;     end
        def left(node);         return node.left;       end
        def right(node);        return node.right;      end

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

        def create_node(kv, pnode, lnode = null_node, rnode = null_node)
            return BinaryTreeNode.new(kv, pnode, lnode, rnode)
        end

        def null_node
            return nil
        end

    end # class BinaryTree


    # Array-based binary tree implementation.
    class BinaryTree_ArrayBased
        include BinaryTreeInterface

        def initialize
            @node_list = [nil]
            @root_id = 0
            @size = 0
        end

        include GenericBinaryTree::Insert
        include GenericBinaryTree::Remove
        include GenericBinaryTree::Search
        include GenericBinaryTree::MinMax

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

        def remove(k)
            result = generic_remove(k)
            @size -= 1 if result
            return self
        end

        def clear
            @node_list = [nil]
            @root_id = 0
            @size = 0
            return self
        end

    private

        def root;               return @root_id;                    end
        def root=(nid);         return @root_id = nid;              end
        def key(nid);           return @node_list[nid].key;         end
        def value(nid);         return @node_list[nid].value;       end
        def key_value(nid);     return @node_list[nid].key_value;   end
        def parent(nid);        return @node_list[nid].parent;      end
        def left(nid);          return @node_list[nid].left;        end
        def right(nid);         return @node_list[nid].right;       end

        def set_key_value(nid, kv)
            @node_list[nid].key_value = kv
            return nil
        end

        def set_parent(nid, pid)
            @node_list[nid].parent = pid
            return nil
        end

        def set_left(nid, lid)
            @node_list[nid].left = lid
            return nil
        end

        def set_right(nid, rid)
            @node_list[nid].right = rid
            return nil
        end

        def create_node(kv, pid, lid = null_node, rid = null_node)
            @node_list.push(BinaryTreeNode.new(kv, pid, lid, rid))
            return @node_list.length-1
        end

        def null_node
            return 0
        end

    end # class BinaryTree_ArrayBased

end # module Tree
end # module Algorithm
