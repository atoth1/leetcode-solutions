// https://leetcode.com/problems/minimum-replacements-to-sort-the-array/

class Solution {
    fun minimumReplacement(nums: IntArray): Long {
        var count = 0L
        var bound = nums.last();
        for (id in nums.size - 2 downTo 0) {
            if (nums[id] > bound) {
                val quot = nums[id] / bound
                val rem = nums[id] - quot * bound
                if (rem != 0) {
                    count += quot
                    bound = nums[id] / (quot + 1)
                } else {
                    count += quot - 1
                }
            } else {
                bound = nums[id]
            }
        }
        return count
    }
}
