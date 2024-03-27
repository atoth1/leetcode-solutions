// https://leetcode.com/problems/median-of-two-sorted-arrays/

class Solution {
    fun findMedianSortedArrays(nums1: IntArray, nums2: IntArray): Double {
        val singleArrayMedian = { arr: IntArray ->
            val mid = arr.size / 2
            if (arr.size % 2 == 0) {
                (arr[mid - 1] + arr[mid]) / 2.0 
            } else {
                arr[mid].toDouble()
            } 
        }
        if (nums1.isEmpty()) {
            return singleArrayMedian(nums2)
        }
        if (nums2.isEmpty()) {
            return singleArrayMedian(nums1)
        }
        
        val upperBound = { arr: IntArray, value: Int ->
            if (value < arr[0]) 0
            else if (value >= arr.last()) arr.size
            else {
                var l = 0
                var r = arr.size - 1
                while (l + 1 != r) {
                    val m = l + (r - l) / 2
                    if (value < arr[m]) {
                        r = m
                    } else {
                        l = m
                    }
                }
                r
            }
        }
        
        val countLessEqual = { value: Int -> upperBound(nums1, value) + upperBound(nums2, value) }
        
        var l = minOf(nums1[0], nums2[0]) - 1
        var r = maxOf(nums1.last(), nums2.last())
        var rCount = nums1.size + nums2.size
        val targetCount = (nums1.size + nums2.size + 1) / 2
        while (l + 1 != r) {
            val m = l + (r - l) / 2
            val mCount = countLessEqual(m)
            if (mCount < targetCount) {
                l = m
            } else {
                r = m
                rCount = mCount
            }
        }
        
        return if ((nums1.size + nums2.size) % 2 == 1 || rCount > targetCount) {
            r.toDouble()
        } else {
            val id1 = upperBound(nums1, r)
            val id2 = upperBound(nums2, r)
            val other = if (id1 == nums1.size) {
                nums2[id2]
            } else if (id2 == nums2.size) {
                nums1[id1]
            } else {
                minOf(nums1[id1], nums2[id2])
            }
            (r + other) / 2.0
        }
    }
}
