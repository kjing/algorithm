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
module GenericBinaryTree

    # Generic method implementations for binary tree.

    module Rotation

    private

        def rotate_left(node)
            ynode = right(node)
            set_right(node, left(ynode))
            if left(ynode) != null_node then
                left_node = left(ynode)
                set_parent(left_node, node)
            end

            parent_node = parent(node)
            set_parent(ynode, parent_node)
            if parent_node == null_node then
                self.root = ynode
            elsif node == left(parent_node) then
                set_left(parent_node, ynode)
            else
                set_right(parent_node, ynode)
            end
            set_left(ynode, node)
            set_parent(node, ynode)
            return nil
        end


        def rotate_right(node)
            ynode = left(node)
            set_left(node, right(ynode))
            if right(ynode) != null_node then
                right_node = right(ynode)
                set_parent(right_node, node)
            end

            parent_node = parent(node)
            set_parent(ynode, parent_node)
            if parent_node == null_node then
                self.root = ynode
            elsif node == right(parent_node) then
                set_right(parent_node, ynode)
            else
                set_left(parent_node, ynode)
            end
            set_right(ynode, node)
            set_parent(node, ynode)
            return nil
        end

    end # module Rotation


    module MinMax

    public

        def min
            node = min_node(root)
            return (node != null_node) ? [key(node), value(node)] : [nil, nil]
        end


        def max
            node = max_node(root)
            return (node != null_node) ? [key(node), value(node)] : [nil, nil]
        end

    private

        def min_node(node)
            while left(node) != null_node
                node = left(node)
            end
            return node
        end


        def max_node(node)
            while right(node) != null_node
                node = right(node)
            end
            return node
        end

    end # module MinMax


    module Successor

    private

        def successor(node)
            if right(node) != null_node then
                return min_node(right(node))
            end

            snode = parent(node)
            while snode != null_node && node == right(snode)
                node = snode
                snode = parent(snode)
            end

            return snode
        end

    end # module Successor


    module Insert

    public

        def insert(kv)
            kv = KeyOnly.new(kv) if not kv.kind_of?(KeyValueInterface)

            parent_node = null_node
            node = root
            k = kv.key
            while node != null_node
                parent_node = node
                if k < key(node) then
                    node = left(node)
                else
                    node = right(node)
                end
            end

            if parent_node == null_node then
                self.root = create_node(kv, null_node)
            elsif k < key(parent_node) then
                set_left(parent_node, create_node(kv, parent_node))
            else
                set_right(parent_node, create_node(kv, parent_node))
            end
            return true
        end

    end # module Insert


    module Remove
        include Successor

    public

        def remove(k)
            k = k.key if k.kind_of?(KeyValueInterface)

            node = search_node(k)
            if node != null_node then
                result = remove_node(node)
                result or raise "Removal of node fails?"
                return true
            end
            return false
        end

    private

        def remove_node(node)
            if left(node) == null_node || right(node) == null_node then
                ynode = node
            else
                ynode = successor(node)
            end

            if left(ynode) != null_node then
                xnode = left(ynode)
            else
                xnode = right(ynode)
            end

            if xnode != null_node then
                set_parent(xnode, parent(ynode))
            end

            if parent(ynode) == null_node then
                self.root = xnode
            else
                if ynode == left(parent(ynode)) then
                    set_left(parent(ynode), xnode)
                else
                    set_right(parent(ynode), xnode)
                end
            end

            if ynode != node then
                set_key_value(node, key_value(ynode))
            end

            return (ynode != null_node) ? true : false
        end

    end # module Remove


    module Search

    public

        def search(k)
            k = k.key if k.kind_of?(KeyValueInterface)

            node = search_node(k)
            return (node != null_node) ? value(node) : nil
        end

    private

        def search_node(k)
            node = root
            while node != null_node && k != key(node)
                if k < key(node) then
                    node = left(node)
                else
                    node = right(node)
                end
            end
            return node
        end

    end # module Search

end # module GenericBinaryTree
end # module Tree
end # module Algorithm
