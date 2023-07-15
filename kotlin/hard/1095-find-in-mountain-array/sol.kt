// https://leetcode.com/problems/find-in-mountain-array/

/**
 * // This is MountainArray's API interface.
 * // You should not implement it, or speculate about its implementation
 * class MountainArray {
 *     fun get(index: Int): Int {}
 *     fun length(): Int {}
 * }
 */

class Solution {
    
    private fun getPeakId(arr: MountainArray): Int {
        var l = 0
        var r = arr.length() - 2
        while (l + 1  != r) {
            val m = (l + r) / 2
            if (arr.get(m) < arr.get(m + 1)) {
                l = m
            } else {
                r = m
            }
        }
        return r
    }
    
    private fun searchIncreasingRange(
        target: Int,
        first: Int,
        firstValue: Int,
        last: Int,
        lastValue: Int,
        arr: MountainArray
    ): Int {
        var l = first
        var lValue = firstValue
        var r = last
        var rValue = lastValue
        while (l + 1 != r) {
            val m = (l + r) / 2
            val value = arr.get(m)
            if (value < target) {
                l = m
                lValue = value
            } else if (value > target) {
                r = m
                rValue = value
            } else {
                return m
            }
        }
        return -1
    }
    
    private fun searchDecreasingRange(
        target: Int,
        first: Int,
        firstValue: Int,
        last: Int,
        lastValue: Int,
        arr: MountainArray
    ): Int {
        var l = first
        var lValue = firstValue
        var r = last
        var rValue = lastValue
        while (l + 1 != r) {
            val m = (l + r) / 2
            val value = arr.get(m)
            if (value > target) {
                l = m
                lValue = value
            } else if (value < target) {
                r = m
                rValue = value
            } else {
                return m
            }
        }
        return -1
    }
    
    fun findInMountainArray(target: Int, mountainArr: MountainArray): Int {
        val n = mountainArr.length()
        val peakId = getPeakId(mountainArr)
        
        val val1 = mountainArr.get(0)
        val val2 = mountainArr.get(peakId)
        val val3 = mountainArr.get(n - 1)
        
        if (target == val2) return peakId
        if (target > val2) return -1
        
        if (target == val1) return 0
        if (target > val1) {
            val id = searchIncreasingRange(target, 0, val1, peakId, val2, mountainArr)
            if (id != -1) return id
        }
        
        if (target == val3) return n - 1
        if (target > val3) {
            val id = searchDecreasingRange(target, peakId, val2 , n - 1, val3, mountainArr)
            if (id != -1) return id
        }
        
        return -1
    }
}