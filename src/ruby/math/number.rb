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


    def coprime?(a, b)
        return (gcd(a, b) == 1) ? true : false
    end


    def factor_whp(n)
        return factor_whp_PollardRho_SF(n)
    end


    # Reference:
    # * Introduction to Algorithms - T. H. Cormen, C. E. Leiserson, R. L. Rivest & C. Stein
    def factor_whp_PollardRho_CLRS(n, ntrial = nil)
        n = abs(n)
        if n >= 0 && n <= 3 then return n; end

        ntrial ||= ::Math.sqrt(n).ceil
        i = 1
        x = rand(n)
        y = x
        k = 2
        begin
            i += 1
            x = (x*x - 1) % n
            d = gcd(y-x, n)
            if d != 1 && d != n then
                return d
            end
            if i == k then
                y = x
                k *= 2
            end
            ntrial -= 1
        end while ntrial >= 0
        return n
    end


    # Reference:
    # * An Introduction To The Analysis Of Algorithms - Robert Sedgewick & Philippe Flajolet
    def factor_whp_PollardRho_SF(n)
        n = abs(n)
        if n >= 0 && n <= 3 then return n; end

        a = rand(n)
        b = a
        c = rand(n)
        d = nil
        begin
            a = (a*a + c) % n
            b = (b*b + c)
            g = b*b
            b = (g + c) % n
            d = gcd((a-b) % n, n)
        end until d != 1
        return d
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


    # binary GCD found in NIST dads site.
    # http://www.nist.gov/dads/HTML/binaryGCD.html
    #
    # Note: Discovered by J. Stein in 1967. Another source says discovered
    # by R. Silver and J. Tersian in 1962 and published by G. Stein in 1967.
    #
    # The algorithm uses the following observations:
    # * If _u_ and _v_ are both even, gcd(u,v) = 2 gcd(u/2, v/2).
    # * If _u_ is even and _v_ is odd, gcd(u,v) = gcd(u/2, v).
    # * Otherwise both are odd, and gcd(u,v) = gcd(|u-v|/2, v). (Euclid's algorithm with a
    #   division by 2 since the difference of two odd numbers is even.)
    #
    # Binary GCD Algorithm:
    #   1.    g = 1
    #   2.    while u is even and v is even
    #   3.        u = u/2 (right shift)
    #   4.        v = v/2
    #   5.        g = 2*g (left shift)
    #   6.    Now u or v (or both) are odd.
    #   7.    while u > 0
    #   8.        if u is even, u = u/2
    #   9.        else if v is even, v = v/2
    #   10.       else
    #   11.           t = |u-v|/2
    #   12.           if u < v, then v = t else u = t
    #   13.   return v*g
    def gcd_binary(a, b)
        g = 1
        u = abs(a)
        v = abs(b)

        while even?(u) && even?(v)
            u /= 2
            v /= 2
            g *= 2
        end

        while u > 0
            if even?(u) then
                u /= 2
            elsif even?(v) then
                v /= 2
            else
                t = abs(u-v) / 2
                if u < v then
                    v = t
                else
                    u = t
                end
            end
        end

        return v*g
    end


    def lcm(a, b)
        v = gcd(a, b)
        return (v != 0) ? abs(a / v * b) : 0
    end


    def nbit(n)
        n >= 0 or raise "Expect n >= 0"

        count = 0
        m = n
        while m > 0
            count += 1
            m >>= 1
        end
        return count
    end


    # Compute a**b (mod n)
    def modular_power(a, b, n)
        a >= 0 or raise "Expect a >= 0"
        b >= 0 or raise "Expect b >= 0"
        n > 0 or raise "Expect n > 0"

        c = 0
        d = 1
        k = nbit(b)
        (k-1).downto(0) do |i|
            c = 2*c
            d = (d*d) % n
            if b[i] == 1 then
                c += 1
                d = (d*a) % n
            end
        end
        return d
    end


    def prime?(n)
        if n > 2 then
            m = 2
            while (r = n % m) != 0 && m*m <= n
                m += 1
            end
            return (r != 0)
        elsif n == 2 then
            return true
        else
            return false
        end
    end


    module_function :abs
    module_function :even?
    module_function :odd?
    module_function :coprime?
    module_function :factor_whp
    module_function :factor_whp_PollardRho_CLRS
    module_function :factor_whp_PollardRho_SF
    module_function :factorial
    module_function :gcd
    module_function :gcd_extended
    module_function :gcd_Euclid
    module_function :gcd_extended_Euclid
    module_function :gcd_binary
    module_function :lcm
    module_function :nbit
    module_function :modular_power
    module_function :prime?

end # module Math
end # module Algorithm
