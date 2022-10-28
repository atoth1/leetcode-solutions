// https://leetcode.com/problems/construct-quad-tree/

/**
 * Definition for a QuadTree node.
 * class Node(var `val`: Boolean, var isLeaf: Boolean) {
 *     var topLeft: Node? = null
 *     var topRight: Node? = null
 *     var bottomLeft: Node? = null
 *     var bottomRight: Node? = null
 * }
 */

const val nonLeafVal = false

class Solution {
    fun construct(grid: Array<IntArray>): Node? {
        return impl(grid, 0, 0, grid.size)
    }
    
    private fun impl(
        grid: Array<IntArray>,
        beginRow: Int,
        beginCol: Int,
        n: Int
    ): Node {
        if (hasUniformValues(grid, beginRow, beginCol, n)) {
            return Node(if (grid[beginRow][beginCol] == 0) false else true, true)
        } else {
            val subCount = n/2
            return Node(nonLeafVal, false).also {node ->
                node.topLeft = impl(grid, beginRow, beginCol, subCount)
                node.bottomLeft = impl(grid, beginRow + subCount, beginCol, subCount)
                node.topRight = impl(grid, beginRow, beginCol + subCount, subCount)
                node.bottomRight = impl(grid, beginRow + subCount, beginCol + subCount, subCount)
            }
        }
    }
    
    private fun hasUniformValues(
        grid: Array<IntArray>,
        beginRow: Int,
        beginCol: Int,
        n: Int
    ): Boolean {
        val topLeft = grid[beginRow][beginCol]
        for (row in beginRow until beginRow+n) {
            for (col in beginCol until beginCol+n) {
                if (grid[row][col] != topLeft) return false
            }
        }
        return true
    }
}
