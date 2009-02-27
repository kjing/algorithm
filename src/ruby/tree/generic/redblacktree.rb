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


require 'tree/generic/binarytree'


module Algorithm
module Tree
module GenericRedBlackTree

    # Generic method implementations for red-black tree.

    module Rotation
        include GenericBinaryTree::Rotation
    end

    module MinMax
        include GenericBinaryTree::MinMax
    end

    module Successor
        include GenericBinaryTree::Successor
    end


    module Insert

    public

        def insert(kv)
            parent_node = null_node
            node = root
            while node != null_node
                parent_node = node
                node = (kv < key_value(node)) ? left(node) : right(node)
            end

            if parent_node == null_node then
                znode = create_red_node(kv, parent_node, null_node, null_node)
                self.root = znode
            elsif kv < key_value(parent_node) then
                znode = create_red_node(kv, parent_node, null_node, null_node)
                set_left(parent_node, znode)
            else
                znode = create_red_node(kv, parent_node, null_node, null_node)
                set_right(parent_node, znode)
            end
            fixup_insert(znode)

            return true
        end

    private

        def fixup_insert(node)
            parent_node = parent(node)
            while red?(parent_node)
                pparent_node = parent(parent_node)
                if parent_node == left(pparent_node) then
                    unode = right(pparent_node)
                    if red?(unode) then
                        set_black(parent_node)
                        set_black(unode)
                        set_red(pparent_node)
                        node = pparent_node
                        parent_node = parent(node)
                    else
                        if node == right(parent_node) then
                            node = parent_node
                            rotate_left(node)
                            parent_node = parent(node)
                        end
                        pparent_node = parent(parent_node)
                        set_black(parent_node)
                        set_red(pparent_node)
                        rotate_right(pparent_node)
                    end
                else
                    unode = left(pparent_node)
                    if red?(unode) then
                        set_black(parent_node)
                        set_black(unode)
                        set_red(pparent_node)
                        node = pparent_node
                        parent_node = parent(node)
                    else
                        if node == left(parent_node) then
                            node = parent_node
                            rotate_right(node)
                            parent_node = parent(node)
                        end
                        pparent_node = parent(parent_node)
                        set_black(parent_node)
                        set_red(pparent_node)
                        rotate_left(pparent_node)
                    end
                end
            end
            set_black(root)
            return nil
        end

    end # module Insert


    module Remove
        include Successor

    public

        def remove(kv)
            node = search_node(kv)
            if node != null_node then
                result = remove_node(node)
                result or raise "Removal of node fails?"
                return true
            end
            return false
        end

    private

        def remove_node(node)
            ynode = (left(node) == null_node || right(node) == null_node) ? node : successor(node)
            xnode = (left(ynode) != null_node) ? left(ynode) : right(ynode)

            if xnode != null_node then
                set_parent(xnode, parent(ynode))
            end

            set_parent(xnode, parent(ynode))

            if parent(ynode) == null_node then
                self.root = xnode
            else
                pnode = parent(ynode)
                if ynode == left(pnode) then
                    set_left(pnode, xnode)
                else
                    set_right(pnode, xnode)
                end
            end

            if ynode != node then
                set_key_value(node, ynode)
            end

            if black?(ynode) then
                fixup_remove(xnode)
            end

            return (ynode != null_node) ? true : false
        end


        def fixup_remove(node)
            while node != root && black?(node)
                pnode = parent(node)
                if node == left(pnode) then
                    wnode = right(pnode)
                    if red?(wnode) then
                        set_black(wnode)
                        set_red(pnode)
                        rotate_left(pnode)
                        pnode = parent(node)
                        wnode = right(pnode)
                    end
                    lnode = left(wnode)
                    rnode = right(wnode)
                    if black?(lnode) && black?(rnode) then
                        set_red(wnode)
                        node = parent(node)
                    else
                        if black?(rnode) then
                            set_black(lnode)
                            set_red(wnode)
                            rotate_right(wnode)
                            pnode = parent(node)
                            wnode = right(pnode)
                            rnode = right(wnode)
                        end
                        set_color(wnode, color(pnode))
                        set_black(pnode)
                        set_black(rnode)
                        rotate_left(pnode)
                        node = root
                    end
                else
                    wnode = left(pnode)
                    if red?(wnode) then
                        set_black(wnode)
                        set_red(pnode)
                        rotate_right(pnode)
                        pnode = parent(node)
                        wnode = left(pnode)
                    end
                    lnode = left(wnode)
                    rnode = right(wnode)
                    if black?(lnode) && black?(rnode) then
                        set_red(wnode)
                        node = parent(node)
                    else
                        if black?(lnode) then
                            set_black(rnode)
                            set_red(wnode)
                            rotate_left(wnode)
                            pnode = parent(node)
                            wnode = left(pnode)
                            lnode = left(wnode)
                        end
                        set_color(wnode, color(pnode))
                        set_black(pnode)
                        set_black(lnode)
                        rotate_right(pnode)
                        node = root
                    end
                end
            end
            set_black(node)
            return nil
        end

    end # module Remove


    module Search
        include GenericBinaryTree::Search
    end

end # module GenericRedBlackTree
end # module Tree
end # module Algorithm
