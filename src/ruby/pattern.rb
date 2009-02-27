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


module Algorithm

    # The Knuth-Morris-Pratt (KMP) algorithm for the string matching problem.
    # Return the index in text where a copy of pattern begins.
    # Return nil if no match for pattern is found.
    def kmp_match(text, pattern, offset = 0)
        failure_link = kmp_setup(pattern)
        return kmp_scan(text, pattern, failure_link, offset)
    end


    # Construct KMP failure links.
    def kmp_setup(pattern)
        length = pattern.length

        length > 0 or raise "Expect length of pattern > 0"

        failure_link = Array.new(length)

        failure_link[0] = -1
        for k in 1...length
            s = failure_link[k-1]
            while s >= 0
                if pattern[s] == pattern[k-1] then
                    break
                end
                s = failure_link[s]
            end
            failure_link[k] = s + 1
        end
        return failure_link
    end


    # Scan the text string for the occurrence of the pattern string using the KMP algorithm.
    # Return the index in text where a copy of pattern begins.
    # Return nil if no match for pattern is found.
    def kmp_scan(text, pattern, failure_link, offset = 0)
        tlength = text.length
        plength = pattern.length

        tlength > 0 or raise "Expect length of text > 0"
        plength > 0 or raise "Expect length of pattern > 0"
        plength == failure_link.length or raise "Pattern and failure links are not the same size?"
        offset >= 0 or raise "Expect offset >= 0"

        match = nil
        i = offset
        k = 0

        while i < tlength
            if k < 0 then
                i += 1
                k = 0
            elsif text[i] == pattern[k] then
                i += 1
                k += 1
            else
                k = failure_link[k]
            end

            if k >= plength then
                match = i - plength
                break
            end
        end
        return match
    end


    def lcs_length(listx, listy,
                   firstx = 0, lastx = listx.length-1,
                   firsty = 0, lasty = listy.length-1)

        lx = lastx - firstx + 1
        ly = lasty - firsty + 1

        if lx == 0 || ly == 0 then
            return 0
        end

        z = Array.new(ly+1, 0)

        for i in 0...lx
            # k = 0, z[0] == 0
            next_zik = z[1]
            if listx[firstx + i] == listy[firsty] then
                z[1] = 1
            end
            zik = next_zik

            for k in 1...ly
                next_zik = z[k+1]
                if listx[firstx + i] == listy[firsty + k] then
                    z[k+1] = zik + 1
                elsif z[k] >= z[k+1] then
                    z[k+1] = z[k]
                end
                zik = next_zik
            end
        end

        length = z[ly]
        return length
    end


    module_function :kmp_match
    module_function :kmp_setup
    module_function :kmp_scan
    module_function :lcs_length

end # module Algorithm
