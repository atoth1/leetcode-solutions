// https://leetcode.com/problems/smallest-rotation-with-highest-score/

private class IntervalTree(nums: IntArray) {
    
    private data class Interval(val l: Int, val r: Int)
    
    private data class Node(
        val interval: Interval,
        var left: Node? = null,
        var right: Node? = null
    ) {
        // interval midpoint
        val mid = interval.l + (interval.r - interval.l) / 2
        
        // Begin and end points for intervals which contain mid
        val beginPts = mutableListOf<Int>()
        val endPts = mutableListOf<Int>()
        
        fun insert(newInterval: Interval) {
            if (newInterval.r < mid) {
                if (left == null) left = Node(Interval(interval.l, mid - 1))
                left?.insert(newInterval)
            } else if (newInterval.l > mid) {
                if (right == null) right = Node(Interval(mid + 1, interval.r))
                right?.insert(newInterval)
            } else {
                beginPts.add(newInterval.l)
                endPts.add(newInterval.r)
            }
        }
        
        fun completeInsertions() {
            beginPts.sort()
            endPts.sortDescending()
            left?.completeInsertions()
            right?.completeInsertions()
        }
        
        private fun List<Int>.upperBound(target: Int, comp: Comparator<Int>): Int {
            if (isEmpty() || comp.compare(get(0), target) > 0) return 0
            if (comp.compare(get(size - 1), target) <= 0) return size
            
            var l = 0
            var r = size - 1
            while (l + 1 != r) {
                val m = (l + r) / 2
                if (comp.compare(get(m), target) <= 0) {
                    l = m
                } else {
                    r = m
                }
            }
            return r
        }
        
        fun query(pt: Int): Int {
            return if (pt < interval.l || pt > interval.r) {
                0
            } else if (pt < mid) {
                var count = left?.query(pt) ?: 0
                count += beginPts.upperBound(pt, Comparator<Int> { l, r -> l - r })
                count
            } else if (pt > mid) {
                var count = right?.query(pt) ?: 0
                count += endPts.upperBound(pt, Comparator<Int> { l, r -> r - l })
                count
            } else {
                beginPts.size
            }
        }
    }
    
    private val size = nums.size
    
    private var root = Node(Interval(0, size - 1))
    
    init {
        nums.forEachIndexed { id, num ->
            if (num <= id) {
                val candidate1 = Interval(0, id - num)
                root.insert(candidate1)
            }
            if (id < size - 1) {
                val candidate2 = Interval(id + 1, minOf(size + id - num, size - 1))
                root.insert(candidate2)
            }
        }
        root.completeInsertions()
    }
    
    fun query(value: Int): Int {
        return root.query(value)
    }
    
    fun queryMax(): Int {
        var max = -1
        var maxScore = 0
        for (rotation in 0 until size) {
            val candidate = query(rotation)
            if (candidate > maxScore) {
                max = rotation
                maxScore = candidate
            }
        }
        return max
    }
}

class Solution {
    fun bestRotation(nums: IntArray): Int {
        val tree = IntervalTree(nums)
        return tree.queryMax()
    }
}
