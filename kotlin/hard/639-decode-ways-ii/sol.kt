// https://leetcode.com/problems/decode-ways-ii/

class Solution {
    
    companion object {
        const val MOD = 1000000007

        private infix fun Int.safePlus(other: Int): Int = ((this + other) % MOD).toInt()
    
        private infix fun Int.safeTimes(other: Int): Int = ((toLong() * other) % MOD).toInt()
    
        private fun String.oneCharDecodingCount(
            pos: Int,
            isContinuationChar: Boolean = false,
            bound: Char = '9'
        ): Int {
            return if (pos < 0 || pos >= length) {
                0
            } else when (get(pos)) {
                '*' -> bound - '0'
                in (if (isContinuationChar) '0' else '1') .. minOf(bound, '9') -> 1
                else -> 0
            }
        }
        
        private fun String.twoCharDecodingCount(pos: Int): Int {
            return if (pos < 0 || pos + 1 >= length) {
                0
            } else when (get(pos)) {
                '*' -> oneCharDecodingCount(pos + 1, true) + oneCharDecodingCount(pos + 1, true, '6')
                '1' -> oneCharDecodingCount(pos + 1, true)
                '2' -> oneCharDecodingCount(pos + 1, true, '6')
                else -> 0
            }
        }
    }
    
    private fun impl(s: String, pos: Int, cache: MutableMap<Int, Int>): Int {
        return if (pos == s.length) {
            1
        } else if (pos < 0 || pos > s.length) {
            0
        } else cache.getOrPut(pos) {
            (s.oneCharDecodingCount(pos) safeTimes impl(s, pos + 1, cache)) safePlus
                (s.twoCharDecodingCount(pos) safeTimes impl(s, pos + 2, cache))
        }
    }
    
    fun numDecodings(s: String): Int {
        return impl(s, 0, mutableMapOf())
    }
}
