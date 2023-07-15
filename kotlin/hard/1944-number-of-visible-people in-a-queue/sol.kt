// https://leetcode.com/problems/number-of-visible-people-in-a-queue/

import java.util.Stack

class Solution {
    fun canSeePersonsCount(heights: IntArray): IntArray {
        val n = heights.size
        val ret = IntArray(n)
        val seen = Stack<Int>()
        for (pos in n - 1 downTo 0) {
            while (!seen.isEmpty() && heights[pos] > seen.peek()) {
                seen.pop()
                ++ret[pos]
            }
            if (!seen.isEmpty()) {
                ++ret[pos]
            }
            seen.push(heights[pos])
        }
        return ret
    }
}