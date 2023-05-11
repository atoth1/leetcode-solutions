// https://leetcode.com/problems/maximum-gap/

import kotlin.math.log10
import kotlin.math.pow

class Solution {
    
    private fun digitCount(n: Int): Int {
        return if (n == 0) 1 else 1 + log10(n.toDouble()).toInt()
    }
    
    private fun Int.digitAt(pos: Int): Int {
        return (this / 10.toDouble().pow(pos-1).toInt()) % 10
    }
    
    private fun radixSort(nums: MutableList<Int>, pos: Int) {
        if (nums.size > 1) {
            val buckets = Array(10) { mutableListOf<Int>() }
            for (num in nums) {
                val digit = num.digitAt(pos)
                buckets[digit].add(num)
            }

            var insertPos = 0
            for (bucket in buckets) {
                if (pos > 1) radixSort(bucket, pos - 1)
                for (num in bucket) {
                    nums[insertPos++] = num
                }
            }
        }
    }
    
    fun maximumGap(nums: IntArray): Int {
        return if (nums.size < 2) {
            0
        } else {
            var maxDigitCount = 0
            val numsList = mutableListOf<Int>()
            for (num in nums) {
                val count = digitCount(num)
                if (count > maxDigitCount) maxDigitCount = count
                numsList.add(num)
            }
            radixSort(numsList, maxDigitCount)
            
            var max = 0
            for (pos in 1 until numsList.size) {
                var diff = numsList[pos] - numsList[pos-1]
                if (diff > max) max = diff
            }
            max
        }
    }
}