//https://leetcode.com/problems/number-of-ways-to-form-a-target-string-given-a-dictionary/

class Solution {
    
    companion object {
        const val NCHAR = 26
        const val MOD = 1000000007
    }
    
    private data class Positions(val wordsPos: Int, val targetPos: Int)
    
    private fun makeLookup(words: Array<String>): Array<IntArray> {
        val n = words[0].length
        val ret = Array(n) { IntArray(NCHAR) }
        for (word in words) {
            for (pos in 0 until n) {
                ++ret[pos][word[pos] - 'a']
            }
        }
        return ret
    }
    
    private fun impl(
        lookup: Array<IntArray>,
        target: String,
        positions: Positions,
        cache: MutableMap<Positions, Int>
    ): Int {
        val available = lookup.size - positions.wordsPos
        val required = target.length - positions.targetPos
        return if (required == 0) {
            1
        } else if (required > available) {
            0
        } else {
            cache[positions] ?: run {
                var ret = ((lookup[positions.wordsPos][target[positions.targetPos] - 'a'].toLong() *
                    impl(lookup, target, Positions(positions.wordsPos + 1, positions.targetPos + 1), cache)) % MOD).toInt()
                ret = (ret + impl(lookup, target, Positions(positions.wordsPos + 1, positions.targetPos), cache)) % MOD
                cache[positions] = ret
                ret
            }
        }
    }
    
    fun numWays(words: Array<String>, target: String): Int {
        return impl(makeLookup(words), target, Positions(0, 0), mutableMapOf<Positions, Int>())
    }
}