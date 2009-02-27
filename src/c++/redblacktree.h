/*
# Copyright (c) 2008 Chung Shin Yee <cshinyee@gmail.com>
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
*/

#ifndef REDBLACKTREE_H
#define REDBLACKTREE_H

#include <cassert>
#include <vector>

namespace algorithm
{
    template <typename Key, typename Value>
    class RedBlackTree
    {
    public:
        RedBlackTree(void);
        ~RedBlackTree(void);

        /// \brief Get the number of elements in the tree.
        /// \return The number of elements in the tree.
        long size(void) const;

        /// \brief Search for the element with <b>key</b> in the tree.
        /// \param[in] key The key of the element to search for.
        /// \return The pointer to the element with <b>key</b> if found, NULL otherwise.
        const Value* search(const Key& key) const;

        /// \brief Insert the (<b>key</b>,<b>value</b>) pair if elements with <b>key</b>
        ///        do not exist in the tree, do nothing otherwise.
        /// \param[in] key The key of the element to insert.
        /// \param[in] value The value of the element to insert.
        /// \return true if an element with <b>key</b> is inserted, false otherwise.
        bool insert(const Key& key, const Value& value);

        /// \brief Remove the element with <b>key</b> in the tree.
        /// \param[in] key The key of the element to remove.
        /// \return true if an element with <b>key</b> is removed, false otherwise.
        bool remove(const Key& key);

    private:
        /// \brief The types of colors of a node.
        typedef enum {
            RED = 0,
            BLACK = 1,
        } Color;

        /// \brief The data type of the tree node.
        typedef struct {
            long parent; ///< The index of the parent node.
            long left; ///< The index of the left child node.
            long right; ///< The index of the right child node.
            Color color; ///< The color of this node.
            Key key; ///< The key of the element associated.
            Value value; ///< The value of the element associated.
        } Node;
        typedef std::vector<Node> NodeList;

        /// \brief Search for the node or element with <b>key</b> in the tree.
        /// \param[in] key The key of the node or element to search for.
        /// \return The index of the node or element with <b>key</b> if found, <b>m_nil</b> otherwise.
        long search_node(const Key& key) const;

        /// \brief Fix up the Red-Black tree properties after an insertion.
        /// \param[in] nid The index of the root node of the sub-tree to fix up.
        void fixup_insert(long nid);

        /// \brief Remove the node with index <b>nid</b>.
        /// \param[in] nid The index of the node to remove.
        void remove_node(long nid);

        /// \brief Fix up the Red-Black tree properties after a removal.
        /// \param[in] nid The index of the root node of the sub-tree to fix up.
        void fixup_remove(long nid);

        /// \brief Get a free node.
        /// \return The index of a free node.
        long create_node(void);

        /// \brief Get and initialize a free node.
        /// \param[in] parent The index of the parent node.
        /// \param[in] left The index of the left child node.
        /// \param[in] right The index of the right child node.
        /// \param[in] color The color of this node, either RED or BLACK.
        /// \param[in] key The key of the element associated to this node.
        /// \param[in] value The value of the element associated to this node.
        /// \return The index of a free node.
        long create_node(long parent, long left, long right, Color color,
                         const Key& key, const Value& value);

        /// \brief Return the node <b>nid</b> to the free-node list.
        /// \param[in] nid The index of the node to return.
        void recycle_node(long nid);

        /// \brief Find the node with minimum value in the sub-tree rooted at node <b>nid</b>.
        /// \param[in] nid The index of the root node of the sub-tree.
        /// \return The index of the node with minimum value.
        long min(long nid) const;

        /// \brief Find the node with maximum value in the sub-tree rooted at node <b>nid</b>.
        /// \param[in] nid The index of the root node of the sub-tree.
        /// \return The index of the node with maximum value.
        long max(long nid) const;

        /// \brief Find the successor of the node <b>nid</b>.
        /// \param[in] nid The index of the predecessor node.
        /// \return The index of the successor node.
        long successor(long nid) const;

        /// \brief Rotate the node left.
        /// \param[in] nid The index of the node to rotate.
        void rotate_left(long nid);

        /// \brief Rotate the node right.
        /// \param[in] nid The index of the node to rotate.
        void rotate_right(long nid);

        /// \brief Perform consistency check on the tree.
        /// \return true if the tree is consistent, false otherwise.
        bool is_consistent(void) const;

        /// \brief Perform consistency check on the sub-tree rooted at node <b>nid</b>.
        /// \param[in] nid The index of the root node of the sub-tree.
        /// \return true if the sub-tree rooted at node <b>nid</b> is consistent, false otherwise.
        bool is_consistent(long nid) const;

        static const long m_block_size; ///< The number of nodes in a block.
        long m_root; ///< The index of the root node.
        long m_free_head; ///< The index of the head node of the free-node list.
        long m_size; ///< The number of elements in this tree.
        long m_nil; ///< The index of the sentinel node that represents nil node.
        NodeList m_nodes; ///< The list of all nodes.
    };
} // namespace algorithm


// ===================================================================
// Implementation
// ===================================================================

namespace algorithm
{
    template <typename Key, typename Value>
    const long RedBlackTree<Key, Value>::m_block_size = 256;


    template <typename Key, typename Value>
    RedBlackTree<Key, Value>::RedBlackTree(void) : m_root(-1), m_free_head(-1), m_size(0), m_nodes()
    {
        m_nil = create_node();
        m_nodes[m_nil].parent = m_nil;
        m_nodes[m_nil].left = m_nil;
        m_nodes[m_nil].right = m_nil;
        m_nodes[m_nil].color = BLACK;

        m_root = m_nil;
    }


    template <typename Key, typename Value>
    RedBlackTree<Key, Value>::~RedBlackTree(void)
    {
    }


    template <typename Key, typename Value>
    long RedBlackTree<Key, Value>::size(void) const
    {
        return m_size;
    }


    template <typename Key, typename Value>
    const Value* RedBlackTree<Key, Value>::search(const Key& key) const
    {
        long nid = search_node(key);
        if (nid != m_nil) {
            return &m_nodes[nid].value;
        }
        return NULL;
    }


    /// \par References:
    /// Introduction to Algorithms - T. H. Cormen, C. E. Leiserson, R. L. Rivest & C. Stein
    template <typename Key, typename Value>
    long RedBlackTree<Key, Value>::search_node(const Key& key) const
    {
        long nid = m_root;

        while (nid != m_nil && key != m_nodes[nid].key) {
            if (key < m_nodes[nid].key) {
                nid = m_nodes[nid].left;
            } else {
                nid = m_nodes[nid].right;
            }
        }
        return nid;
    }


    /// \par References:
    /// Introduction to Algorithms - T. H. Cormen, C. E. Leiserson, R. L. Rivest & C. Stein
    template <typename Key, typename Value>
    bool RedBlackTree<Key, Value>::insert(const Key& key, const Value& value)
    {
        long pid = m_nil; // Parent node index.
        long nid = m_root; // Node index.
        long zid; // New node index.

        // Get the right node, pid, to insert.
        while (nid != m_nil) {
            pid = nid;
            if (key == m_nodes[nid].key) {
                return false;
            } else if (key < m_nodes[nid].key) {
                nid = m_nodes[nid].left;
            } else {
                nid = m_nodes[nid].right;
            }
        }

        if (pid == m_nil) { // The tree is empty.
            zid = m_root = create_node(m_nil, m_nil, m_nil, RED, key, value);
        } else if (key < m_nodes[pid].key) {
            zid = create_node(pid, m_nil, m_nil, RED, key, value);
            m_nodes[pid].left = zid;
        } else {
            zid = create_node(pid, m_nil, m_nil, RED, key, value);
            m_nodes[pid].right = zid;
        }
        fixup_insert(zid);
        ++m_size;

        return true;
    }


    /// \par References:
    /// Introduction to Algorithms - T. H. Cormen, C. E. Leiserson, R. L. Rivest & C. Stein
    template <typename Key, typename Value>
    void RedBlackTree<Key, Value>::fixup_insert(long nid)
    {
        long pid = m_nodes[nid].parent;
        while (m_nodes[pid].color == RED) {
            long ppid = m_nodes[pid].parent;
            if (pid == m_nodes[ppid].left) {
                long uid = m_nodes[ppid].right; // The index of the uncle of node nid.
                if (m_nodes[uid].color == RED) {
                    m_nodes[pid].color = BLACK;
                    m_nodes[uid].color = BLACK;
                    m_nodes[ppid].color = RED;
                    nid = ppid;
                    pid = m_nodes[nid].parent;
                } else {
                    if (nid == m_nodes[pid].right) {
                        nid = pid;
                        rotate_left(nid);
                        pid = m_nodes[nid].parent;
                    }
                    ppid = m_nodes[pid].parent;
                    m_nodes[pid].color = BLACK;
                    m_nodes[ppid].color = RED;
                    rotate_right(ppid);
                }
            } else { // Symmetric, with "left" & "right" exchanged.
                long uid = m_nodes[ppid].left; // The index of the uncle of node nid.
                if (m_nodes[uid].color == RED) {
                    m_nodes[pid].color = BLACK;
                    m_nodes[uid].color = BLACK;
                    m_nodes[ppid].color = RED;
                    nid = ppid;
                    pid = m_nodes[nid].parent;
                } else {
                    if (nid == m_nodes[pid].left) {
                        nid = pid;
                        rotate_right(nid);
                        pid = m_nodes[nid].parent;
                    }
                    ppid = m_nodes[pid].parent;
                    m_nodes[pid].color = BLACK;
                    m_nodes[ppid].color = RED;
                    rotate_left(ppid);
                }
            }
        }
        m_nodes[m_root].color = BLACK;
    }


    template <typename Key, typename Value>
    bool RedBlackTree<Key, Value>::remove(const Key& key)
    {
        long nid = search_node(key);
        if (nid != m_nil) {
            remove_node(nid);
            return true;
        }
        return false;
    }


    /// \par References:
    /// Introduction to Algorithms - T. H. Cormen, C. E. Leiserson, R. L. Rivest & C. Stein
    template <typename Key, typename Value>
    void RedBlackTree<Key, Value>::remove_node(long nid)
    {
        assert(nid != m_nil);

        long xid, yid;
        if (m_nodes[nid].left == m_nil || m_nodes[nid].right == m_nil) {
            yid = nid;
        } else {
            yid = successor(nid);
        }

        if (m_nodes[yid].left != m_nil) {
            xid = m_nodes[yid].left;
        } else {
            xid = m_nodes[yid].right;
        }

        m_nodes[xid].parent = m_nodes[yid].parent;

        if (m_nodes[yid].parent == m_nil) {
            m_root = xid;
        } else {
            long pid = m_nodes[yid].parent;
            if (yid == m_nodes[pid].left) {
                m_nodes[pid].left = xid;
            } else {
                m_nodes[pid].right = xid;
            }
        }

        if (yid != nid) {
            m_nodes[nid].key = m_nodes[yid].key;
            m_nodes[nid].value = m_nodes[yid].value;
        }

        if (m_nodes[yid].color == BLACK) {
            fixup_remove(xid);
        }

        if (yid != m_nil) {
            --m_size;
            recycle_node(yid);
        }
    }


    /// \par References:
    /// Introduction to Algorithms - T. H. Cormen, C. E. Leiserson, R. L. Rivest & C. Stein
    template <typename Key, typename Value>
    void RedBlackTree<Key, Value>::fixup_remove(long nid)
    {
        long pid;
        long wid;

        while (nid != m_root && m_nodes[nid].color == BLACK) {
            pid = m_nodes[nid].parent;
            if (nid == m_nodes[pid].left) {
                wid = m_nodes[pid].right;
                if (m_nodes[wid].color == RED) {
                    m_nodes[wid].color = BLACK;
                    m_nodes[pid].color = RED;
                    rotate_left(pid);
                    pid = m_nodes[nid].parent;
                    wid = m_nodes[pid].right;
                }
                long lid = m_nodes[wid].left; // Left ID.
                long rid = m_nodes[wid].right; // Right ID.
                if (m_nodes[lid].color == BLACK && m_nodes[rid].color == BLACK) {
                    m_nodes[wid].color = RED;
                    nid = m_nodes[nid].parent;
                } else {
                    if (m_nodes[rid].color == BLACK) {
                        m_nodes[lid].color = BLACK;
                        m_nodes[wid].color = RED;
                        rotate_right(wid);
                        pid = m_nodes[nid].parent;
                        wid = m_nodes[pid].right;
                        // lid = m_nodes[wid].left; // Not use.
                        rid = m_nodes[wid].right;
                    }
                    m_nodes[wid].color = m_nodes[pid].color;
                    m_nodes[pid].color = BLACK;
                    m_nodes[rid].color = BLACK;
                    rotate_left(pid);
                    nid = m_root;
                }
            } else { // Symmetric, with "left" and "right" exchanged.
                wid = m_nodes[pid].left;
                if (m_nodes[wid].color == RED) {
                    m_nodes[wid].color = BLACK;
                    m_nodes[pid].color = RED;
                    rotate_right(m_nodes[nid].parent);
                    pid = m_nodes[nid].parent;
                    wid = m_nodes[pid].left;
                }
                long lid = m_nodes[wid].left;
                long rid = m_nodes[wid].right;
                if (m_nodes[lid].color == BLACK && m_nodes[rid].color == BLACK) {
                    m_nodes[wid].color = RED;
                    nid = m_nodes[nid].parent;
                } else {
                    if (m_nodes[lid].color == BLACK) {
                        m_nodes[rid].color = BLACK;
                        m_nodes[wid].color = RED;
                        rotate_left(wid);
                        pid = m_nodes[nid].parent;
                        wid = m_nodes[pid].left;
                        lid = m_nodes[wid].left;
                        // rid = m_nodes[wid].right; // Not use.
                    }
                    m_nodes[wid].color = m_nodes[pid].color;
                    m_nodes[pid].color = BLACK;
                    m_nodes[lid].color = BLACK;
                    rotate_right(pid);
                    nid = m_root;
                }
            }
        }
        m_nodes[nid].color = BLACK;
    }


    /// \warning This may re-allocate <b>m_nodes</b>, and invalidate all
    ///          references to <b>m_nodes</b>.
    template <typename Key, typename Value>
    long RedBlackTree<Key, Value>::create_node(void)
    {
        long nid; // Node index.

        if (m_free_head < 0) { // No more free nodes available.
            long size = m_nodes.size();
            m_nodes.resize(size + m_block_size);
            for (long i = size; i < size + m_block_size; ++i) {
                m_nodes[i].parent = -1;
                m_nodes[i].left = i-1;
                m_nodes[i].right = i+1;
            }
            m_nodes[size].left = -1;
            m_nodes[size + m_block_size - 1].right = -1;
            m_free_head = size;
        }
        nid = m_free_head;
        m_free_head = m_nodes[nid].right;
        if (m_free_head >= 0) {
            m_nodes[m_free_head].left = -1;
        }

        return nid;
    }


    /// \warning This may re-allocate <b>m_nodes</b>, and invalidate all
    ///          references to <b>m_nodes</b>.
    template <typename Key, typename Value>
    long RedBlackTree<Key, Value>::create_node(long parent, long left, long right, Color color,
                                               const Key& key, const Value& value)
    {
        long nid = create_node();

        m_nodes[nid].parent = parent;
        m_nodes[nid].left = left;
        m_nodes[nid].right = right;
        m_nodes[nid].color = color;
        m_nodes[nid].key = key;
        m_nodes[nid].value = value;

        return nid;
    }


    template <typename Key, typename Value>
    void RedBlackTree<Key, Value>::recycle_node(long nid)
    {
        assert(nid >= 0);

        m_nodes[nid].parent = -1;
        m_nodes[nid].left = -1;
        m_nodes[nid].right = m_free_head;
        m_free_head = nid;
        long nsize = m_nodes.size();
        if (nsize >= m_size*2 && nsize >= m_block_size*3) {
            // Reduce 1 block size.
            long rid = nsize-1; // Recycle-node ID.
            for (long i = 0; i < m_block_size; ++i, --rid) {
                // Only free nodes have parent links as -1.
                if (m_nodes[rid].parent < 0) {
                    // Remove node rid out of the free-node list.
                    if (m_nodes[rid].left >= 0) {
                        long left = m_nodes[rid].left;
                        m_nodes[left].right = m_nodes[rid].right;
                    }
                    if (m_nodes[rid].right >= 0) {
                        long right = m_nodes[rid].right;
                        m_nodes[right].left = m_nodes[rid].left;
                    }
                    m_nodes[rid].parent = -1;
                    m_nodes[rid].left = -1;
                    m_nodes[rid].right = -1;
                    continue;
                }

                long fid = m_free_head; // Free-node index.
                while (fid >= nsize - m_block_size) {
                    if (m_nodes[fid].left >= 0) {
                        long left = m_nodes[fid].left;
                        m_nodes[left].right = m_nodes[fid].right;
                    }
                    if (m_nodes[fid].right >= 0) {
                        long right = m_nodes[fid].right;
                        m_nodes[right].left = m_nodes[fid].left;
                    }
                    long next = m_nodes[fid].right;
                    m_nodes[fid].parent = -1;
                    m_nodes[fid].left = -1;
                    m_nodes[fid].right = -1;
                    fid = next;
                    // assert(fid >= 0);
                }
                if (fid < 0) continue;
                long fid_parent;
                long fid_left = m_nodes[fid].left;
                long fid_right = m_nodes[fid].right;
                assert(m_nodes[fid].parent == -1);
                if (fid_left >= 0) {
                    m_nodes[fid_left].right = m_nodes[fid].right;
                } else {
                    // Only head node has left == -1.
                    m_free_head = m_nodes[fid].right;
                }
                if (fid_right >= 0) {
                    m_nodes[fid_right].left = m_nodes[fid].left;
                }
                m_nodes[fid].parent = -1;
                m_nodes[fid].left = -1;
                m_nodes[fid].right = -1;

                m_nodes[fid] = m_nodes[rid];

                // Update neighbour nodes.
                fid_parent = m_nodes[fid].parent;
                fid_left = m_nodes[fid].left;
                fid_right = m_nodes[fid].right;
                if (fid_parent != m_nil) {
                    if (m_nodes[fid_parent].left == rid) {
                        m_nodes[fid_parent].left = fid;
                    } else {
                        assert(m_nodes[fid_parent].right == rid);
                        m_nodes[fid_parent].right = fid;
                    }
                } else {
                    m_root = fid;
                }
                if (fid_left != m_nil) {
                    assert(m_nodes[fid_left].parent == rid);
                    m_nodes[fid_left].parent = fid;
                }
                if (fid_right != m_nil) {
                    assert(m_nodes[fid_right].parent == rid);
                    m_nodes[fid_right].parent = fid;
                }
            }
            m_nodes.resize(nsize - m_block_size);
        }
    }


    template <typename Key, typename Value>
    long RedBlackTree<Key, Value>::min(long nid) const
    {
        assert(nid != m_nil);

        while (m_nodes[nid].left != m_nil) {
            nid = m_nodes[nid].left;
        }
        return nid;
    }


    template <typename Key, typename Value>
    long RedBlackTree<Key, Value>::max(long nid) const
    {
        assert(nid != m_nil);

        while (m_nodes[nid].right != m_nil) {
            nid = m_nodes[nid].right;
        }
        return nid;
    }


    template <typename Key, typename Value>
    long RedBlackTree<Key, Value>::successor(long nid) const
    {
        assert(nid != m_nil);

        long sid; // Successor node index.

        if (m_nodes[nid].right != m_nil) {
            return min(m_nodes[nid].right);
        }

        sid = m_nodes[nid].parent;
        while (sid != m_nil && nid == m_nodes[sid].right) {
            nid = sid;
            sid = m_nodes[sid].parent;
        }

        return sid;
    }


    /// \pre Right child of <b>nid</b> is not nil.
    template <typename Key, typename Value>
    void RedBlackTree<Key, Value>::rotate_left(long nid)
    {
        assert(m_nodes[nid].right != m_nil);

        long yid = m_nodes[nid].right;
        m_nodes[nid].right = m_nodes[yid].left;
        if (m_nodes[yid].left != m_nil) {
            long left = m_nodes[yid].left;
            m_nodes[left].parent = nid;
        }

        long pid = m_nodes[nid].parent;
        m_nodes[yid].parent = pid;
        if (pid == m_nil) {
            m_root = yid;
        } else if (nid == m_nodes[pid].left) {
            m_nodes[pid].left = yid;
        } else {
            m_nodes[pid].right = yid;
        }
        m_nodes[yid].left = nid;
        m_nodes[nid].parent = yid;
    }


    /// \pre Left child of <b>nid</b> is not nil.
    template <typename Key, typename Value>
    void RedBlackTree<Key, Value>::rotate_right(long nid)
    {
        assert(m_nodes[nid].left != m_nil);

        long yid = m_nodes[nid].left;
        m_nodes[nid].left = m_nodes[yid].right;
        if (m_nodes[yid].right != m_nil) {
            long right = m_nodes[yid].right;
            m_nodes[right].parent = nid;
        }

        long pid = m_nodes[nid].parent;
        m_nodes[yid].parent = pid;
        if (pid == m_nil) {
            m_root = yid;
        } else if (nid == m_nodes[pid].right) {
            m_nodes[pid].right = yid;
        } else {
            m_nodes[pid].left = yid;
        }
        m_nodes[yid].right = nid;
        m_nodes[nid].parent = yid;
    }


    template <typename Key, typename Value>
    inline bool RedBlackTree<Key, Value>::is_consistent(void) const
    {
        return is_consistent(m_root);
    }


    template <typename Key, typename Value>
    bool RedBlackTree<Key, Value>::is_consistent(long nid) const
    {
        if (nid == m_nil) return true;

        long parent = m_nodes[nid].parent;
        long left = m_nodes[nid].left;
        long right = m_nodes[nid].right;

        if (parent != m_nil) {
            bool parent_link_ok = (m_nodes[parent].left == nid || m_nodes[parent].right == nid);
            bool parent_unique_children = (m_nodes[parent].left != m_nodes[parent].right);

            assert(parent_link_ok);
            assert(parent_unique_children);

            if (parent_link_ok == false) return false;
            if (parent_unique_children == false) return false;
        }
        if (left != m_nil) {
            bool left_link_ok = (m_nodes[left].parent == nid);
            bool left_subtree_ok = is_consistent(left);

            assert(left_link_ok);
            assert(left_subtree_ok);

            if (left_link_ok == false) return false;
            if (left_subtree_ok == false) return false;
        }
        if (right != m_nil) {
            bool right_link_ok = (m_nodes[right].parent == nid);
            bool right_subtree_ok = is_consistent(right);

            assert(right_link_ok);
            assert(right_subtree_ok);

            if (right_link_ok == false) return false;
            if (right_subtree_ok == false) return false;
        }
        return true;
    }
} // namespace algorithm

#endif // REDBLACKTREE_H
