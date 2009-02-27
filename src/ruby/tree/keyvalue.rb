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


require 'tree/interface/keyvalue'


module Algorithm
module Tree

    # Generic key implementation.
    class KeyOnly
        include KeyValueInterface

        def initialize(key)
            @key = key
        end

        def value
            return @key
        end

    public
        attr_reader :key
    end


    # Generic key value pair implementation.
    class KeyValue
        include KeyValueInterface

        def initialize(key, value = nil)
            @key = key
            @value = value
        end

    public
        attr_reader :key, :value
    end

end # module Tree
end # module Algorithm
