// https://leetcode.com/problems/number-of-great-partitions/

private const val MOD = 1000000007

private infix fun Int.modPlus(other: Int): Int = (this + other) % MOD

private infix fun Int.modMinus(other: Int): Int {
    var ret = this - other
    return if (ret < 0) ret + MOD else ret
}

private infix fun Int.modTimes(other: Int) : Int = ((toLong() * other) % MOD).toInt()

class Solution {
    fun countPartitions(nums: IntArray, k: Int): Int {
        val n = nums.size
        if (nums.sumOf { it.toLong() } < 2L * k) {
            return 0
        }
        
        var ret = 1
        repeat (n) {
            ret = ret modTimes 2
        }
        
        val dp = Array(k) { targetSum -> if (targetSum == 0) IntArray(n) { 1 } else IntArray(n) }
        for (targetSum in 1 until k) {
            if (nums[n - 1] == targetSum) {
                dp[targetSum][n - 1] = 1
            }
            
            for (id in n - 2 downTo 0) {
                dp[targetSum][id] = dp[targetSum][id + 1] modPlus if (targetSum >= nums[id]) {
                    dp[targetSum - nums[id]][id + 1]
                } else {
                    0
                }
            }
        }
        
        for (targetSum in 0 until k) {
            ret = ret modMinus dp[targetSum][0]
            ret = ret modMinus dp[targetSum][0]
        }
        return ret
    }
}
