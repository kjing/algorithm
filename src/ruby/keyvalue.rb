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


require 'interface/keyvalue'


module Algorithm

    # Generic key implementation.
    class KeyOnly
        include KeyValueInterface
        include Comparable

        def initialize(key)
            @key = key
        end

        def value
            return @key
        end

        def eql?(other)
            if other.kind_of?(KeyValueInterface) then
                return (@key == other.key && @key == other.value)
            end
            return false
        end

        def <=>(other)
            case other
                when KeyValueInterface then return @key <=> other.key
            end
            return @key <=> other
        end

        def coerce(other)
            return KeyOnly.new(other), self
        end

    public
        attr_reader :key
    end


    # Generic key value pair implementation.
    class KeyValue < KeyOnly
        include KeyValueInterface

        def initialize(key, value = nil)
            super(key)
            @value = value
        end

        def eql?(other)
            if other.kind_of?(KeyValueInterface) then
                return (@key == other.key && @value == other.value)
            end
            return false
        end

    public
        attr_reader :value
    end

end # module Algorithm
