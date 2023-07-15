// https://leetcode.com/problems/stone-game-iii/

class Solution {
    fun stoneGameIII(values: IntArray): String {
        val n = values.size
        var postfix = values[n - 1]
        val dp = mutableListOf(values[n - 1], 0, 0)
        for (id in n - 2 downTo 0) {
            postfix += values[id]
            var value = Integer.MIN_VALUE
            for (offset in 0 until 3) {
                val candidate = postfix - dp[offset]
                if (candidate > value) value = candidate
            }
            dp[2] = dp[1]
            dp[1] = dp[0]
            dp[0] = value
        }
        
        val alicePoints = dp[0]
        val bobPoints = postfix - alicePoints
        return if (alicePoints > bobPoints) {
            "Alice"
        } else if (alicePoints < bobPoints) {
            "Bob"
        } else {
            "Tie"
        }
    }
}