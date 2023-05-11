// https://leetcode.com/problems/count-subarrays-with-fixed-bounds/

import java.util.LinkedList

class Solution {
    
    private fun contrib(
        nums: IntArray,
        start: Int,
        end: Int,
        min: Int,
        minIds: LinkedList<Int>,
        max: Int,
        maxIds: LinkedList<Int>
    ): Long {
        if (min == max) {
            val n = (end - start).toLong()
            return n*(n+1)/2
        }
        
        var contrib = 0.toLong()
        var pos = start
        while (!minIds.isEmpty() && !maxIds.isEmpty()) {
            if (nums[pos] == min) {
                contrib += end - maxIds.getFirst()
                minIds.removeFirst()
            } else if (nums[pos] == max) {
                contrib += end - minIds.getFirst()
                maxIds.removeFirst()
            } else {
                contrib += end - maxOf(minIds.getFirst(), maxIds.getFirst())
            }
            ++pos
        }
        return contrib
    }
    
    fun countSubarrays(nums: IntArray, min: Int, max: Int): Long {
        var start = 0
        var count = 0.toLong()
        while (start < nums.size) {
            if (nums[start] >= min && nums[start] <= max) {
                var end = start
                val minIds = LinkedList<Int>()
                val maxIds = LinkedList<Int>()
                while (end < nums.size && nums[end] >= min && nums[end] <= max) {
                    if (min != max) {
                        if (nums[end] == min) minIds.addLast(end)
                        if (nums[end] == max) maxIds.addLast(end)
                    }
                    ++end
                }
                count += contrib(nums, start, end, min, minIds, max, maxIds)
                start = end
            } else {
                ++start
            }
        }
        return count
    }
}