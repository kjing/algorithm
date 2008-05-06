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

#ifndef STACK_H
#define STACK_H

#include <cassert>
#include <vector>

namespace algorithm
{
    template <typename T>
    class Stack
    {
    public:
        Stack(void);
        Stack(const Stack<T>& rhs);
        ~Stack(void);

        Stack& operator=(const Stack& rhs);

        /// \brief Is the stack empty?
        /// \return true if the stack has no elements.
        bool empty(void);

        /// \brief Pop an element out of the stack if the stack is non-empty, do nothing otherwise.
        void pop(void);

        /// \brief Push an element into the stack.
        /// \param[in] v The element to push into the stack.
        /// \note The element <b>v</b> is copied during the push.
        void push(const T& v);

        /// \brief Get the top element in the stack.
        /// \warning It's an error to access the top element when the stack is empty.
        /// \return The top element in the stack.
        T& top(void);
        const T& top() const;

        /// \brief Get the number of elements in the stack.
        /// \return The number of elements in the stack.
        long size(void) const;

    private:
        typedef std::vector<T*> Data;
        Data m_data; ///< The data storage to store a list of blocks of elements.
        long m_index; ///< The index to the top element in the last block of the stack.
        static const long m_block_size; ///< The maximum number of elements in a block.
    };
} // namespace algorithm


// ===================================================================
// Implementation
// ===================================================================

namespace algorithm
{
    template <typename T>
    const long Stack<T>::m_block_size = 256;


    template <typename T>
    Stack<T>::Stack(void) : m_data(1, NULL), m_index(-1)
    {
        T*& last_block = m_data.back();
        last_block = new T[m_block_size];

        assert(last_block != NULL);
    }


    template <typename T>
    Stack<T>::Stack(const Stack<T>& rhs) : m_data(), m_index(-1)
    {
        *this = rhs;
    }


    template <typename T>
    Stack<T>::~Stack(void)
    {
        for (typename Data::iterator i = m_data.begin(); i != m_data.end(); ++i) {
            T*& block = *i;

            assert(block != NULL);

            delete[] block;
            block = NULL;
        }
        m_index = -1;
    }


    template <typename T>
    Stack<T>& Stack<T>::operator=(const Stack& rhs)
    {
        typename Data::iterator i;
        typename Data::const_iterator k;

        if (this == &rhs) return *this;

        // Remove existing elements in current stack.
        for (i = m_data.begin(); i != m_data.end(); ++i) {
            T*& block = *i;

            assert(block != NULL);

            delete[] block;
            block = NULL;
        }

        m_data.resize(rhs.m_data.size(), NULL);

        assert(m_data.size() == rhs.m_data.size());

        // Copy elements into current stack.
        for (i = m_data.begin(), k = rhs.m_data.begin(); i != m_data.end(); ++i, ++k)
        {
            const T* const& src_block = *k;
             T*& dest_block = *i;
            dest_block = new T[m_block_size];

            assert(dest_block != NULL);

            for (long p = 0; p < m_block_size; ++p) {
                dest_block[p] = src_block[p];
            }
        }
        m_index = rhs.m_index;
        return *this;
    }


    template <typename T>
    bool Stack<T>::empty(void)
    {
        return (m_index == -1);
    }


    template <typename T>
    void Stack<T>::pop(void)
    {
        if (empty()) return;

        assert(m_index >= 0 && m_index <= m_block_size-1);

        if (m_index == 0) {
            long size = m_data.size();
            if (size > 1) {
                m_data.resize(size-1);
                m_index = m_block_size;
            }
        }
        --m_index;

        assert(m_index >= -1 && m_index <= m_block_size-1);
    }


    template <typename T>
    void Stack<T>::push(const T& v)
    {
        assert(m_index >= -1 && m_index <= m_block_size-1);

        ++m_index;
        if (m_index == m_block_size) {
            T* block = new T[m_block_size];

            assert(block != NULL);

            m_data.push_back(block);
            m_index = 0;
        }

        T*& last_block = m_data.back();
        last_block[m_index] = v;

        assert(m_index >= 0 && m_index <= m_block_size-1);
    }


    template <typename T>
    T& Stack<T>::top(void)
    {
        assert(!empty());

        T*& last_block = m_data.back();
        return last_block[m_index];
    }


    template <typename T>
    const T& Stack<T>::top(void) const
    {
        assert(!empty());

        const T*& last_block = m_data.back();
        return last_block[m_index];
    }


    template <typename T>
    long Stack<T>::size(void) const
    {
        return (m_data.size()-1)*m_block_size + m_index + 1;
    }
} // namespace algorithm

#endif // STACK_H

