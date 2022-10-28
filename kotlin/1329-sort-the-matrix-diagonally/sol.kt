// https://leetcode.com/problems/sort-the-matrix-diagonally/

import kotlin.math.min

class Solution {
    fun diagonalSort(mat: Array<IntArray>): Array<IntArray> {
        val m = mat.size
        val n = mat[0].size
        for (startRow in 0..(m-1)) {
            val offsetMax = min(m - startRow - 1, n - 1)
            val values = mutableListOf<Int>()
            for (offset in 0..offsetMax) {
                values.add(mat[startRow + offset][offset])
            }
            values.sort()
            for (offset in 0..offsetMax) {
                mat[startRow + offset][offset] = values[offset]
            }
        }
        for (startCol in 1..(n-1)) {
            val offsetMax = min(m - 1, n - startCol - 1)
            val values = mutableListOf<Int>()
            for (offset in 0..offsetMax) {
                values.add(mat[offset][startCol + offset])
            }
            values.sort()
            for (offset in 0..offsetMax) {
                mat[offset][startCol + offset] = values[offset]
            }
        }
        return mat
    }
}
