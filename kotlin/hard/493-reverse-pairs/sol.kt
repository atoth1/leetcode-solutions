// https://leetcode.com/problems/reverse-pairs/

data class Interval(val begin: Long, val end: Long) {
    val length: Long
        get() = end - begin
    
    val mid: Long
        get() = begin + length / 2
}

private fun IntArray.bounds(): Interval {
    var min = Int.MAX_VALUE
    var max = Int.MIN_VALUE
    for (num in this) {
        min = minOf(min, num)
        max = maxOf(max, num)
    }
    return Interval(min.toLong(), max.toLong() + 1)
}

private class Node(val bounds: Interval) {
    var left: Node? = null
    var right: Node? = null
    private var _count: Int = 0
    val count: Int
        get() = _count
    
    fun increment(value: Int) {
        ++_count
        if (bounds.length > 1) {
            if (value < bounds.mid) {
                if (left == null) left = Node(Interval(bounds.begin, bounds.mid))
                left?.increment(value)
            } else {
                if (right == null) right = Node(Interval(bounds.mid, bounds.end))
                right?.increment(value)
            }
        }
    }
    
    fun query(interval: Interval): Int {
        return if (interval == bounds) {
            count
        } else if (interval.end <= bounds.mid) {
            left?.query(interval) ?: 0
        } else if (interval.begin >= bounds.mid) {
            right?.query(interval) ?: 0
        } else {
            val leftPortion = Interval(interval.begin, bounds.mid)
            val rightPortion = Interval(bounds.mid, interval.end)
            (left?.query(leftPortion) ?: 0) + (right?.query(rightPortion) ?: 0)
        }
    }
}

class SegmentTree(bounds: Interval) {
    
    private val root: Node = Node(bounds)
    
    fun increment(value: Int) {
        if (value >= root.bounds.begin && value < root.bounds.end) root.increment(value)
    }
    
    fun query(value: Int): Int {
        return if (value < root.bounds.begin) {
            0
        } else if (value >= root.bounds.end) {
            root.count
        } else {
            root.query(Interval(root.bounds.begin, value.toLong() + 1))
        }
    }
}

class Solution {
    fun reversePairs(nums: IntArray): Int {
        val tree = SegmentTree(nums.bounds())
        var count = 0
        for (id in nums.size - 1 downTo 0) {
            val queryValue = (nums[id].toLong() - 1).floorDiv(2).toInt()
            count += tree.query(queryValue)
            tree.increment(nums[id])
        }
        return count
    }
}
