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

#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <cassert>
#include <vector>

namespace algorithm
{
    template <typename Key, typename Value>
    class BinaryTree
    {
    public:
        BinaryTree(void);
        ~BinaryTree(void);

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
        /// \brief The data type of the tree node.
        typedef struct {
            long parent; ///< The index of the parent node.
            long left; ///< The index of the left child node.
            long right; ///< The index of the right child node.
            Key key; ///< The key of the element associated.
            Value value; ///< The value of the element associated.
        } Node;
        typedef std::vector<Node> NodeList;

        /// \brief Search for the node or element with <b>key</b> in the tree.
        /// \param[in] key The key of the node or element to search for.
        /// \return The index of the node or element with <b>key</b> if found, -1 otherwise.
        long search_node(const Key& key) const;

        /// \brief Remove the node with index <b>nid</b>.
        /// \param[in] nid The index of the node to remove.
        void remove_node(long nid);

        /// \brief Get and initialize a free node.
        /// \param[in] parent The index of the parent node.
        /// \param[in] left The index of the left child node.
        /// \param[in] right The index of the right child node.
        /// \param[in] key The key of the element associated to this node.
        /// \param[in] value The value of the element associated to this node.
        /// \return The index of a free node.
        long create_node(long parent, long left, long right,
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
        NodeList m_nodes; ///< The list of all nodes.
    };
} // namespace algorithm


// ===================================================================
// Implementation
// ===================================================================

namespace algorithm
{
    template <typename Key, typename Value>
    const long BinaryTree<Key, Value>::m_block_size = 256;


    template <typename Key, typename Value>
    BinaryTree<Key, Value>::BinaryTree(void) : m_root(-1), m_free_head(-1), m_size(0), m_nodes()
    {
    }


    template <typename Key, typename Value>
    BinaryTree<Key, Value>::~BinaryTree(void)
    {
    }


    template <typename Key, typename Value>
    long BinaryTree<Key, Value>::size(void) const
    {
        return m_size;
    }


    template <typename Key, typename Value>
    const Value* BinaryTree<Key, Value>::search(const Key& key) const
    {
        long nid = search_node(key);
        if (nid >= 0) {
            return &m_nodes[nid].value;
        }
        return NULL;
    }


    /// \par References:
    /// Introduction to Algorithms - T. H. Cormen, C. E. Leiserson, R. L. Rivest & C. Stein
    template <typename Key, typename Value>
    long BinaryTree<Key, Value>::search_node(const Key& key) const
    {
        long nid = m_root;

        while (nid >= 0 && key != m_nodes[nid].key) {
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
    bool BinaryTree<Key, Value>::insert(const Key& key, const Value& value)
    {
        long pid = -1; // Parent node index.
        long nid = m_root; // Node index.

        // Get the right node, pid, to insert.
        // If the key exists, return immediately.
        while (nid >= 0) {
            pid = nid;
            if (key == m_nodes[nid].key) {
                return false;
            } else if (key < m_nodes[nid].key) {
                nid = m_nodes[nid].left;
            } else {
                nid = m_nodes[nid].right;
            }
        }

        if (pid < 0) { // The binary tree is empty.
            m_root = create_node(-1, -1, -1, key, value);
        } else if (key < m_nodes[pid].key) {
            long left = create_node(pid, -1, -1, key, value);
            m_nodes[pid].left = left;
        } else {
            long right = create_node(pid, -1, -1, key, value);
            m_nodes[pid].right = right;
        }
        ++m_size;

        return true;
    }


    template <typename Key, typename Value>
    bool BinaryTree<Key, Value>::remove(const Key& key)
    {
        long nid = search_node(key);
        if (nid >= 0) {
            remove_node(nid);
            return true;
        }
        return false;
    }


    /// \par References:
    /// Introduction to Algorithms - T. H. Cormen, C. E. Leiserson, R. L. Rivest & C. Stein
    template <typename Key, typename Value>
    void BinaryTree<Key, Value>::remove_node(long nid)
    {
        assert(nid >= 0);

        long xid, yid;
        if (m_nodes[nid].left < 0 || m_nodes[nid].right < 0) {
            yid = nid;
        } else {
            yid = successor(nid);
        }

        if (m_nodes[yid].left >= 0) {
            xid = m_nodes[yid].left;
        } else {
            xid = m_nodes[yid].right;
        }

        if (xid >= 0) {
            m_nodes[xid].parent = m_nodes[yid].parent;
        }

        if (m_nodes[yid].parent < 0) {
            m_root = xid;
        } else {
            if (yid == m_nodes[m_nodes[yid].parent].left) {
                m_nodes[m_nodes[yid].parent].left = xid;
            } else {
                m_nodes[m_nodes[yid].parent].right = xid;
            }
        }

        if (yid != nid) {
            m_nodes[nid].key = m_nodes[yid].key;
            m_nodes[nid].value = m_nodes[yid].value;
        }

        if (yid >= 0) {
            --m_size;
            recycle_node(yid);
        }
    }


    /// \warning This may re-allocate <b>m_nodes</b>, and invalidate all
    ///          references to <b>m_nodes</b>.
    template <typename Key, typename Value>
    long BinaryTree<Key, Value>::create_node(long parent, long left, long right,
                                             const Key& key, const Value& value)
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

        m_nodes[nid].parent = parent;
        m_nodes[nid].left = left;
        m_nodes[nid].right = right;
        m_nodes[nid].key = key;
        m_nodes[nid].value = value;

        return nid;
    }


    template <typename Key, typename Value>
    void BinaryTree<Key, Value>::recycle_node(long nid)
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
                // Only root or free nodes have parent links as -1.
                // And we should re-locate the root node if encountered.
                if (m_nodes[rid].parent < 0 && rid != m_root) {
                    // Remove node rid out of the free-node list.
                    if (m_nodes[rid].left >= 0) {
                        m_nodes[m_nodes[rid].left].right = m_nodes[rid].right;
                    }
                    if (m_nodes[rid].right >= 0) {
                        m_nodes[m_nodes[rid].right].left = m_nodes[rid].left;
                    }
                    m_nodes[rid].parent = -1;
                    m_nodes[rid].left = -1;
                    m_nodes[rid].right = -1;
                    continue;
                }

                long fid = m_free_head; // Free-node index.
                while (fid >= nsize - m_block_size) {
                    if (m_nodes[fid].left >= 0) {
                        m_nodes[m_nodes[fid].left].right = m_nodes[fid].right;
                    }
                    if (m_nodes[fid].right >= 0) {
                        m_nodes[m_nodes[fid].right].left = m_nodes[fid].left;
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
                if (fid_parent >= 0) {
                    if (m_nodes[fid_parent].left == rid) {
                        m_nodes[fid_parent].left = fid;
                    } else {
                        assert(m_nodes[fid_parent].right == rid);
                        m_nodes[fid_parent].right = fid;
                    }
                } else {
                    m_root = fid;
                }
                if (fid_left >= 0) {
                    assert(m_nodes[fid_left].parent == rid);
                    m_nodes[fid_left].parent = fid;
                }
                if (fid_right >= 0) {
                    assert(m_nodes[fid_right].parent == rid);
                    m_nodes[fid_right].parent = fid;
                }
            }
            m_nodes.resize(nsize - m_block_size);
        }
    }


    template <typename Key, typename Value>
    long BinaryTree<Key, Value>::min(long nid) const
    {
        assert(nid >= 0);

        while (m_nodes[nid].left >= 0) {
            nid = m_nodes[nid].left;
        }
        return nid;
    }


    template <typename Key, typename Value>
    long BinaryTree<Key, Value>::max(long nid) const
    {
        assert(nid >= 0);

        while (m_nodes[nid].right >= 0) {
            nid = m_nodes[nid].right;
        }
        return nid;
    }


    template <typename Key, typename Value>
    long BinaryTree<Key, Value>::successor(long nid) const
    {
        assert(nid >= 0);

        long sid; // Successor node index.

        if (m_nodes[nid].right >= 0) {
            return min(m_nodes[nid].right);
        }

        sid = m_nodes[nid].parent;
        while (sid >= 0 && nid == m_nodes[sid].right) {
            nid = sid;
            sid = m_nodes[sid].parent;
        }

        return sid;
    }


    template <typename Key, typename Value>
    inline bool BinaryTree<Key, Value>::is_consistent(void) const
    {
        return is_consistent(m_root);
    }


    template <typename Key, typename Value>
    bool BinaryTree<Key, Value>::is_consistent(long nid) const
    {
        if (nid < 0) return true;

        long parent = m_nodes[nid].parent;
        long left = m_nodes[nid].left;
        long right = m_nodes[nid].right;

        if (parent >= 0) {
            bool parent_link_ok = (m_nodes[parent].left == nid || m_nodes[parent].right == nid);
            bool parent_unique_children = (m_nodes[parent].left != m_nodes[parent].right);

            assert(parent_link_ok);
            assert(parent_unique_children);

            if (parent_link_ok == false) return false;
            if (parent_unique_children == false) return false;
        }
        if (left >= 0) {
            bool left_link_ok = (m_nodes[left].parent == nid);
            bool left_subtree_ok = is_consistent(left);

            assert(left_link_ok);
            assert(left_subtree_ok);

            if (left_link_ok == false) return false;
            if (left_subtree_ok == false) return false;
        }
        if (right >= 0) {
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

#endif // BINARYTREE_H
