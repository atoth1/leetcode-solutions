// https://leetcode.com/problems/minimum-cost-to-make-array-equal/

import java.util.TreeMap

class Solution {
    fun minCost(nums: IntArray, costs: IntArray): Long {
        val numToCost = TreeMap<Int, Long>()
        var totalCost = 0L
        for (id in 0 until nums.size) {
            numToCost[nums[id]] = numToCost[nums[id]]?.let { it + costs[id] } ?: costs[id].toLong()
            totalCost += costs[id]
        }
        
        var candidateCost = 0L
        for ((num, cost) in numToCost) {
            candidateCost += cost * (num - numToCost.firstKey())
        }
        
        val iter = numToCost.iterator()
        var (prevNum, prevCost) = iter.next()
        var minCost = candidateCost
        var lessCost = 0L
        var greaterCost = totalCost - prevCost
        while (iter.hasNext()) {
            val (currNum, currCost) = iter.next()
            lessCost += prevCost
            candidateCost += lessCost * (currNum - prevNum)
            candidateCost -= greaterCost * (currNum - prevNum)
            greaterCost -= currCost
            minCost = minOf(minCost, candidateCost)
            prevNum = currNum
            prevCost = currCost
        }
        return minCost
    }
}