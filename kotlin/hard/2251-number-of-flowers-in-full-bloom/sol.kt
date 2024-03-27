// https://leetcode.com/problems/number-of-flowers-in-full-bloom/

private data class Interval(val begin: Int, val end: Int) {
    val length: Int
        get() = end - begin
    
    val mid: Int
        get() = begin + length / 2
}

private class Node(val bounds: Interval) {
    var left: Node? = null
    var right: Node? = null
    val beginPts: MutableList<Int> = mutableListOf()
    val endPts: MutableList<Int> = mutableListOf()
    
    fun insert(interval: Interval) {
        if (interval.end <= bounds.mid) {
            if (left == null) left = Node(Interval(bounds.begin, bounds.mid))
            left?.insert(interval)
            
        } else if (interval.begin > bounds.mid) {
            if (right == null) right = Node(Interval(bounds.mid + 1, bounds.end))
            right?.insert(interval)
            
        } else {
            beginPts.add(interval.begin)
            endPts.add(interval.end)
        }
    }
    
    fun completeInsertions() {
        beginPts.sort()
        endPts.sort()
        left?.completeInsertions()
        right?.completeInsertions()
    }
    
    private fun List<Int>.search(value: Int, pred: (Int, Int) -> Boolean): Int {
        if (isEmpty() || pred(value, get(0))) return 0
        
        var l = 0
        var r = size
        while (l + 1 != r) {
            val m = l + (r - l) / 2
            if (pred(value, get(m))) {
                r = m
            } else {
                l = m
            }
        }
        return r
    }
    
    private fun List<Int>.lowerBound(value: Int): Int {
        return search(value) { x, y -> x <= y }
    }
    
    private fun List<Int>.upperBound(value: Int): Int {
        return search(value) { x, y -> x < y }
    }
    
    fun query(pt: Int): Int {
        return if (pt < bounds.mid) {
            beginPts.upperBound(pt) + (left?.query(pt) ?: 0)
        } else if (pt > bounds.mid) {
            endPts.size - endPts.upperBound(pt) + (right?.query(pt) ?: 0)
        } else {
            beginPts.size
        }
    }
}

private class IntervalTree(intervals: Array<IntArray>) {
    lateinit var root: Node
    
    init {
        var begin = Int.MAX_VALUE
        var end = Int.MIN_VALUE
        for (interval in intervals) {
            begin = minOf(begin, interval[0])
            end = maxOf(end, interval[1])
        }
        root = Node(Interval(begin, end + 1))
        
        for (interval in intervals) {
            root.insert(Interval(interval[0], interval[1] + 1))
        }
        root.completeInsertions()
    }
    
    fun query(value: Int): Int {
        return if (value < root.bounds.begin || value >= root.bounds.end) 0 else root.query(value)
    }
}

class Solution {
    fun fullBloomFlowers(flowers: Array<IntArray>, people: IntArray): IntArray {
        val tree = IntervalTree(flowers)
        val ret = IntArray(people.size) { tree.query(people[it]) }
        return ret
    }
}
