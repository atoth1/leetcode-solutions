// https://leetcode.com/problems/scramble-string/

class Solution {
    
    private data class IdRange(val begin: Int, val end: Int)

    private data class IdRangePair(val p1: IdRange, val p2: IdRange)

    
    private fun equalSubstrings(s1: String, s2: String, ranges: IdRangePair): Boolean {
        val rangeLen = ranges.p1.end - ranges.p1.begin
        for (offset in 0 until rangeLen) {
            if (s1[ranges.p1.begin + offset] != s2[ranges.p2.begin + offset]) return false
        }
        return true
    }
    
    private fun isScramble(
        s1: String,
        s2: String,
        ranges: IdRangePair,
        cache: MutableMap<IdRangePair, Boolean>
    ): Boolean {
        if (equalSubstrings(s1, s2, ranges)) {
            return true
        } else {
            val cachedVal = cache[ranges]
            if (cachedVal != null) return cachedVal
            
            val rangeLen = ranges.p1.end - ranges.p1.begin
            val counts1 = IntArray(26)
            val frontCounts2 = IntArray(26)
            val backCounts2 = IntArray(26)
            for (offset in 0 until rangeLen - 1) {
                ++counts1[s1[ranges.p1.begin + offset] - 'a']
                ++frontCounts2[s2[ranges.p2.begin + offset] - 'a']
                ++backCounts2[s2[ranges.p2.end - offset - 1] - 'a']
                
                val noSwapIds1 = IdRangePair(IdRange(ranges.p1.begin, ranges.p1.begin + offset + 1),
                                             IdRange(ranges.p2.begin, ranges.p2.begin + offset + 1))
                val noSwapIds2 = IdRangePair(IdRange(ranges.p1.begin + offset + 1, ranges.p1.end),
                                             IdRange(ranges.p2.begin + offset + 1, ranges.p2.end))
                if (counts1 contentEquals frontCounts2 &&
                        isScramble(s1, s2, noSwapIds1, cache) &&
                        isScramble(s1, s2, noSwapIds2, cache)) {
                    cache[ranges] = true
                    return true
                }
                
                val swapIds1 = IdRangePair(IdRange(ranges.p1.begin, ranges.p1.begin + offset + 1),
                                           IdRange(ranges.p2.end - offset - 1, ranges.p2.end))
                val swapIds2 = IdRangePair(IdRange(ranges.p1.begin + offset + 1, ranges.p1.end),
                                           IdRange(ranges.p2.begin, ranges.p2.end - offset - 1))
                if (counts1 contentEquals backCounts2 &&
                        isScramble(s1, s2, swapIds1, cache) &&
                        isScramble(s1, s2, swapIds2, cache)) {
                    cache[ranges] = true
                    return true
                }
            }
            cache[ranges] = false
            return false
        }
    }
    
    private fun String.charCounts(): IntArray {
        val counts = IntArray(26)
        for (c in this) {
            ++counts[c - 'a']
        }
        return counts
    }
    
    private fun equalCounts(s1: String, s2: String): Boolean {
        return if (s1.length == s2.length && s1.charCounts() contentEquals s2.charCounts()) {
            true
        } else {
            false
        }
    }
    
    fun isScramble(s1: String, s2: String): Boolean {
        return if (!equalCounts(s1, s2)) {
            false
        } else {
            val ranges = IdRangePair(IdRange(0, s1.length), IdRange(0, s2.length))
            val cache = mutableMapOf<IdRangePair, Boolean>()
            isScramble(s1, s2, ranges, cache)
        }
    }
}