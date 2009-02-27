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
module Matrix

    # Compute optimal matrix chain order for all lengths minimizing
    # the number of scalar multiplications.
    # The input +p+ is an array consists of the dimensions
    # of the matrices.
    def matrix_chain_order(p)
        n = p.length - 1
        m = []
        s = []
        for i in 1..n
            m[i] = []
            s[i] = []
            m[i][i] = 0
        end

        # Compute optimal matrix chain order.
        for l in 2..n
            for i in 1..n-l+1
                j = i+l-1
                for k in i..j-1
                    q = m[i][k] + m[k+1][j] + p[i-1]*p[k]*p[j]
                    if m[i][j].nil? || q < m[i][j] then
                        m[i][j] = q
                        s[i][j] = k
                    end
                end
            end
        end

        return m[1][n], m, s
    end


    module_function :matrix_chain_order

end # module Matrix
end # module Algorithm
