// https://leetcode.com/problems/maximum-running-time-of-n-computers/

class Solution {
    
    private fun IntArray.sumLong(): Long {
        var sum = 0L
        for (num in this) sum += num
        return sum
    }
    
    private fun canRunForTime(n: Int, batteries: IntArray, time: Long): Boolean {
        var power = 0L
        for (num in batteries) {
            power += minOf(num.toLong(), time)
        }
        return power >= time * n
    }
    
    fun maxRunTime(n: Int, batteries: IntArray): Long {
        var l = 1L
        var r = batteries.sumLong() / n
        if (canRunForTime(n, batteries, r)) return r
        
        while (l + 1 != r) {
            val candidateTime = l + (r -  l) / 2
            if (canRunForTime(n, batteries, candidateTime)) {
                l = candidateTime
            } else {
                r = candidateTime
            }
        }
        return l
    }
}
