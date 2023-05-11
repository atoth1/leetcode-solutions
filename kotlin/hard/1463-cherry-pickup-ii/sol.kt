// https://leetcode.com/problems/cherry-pickup-ii/

class Solution {
    private fun initDp(grid: Array<IntArray>): Array<IntArray> {
        val m = grid.size
        val n = grid[0].size
        
        val dp = Array(n) { IntArray(n) }
        for (col1 in 0 until n) {
            for (col2 in 0 until n) {
                dp[col1][col2] = if (col1 == col2) {
                    grid[m-1][col1]
                } else {
                    grid[m-1][col1] + grid[m-1][col2]
                }
            }
        }
        return dp
    }
    
    private fun doDp(grid: Array<IntArray>): Int {
        val m = grid.size
        val n = grid[0].size
        
        var curr = Array(n) { IntArray(n) }
        var next = initDp(grid)
        for (row in m-2 downTo 0) {
            for (col1 in 0 until n) {
                for (col2 in 0 until n) {
                    for (offset1 in -1..1) {
                        for (offset2 in -1..1) {
                            if (col1+offset1 >= 0 && col1+offset1 < n && col2+offset2 >= 0 && col2+offset2 < n) {
                                curr[col1][col2] = maxOf(curr[col1][col2], next[col1+offset1][col2+offset2])
                            }
                        }
                    }
                    curr[col1][col2] += if (col1 == col2) {
                        grid[row][col1]
                    } else {
                        grid[row][col1] + grid[row][col2]
                    }
                }
            }
            curr = next.also { next = curr }
        }
        return next[0][n-1]
    }
    
    fun cherryPickup(grid: Array<IntArray>): Int {
        return doDp(grid)
    }
}
