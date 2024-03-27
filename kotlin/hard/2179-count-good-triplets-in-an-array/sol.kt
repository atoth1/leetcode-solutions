// https://leetcode.com/problems/count-good-triplets-in-an-array/


private class SegmentTree(val size: Int) {
    private data class Node(val lid: Int, val rid: Int) {
        val mid = lid + (rid - lid) / 2
        var value = 0
        var left: Node? = null
        var right: Node? = null
        
        init {
            if (rid - lid > 1) {
                left = Node(lid, mid)
                right = Node(mid, rid)
            }
        }
        
        fun incrementAt(id: Int) {
            if (id >= lid && id < rid) {
                ++value
                left?.incrementAt(id)
                right?.incrementAt(id)
            }
        }
        
        fun query(l: Int, r: Int): Int {
            return if (l == lid && r == rid) {
                value
            } else if (r <= mid) {
                left!!.query(l, r)
            } else if (l >= mid) {
                right!!.query(l, r)
            } else {
                left!!.query(l, mid) + right!!.query(mid, r)
            }
        }
        
        fun reset() {
            value = 0
            left?.reset()
            right?.reset()
        }
    }
    
    private val root = Node(0, size)
    
    fun incrementAt(id: Int) {
        root.incrementAt(id)
    }
    
    fun query(l: Int, r: Int): Int {
        // Should probably bounds check
        return if (l >= r) 0 else root.query(l, r)
    }
    
    fun reset() {
        root.reset()
    }
}

class Solution {
    fun goodTriplets(nums1: IntArray, nums2: IntArray): Long {
        val n = nums1.size
        val nums2IdLookup = IntArray(n)
        for (id in 0 until n) {
            nums2IdLookup[nums2[id]] = id
        }
        
        val preCount = IntArray(n)
        val idsInNums2 = SegmentTree(n)
        for (id in 0 until n) {
            val value = nums1[id]
            val idInNums2 = nums2IdLookup[value]
            idsInNums2.incrementAt(idInNums2)
            preCount[id] = idsInNums2.query(0, idInNums2)
        }
        
        val postCount = IntArray(n)
        idsInNums2.reset()
        for (id in n - 1 downTo 0) {
            val value = nums1[id]
            val idInNums2 = nums2IdLookup[value]
            idsInNums2.incrementAt(idInNums2)
            postCount[id] = idsInNums2.query(idInNums2 + 1, n)
        }
        
        var count = 0L
        for (id in 0 until n) {
            count += preCount[id].toLong() * postCount[id]
        }
        return count
    }
}
