// https://leetcode.com/problems/count-of-range-sum/

import java.util.TreeMap

private fun IntArray.inclusiveScan(): LongArray {
    val prefix = LongArray(size)
    var sum = 0L
    for (id in 0 until size) {
        sum += get(id)
        prefix[id] = sum
    }
    return prefix
}

private data class IdRange(val begin: Int, val end: Int) {
    val size: Int
        get() = end - begin
    
    val mid: Int
        get() = begin + size / 2
    
    fun canSplit(): Boolean = size > 1
    
    fun split(): Pair<IdRange, IdRange> {
        return Pair(IdRange(begin, mid), IdRange(mid, end))
    }
    
    infix fun intersectsWith(other: IdRange): Boolean {
        return begin < other.end && other.begin < end
    }
    
    infix fun intersectionWith(other: IdRange): IdRange {
        return IdRange(maxOf(begin, other.begin), minOf(end, other.end))
    }
}

private class IdMapping(prefixes: LongArray) {
    private val idLookup = TreeMap<Long, Int>()
    
    val size: Int
        get() = idLookup.size
    
    init {
        // Always include prefix 0 for empty sum
        idLookup[0] = 0
        for (prefix in prefixes) {
            idLookup[prefix] = 0
        }
        
        var id = 0
        for ((prefix, _) in idLookup) {
            idLookup[prefix] = id++
        }
    }
    
    fun getPrefixId(prefix: Long): Int {
        return idLookup[prefix]!!
    }
    
    fun getBoundedIdRange(lowPrefix: Long, highPrefix: Long): IdRange? {
        val lowEntry = idLookup.ceilingEntry(lowPrefix)
        val highEntry = idLookup.floorEntry(highPrefix)
        return if (lowEntry != null && highEntry != null && lowEntry.value <= highEntry.value) {
            IdRange(lowEntry.value, highEntry.value + 1)
        } else {
            null
        }
    }
}

private class SegmentTree(range: IdRange) {
    private class Node(private val myRange: IdRange) {
        private var left: Node? = null
        
        private var right: Node? = null
        
        private var count: Int = 0
        
        init {
            if (myRange.canSplit()) {
                val (lRange, rRange) = myRange.split()
                left = Node(lRange)
                right = Node(rRange)
            }
        }
        
        fun increment(id: Int) {
            ++count
            if (myRange.canSplit()) {
                if (id < myRange.mid) {
                    left?.increment(id)
                } else {
                    right?.increment(id)
                }
            }
        }
        
        fun query(range: IdRange): Int {
            return if (range == myRange) {
                count
            } else {
                val (lRange, rRange) = myRange.split()
                val lCount = if (lRange intersectsWith range) left!!.query(lRange intersectionWith range) else 0 
                val rCount = if (rRange intersectsWith range) right!!.query(rRange intersectionWith range) else 0
                lCount + rCount
            }
        }
    }
    
    private val root = Node(range)
    
    fun increment(id: Int) {
        root.increment(id)
    }
    
    fun query(range: IdRange): Int {
        return root.query(range)
    }
}

class Solution {
    fun countRangeSum(nums: IntArray, lower: Int, upper: Int): Int {
        val prefixes = nums.inclusiveScan()
        val idLookup = IdMapping(prefixes)
        val countLookup = SegmentTree(IdRange(0, idLookup.size))
        // Include empty prefix sum
        countLookup.increment(idLookup.getPrefixId(0))
        var count = 0
        for (prefix in prefixes) {
            val prefixIdRange = idLookup.getBoundedIdRange(prefix - upper, prefix - lower)
            prefixIdRange?.let {
                count += countLookup.query(prefixIdRange)
            }
            countLookup.increment(idLookup.getPrefixId(prefix))
        }
        return count
    }
}
