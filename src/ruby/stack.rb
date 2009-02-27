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

    module StackInterface
        def push(v);    raise NotImplementedError; end
        def pop;        raise NotImplementedError; end
        def top;        raise NotImplementedError; end
        def clear;      raise NotImplementedError; end
        def empty?;     raise NotImplementedError; end
        def size;       raise NotImplementedError; end
        def ==(other);  raise NotImplementedError; end
        def freeze;     raise NotImplementedError; end
    end


    # Generic stack implementation.
    class Stack
        include StackInterface
        extend Forwardable

        def initialize
            @s = []     # Storage for stack elements.
        end


        def initialize_copy(other)
            @s = other.s.dup
        end


        def_delegators :@s, :empty?, :size, :==

    public

        def push(*v)
            @s.push(*v)
            return self
        end


        def pop
            not @s.empty? or raise "pop() on an empty stack!"

            @s.pop
            return self
        end


        def top
            not @s.empty? or raise "top() on an empty stack!"

            return @s.last
        end


        def clear
            @s.clear
            return self
        end


        def freeze
            super
            @s.freeze
            return self
        end

    protected

        attr_reader :s

    end # class Stack

end # module Algorithm
