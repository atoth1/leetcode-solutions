// https://leetcode.com/problems/longest-duplicate-substring/

class Solution {
    
    companion object {
        // Largest prime such that extendHash can't overflow
        const val MOD = 82595327
    }
    
    private fun extendHash(current: Int, added: Int): Int {
        return (26 * current + added) % MOD
    }
    
    private fun shrinkHash(current: Int, removed: Int, factor: Int): Int {
        var hash = current - removed * factor
        while (hash < 0) hash += MOD
        return hash
    }
    
    private data class Extents(val begin: Int, val end: Int)
    
    private fun String.substring(extents: Extents): String {
        return substring(extents.begin, extents.end)
    }
    
    private fun containsMatch(s: String, extents: Extents, pastExtents: List<Extents>): Boolean {
        val len = extents.end - extents.begin
        for (past in pastExtents) {
            var allMatch = true
            for (offset in 0 until len) {
                if (s[extents.begin + offset] != s[past.begin + offset]) {
                    allMatch = false
                    break
                }
            }
            if (allMatch) return true
        }
        return false
    }
    
    private fun getLengthKRepeat(s: String, k: Int): Extents? {
        var hash = 0
        for (id in 0 until k) {
            hash = extendHash(hash, s[id] - 'a')
        }
        
        var factor = 1
        repeat(k - 1) {
            factor = (factor * 26) % MOD
        }
        
        val hashToStr = mutableMapOf(hash to mutableListOf(Extents(0, k)))
        for (id in k until s.length) {
            val extents = Extents(id - k + 1, id + 1)
            hash = shrinkHash(hash, s[id - k] - 'a', factor)
            hash = extendHash(hash, s[id] - 'a')
            var matchFound = false
            hashToStr[hash]?.let { matchFound = containsMatch(s, extents, it) }
            if (matchFound) return extents
            hashToStr[hash] = hashToStr[hash]?.let {
                it.add(extents)
                it
            } ?: mutableListOf(extents)
        }
        return null
    }
    
    private fun binarySearch(s: String): String {
        var l = 0
        var r = s.length
        var extents: Extents? = null
        while (l + 1 != r) {
            val m = (l + r)/2
            getLengthKRepeat(s, m)?.let {
                extents = it
                l = m
            } ?: run {
                r = m
            }
        }
        return extents?.let { s.substring(it) } ?: ""
    }
    
    fun longestDupSubstring(s: String): String {
        return binarySearch(s)
    }
}