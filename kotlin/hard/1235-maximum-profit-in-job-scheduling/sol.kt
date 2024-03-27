// https://leetcode.com/problems/maximum-profit-in-job-scheduling/

import java.util.TreeMap

class Solution {
    
    fun jobScheduling(startTime: IntArray, endTime: IntArray, profit: IntArray): Int {
        val n = startTime.size
        val ids = IntArray(n) { it }
        val sortedIds = ids.sortedByDescending { startTime[it] }
        val cache = TreeMap<Int, Int>()
        for (id in sortedIds) {
            val candidate = maxOf(
                profit[id] + (cache.ceilingEntry(endTime[id])?.value ?: 0 ),
                cache.higherEntry(startTime[id])?.value ?: 0
            )
            cache[startTime[id]] = cache[startTime[id]]?.let { maxOf(it, candidate) } ?: candidate
        }
        return cache.firstEntry()?.value ?: 0
    }
}
