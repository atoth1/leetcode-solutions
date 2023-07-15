// https://leetcode.com/problems/number-of-increasing-paths-in-a-grid/

class Solution {
    
    companion object {
        private const val MOD = 1000000007
    
        private data class Position(val row: Int, val col: Int)

        private data class IntWrapper(var value: Int)

        private fun impl(
            grid: Array<IntArray>,
            pos: Position,
            sum: IntWrapper,
            cache: MutableMap<Position, Int>
        ): Int {
            return cache[pos] ?: run {
                var ret = 1
                if (pos.row > 0 && grid[pos.row][pos.col] < grid[pos.row - 1][pos.col]) {
                    ret = (ret + impl(grid, Position(pos.row - 1, pos.col), sum, cache)) % MOD
                }
                if (pos.row < grid.size - 1 && grid[pos.row][pos.col] < grid[pos.row + 1][pos.col]) {
                    ret = (ret + impl(grid, Position(pos.row + 1, pos.col), sum, cache)) % MOD
                }
                if (pos.col > 0 && grid[pos.row][pos.col] < grid[pos.row][pos.col - 1]) {
                    ret = (ret + impl(grid, Position(pos.row, pos.col - 1), sum, cache)) % MOD
                }
                if (pos.col < grid[0].size - 1 && grid[pos.row][pos.col] < grid[pos.row][pos.col + 1]) {
                    ret = (ret + impl(grid, Position(pos.row, pos.col + 1), sum, cache)) % MOD
                }

                sum.value = (sum.value + ret) % MOD;
                cache[pos] = ret
                ret
            }
        }
    }
    
    fun countPaths(grid: Array<IntArray>): Int {
        val sum = IntWrapper(0)
        val cache = mutableMapOf<Position, Int>()
        for (row in 0 until grid.size) {
            for (col in 0 until grid[0].size) {
                impl(grid, Position(row, col), sum, cache)
            }
        }
        return sum.value
    }
}