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


module Algorithm

    module QueueInterface
        def enqueue(v);     raise NotImplementedError; end
        def dequeue;        raise NotImplementedError; end
        def front;          raise NotImplementedError; end
        def clear;          raise NotImplementedError; end
        def empty?;         raise NotImplementedError; end
        def size;           raise NotImplementedError; end
        def ==(other);      raise NotImplementedError; end
        def freeze;         raise NotImplementedError; end
    end


    # Generic FIFO queue implementation.
    class Queue
        include QueueInterface
        extend Forwardable

        def initialize
            @q = []     # Storage for queue elements.
        end


        def initialize_copy(other)
            @q = other.q.dup
        end


        def_delegators :@q, :empty?, :size, :==

    public

        def enqueue(*v)
            @q.push(*v)
            return self
        end
        alias enq enqueue


        def dequeue
            not @q.empty? or raise "dequeue() on an empty queue!"

            @q.shift
            return self
        end
        alias deq dequeue


        def front
            not @q.empty? or raise "front() on an empty queue!"

            return @q.first
        end


        def clear
            @q.clear
            return self
        end


        def freeze
            super
            @q.freeze
            return self
        end

    protected

        attr_reader :q

    end # class Queue

end # module Algorithm
