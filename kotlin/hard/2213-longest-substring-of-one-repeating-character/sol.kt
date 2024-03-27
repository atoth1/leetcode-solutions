// https://leetcode.com/problems/longest-substring-of-one-repeating-character/

import java.util.TreeMap
import java.util.TreeSet

class Solution {
    
    private fun TreeMap<Int, Int>.incrementCount(key: Int) {
        put(key, (get(key) ?: 0) + 1)
    }
    
    private fun TreeMap<Int, Int>.decrementCount(key: Int) {
        get(key)?.let { count ->
            if (count == 1) {
                remove(key)
            } else {
                put(key, count - 1)
            }
        }
    }
    
    private data class CharacterInterval(val c: Char, val begin: Int, val end: Int) {
        fun length(): Int = end - begin
    }
    
    private fun makeIntervalData(s: String): Pair<TreeSet<CharacterInterval>, TreeMap<Int, Int>> {
        val charIntervals = TreeSet<CharacterInterval> { x, y -> x.end - y.end }
        val lengthCounts = TreeMap<Int, Int>()
        var begin = 0
        while (begin < s.length) {
            var end = begin + 1
            while (end < s.length && s[begin] == s[end]) {
                ++end
            }
            charIntervals.add(CharacterInterval(s[begin], begin, end))
            lengthCounts.incrementCount(end - begin)
            begin = end
        }
        return Pair(charIntervals, lengthCounts)
    }
    
    fun longestRepeating(s: String, queryCharacters: String, queryIndices: IntArray): IntArray {
        val (charIntervals, lengthCounts) = makeIntervalData(s)
        
        val queryCount = queryCharacters.length
        val ret = IntArray(queryCount)
        for (queryId in 0 until queryCount) {
            var update = CharacterInterval(queryCharacters[queryId], queryIndices[queryId], queryIndices[queryId] + 1)
            val containingInterval = charIntervals.ceiling(update)
            if (update.c != containingInterval.c) {
                charIntervals.remove(containingInterval)
                lengthCounts.decrementCount(containingInterval.length())
                
                if (update.begin > containingInterval.begin) {
                    charIntervals.add(containingInterval.copy(end = update.begin))
                    lengthCounts.incrementCount(update.begin - containingInterval.begin)
                }
                
                if (update.end < containingInterval.end) {
                    charIntervals.add(containingInterval.copy(begin = update.end)) 
                    lengthCounts.incrementCount(containingInterval.end - update.end)
                }
                
                charIntervals.floor(update)?.let { leftInterval ->
                    if (update.c == leftInterval.c) {
                        charIntervals.remove(leftInterval)
                        lengthCounts.decrementCount(leftInterval.length())
                        update = update.copy(begin = leftInterval.begin)
                    }
                }
                
                charIntervals.ceiling(update)?.let { rightInterval ->
                    if (update.c == rightInterval.c) {
                        charIntervals.remove(rightInterval)
                        lengthCounts.decrementCount(rightInterval.length())
                        update = update.copy(end = rightInterval.end)
                    }
                }
                
                charIntervals.add(update)
                lengthCounts.incrementCount(update.length())
            }
            ret[queryId] = lengthCounts.lastKey()
        }
        return ret
    }
}
