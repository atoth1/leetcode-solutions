// https://leetcode.com/problems/minimum-window-substring/

class Solution {
    
    private fun String.getCharCounts(): Map<Char, Int> {
        val counts = mutableMapOf<Char, Int>()
        for (c in this) {
            counts[c] = 1 + (counts[c] ?: 0)
        }
        return counts
    }
    
    private infix fun Map<Char, Int>.isSubsetOf(other: Map<Char, Int>): Boolean {
        for ((c, count) in this) {
            val otherCount = other[c]
            if (otherCount == null || count > otherCount) {
                return false
            }
        }
        return true
    }
    
    private fun expandToContain(
        s: String,
        currEndId: Int,
        currCounts: MutableMap<Char, Int>,
        targetCounts: Map<Char, Int>
    ): Int? {
        var newEndId = currEndId
        while (newEndId < s.length && !(targetCounts isSubsetOf currCounts)) {
            val c = s[newEndId]
            currCounts[c] = currCounts[c]?.plus(1) ?: 1
            ++newEndId
        }
        return if (targetCounts isSubsetOf currCounts) newEndId else null
    }
    
    private fun shrinkToFit(
        s: String,
        currBeginId: Int,
        currCounts: MutableMap<Char, Int>,
        targetCounts: Map<Char, Int>
    ): Int {
        var newBeginId = currBeginId
        while (targetCounts isSubsetOf currCounts) {
            val c = s[newBeginId]
            currCounts[c] = currCounts[c]?.minus(1) ?: 0
            ++newBeginId
        }
        return newBeginId
    }
    
    private data class Bounds(val begin: Int, val end: Int)
    
    fun minWindow(s: String, t: String): String {
        if (s.length < t.length) return ""
        
        val sCounts = mutableMapOf<Char, Int>()
        val tCounts = t.getCharCounts()
        var beginId = 0
        var endId = 0
        var optimalBounds: Bounds? = null
        while (endId < s.length) {
            expandToContain(s, endId, sCounts, tCounts)?.let { endId = it } ?: break
            beginId = shrinkToFit(s, beginId, sCounts, tCounts)
            if (optimalBounds == null || endId - beginId + 1 < optimalBounds.end - optimalBounds.begin) {
                optimalBounds = Bounds(beginId - 1, endId)
            }
        }
        return if (optimalBounds == null) "" else s.substring(optimalBounds.begin, optimalBounds.end)
    }
}
