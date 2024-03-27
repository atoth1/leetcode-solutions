// https://leetcode.com/problems/minimum-number-of-operations-to-make-array-continuous/

class Solution {
    private fun IntArray.uniqueSorted(): List<Int> {
        val ret = mutableListOf<Int>()
        for (num in this) ret.add(num)
        ret.sort()
        
        var end = 1
        for (id in 1 until ret.size) {
            if (ret[id] != ret[end - 1]) {
                ret[end++] = ret[id]
            }
        }
        while (ret.size > end) ret.removeLast()
        
        return ret
    }
    
    fun minOperations(nums: IntArray): Int {
        val sortedNums = nums.uniqueSorted()
        var begin = 0
        var end = 0
        var count = 0
        var maxCount = 0
        while (end != sortedNums.size) {
            while (end != sortedNums.size && sortedNums[end] < sortedNums[begin] + nums.size) {
                ++end
                ++count
            }
            maxCount = maxOf(maxCount, count)
            ++begin
            --count
        }
        return nums.size - maxCount
    }
}
