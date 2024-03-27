// https://leetcode.com/problems/minimum-falling-path-sum-ii/

import java.util.PriorityQueue

class Solution {
    fun minFallingPathSum(matrix: Array<IntArray>): Int {
        val n = matrix.size
        if (n == 1) return matrix[0][0]
        
        var curr = matrix[n - 1].copyOf()
        var next = IntArray(n)
        for (row in n - 2 downTo 0) {
            curr = next.also { next = curr }
            val queue = PriorityQueue<Int> { x, y -> y - x }
            for (sum in next) {
                if (queue.size < 2) {
                    queue.add(sum)
                } else if (sum < queue.peek()) {
                    queue.poll()
                    queue.add(sum)
                }
            }
            val twoSmallest = mutableListOf<Int>()
            twoSmallest.add(queue.poll())
            twoSmallest.add(queue.poll())
            
            for (col in 0 until n) {
                val nextVal = if (next[col] == twoSmallest[1]) twoSmallest[0] else twoSmallest[1]
                curr[col] = matrix[row][col] + nextVal
            }
        }
        return curr.minOrNull()!!
    }
}
