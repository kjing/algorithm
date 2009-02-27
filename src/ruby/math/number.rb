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


require 'assert'


module Algorithm
module Math

    def abs(x)
        return (x >= 0) ? x : -x
    end


    def even?(x)
        return (x % 2 == 0) ? true : false
    end


    def odd?(x)
        return (x % 2 != 0) ? true : false
    end


    def factorial(n)
        n >= 0 or raise "Expect n >= 0, but got n = #{n}"

        k = 1
        for i in 1..n
            k *= i
        end
        return k
    end


    def gcd(a, b)
        a = abs(a)
        b = abs(b)
        return gcd_Euclid(a, b)
    end


    def gcd_extended(a, b)
        a = abs(a)
        b = abs(b)
        return gcd_extended_Euclid(a, b)
    end


    # Euclid's GCD algorithm.
    def gcd_Euclid(a, b)
        (a >= 0 && b >= 0) or raise "Inputs a and b should be >= 0"

        return (b == 0) ? a : gcd_Euclid(b, a % b)
    end


    # Extended Euclid's GCD algorithm.
    # TODO: Annotate return values.
    def gcd_extended_Euclid(a, b)
        (a >= 0 && b >= 0) or raise "Inputs a and b should be >= 0"

        if b == 0 then
            return a, 1, 0
        end
        d, x, y = gcd_extended_Euclid(b, a % b)
        x, y = y, x - (a/b)*y

        Assert.assert(d == a*x + b*y) if $DEBUG
        return d, x, y
    end


    module_function :abs
    module_function :even?
    module_function :odd?
    module_function :factorial
    module_function :gcd
    module_function :gcd_extended
    module_function :gcd_Euclid
    module_function :gcd_extended_Euclid

end # module Math
end # module Algorithm
