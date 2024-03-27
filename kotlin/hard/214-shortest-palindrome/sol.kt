// https://leetcode.com/problems/shortest-palindrome/

class Solution {
    
    companion object {
        const val HASH_BASE = 31
        const val HASH_MOD = 50000017
        const val HASH_BASE_MULT_INVERSE = 14516134L
    }
    
    private fun Int.expandFactor(): Int = (HASH_BASE * this) % HASH_MOD
    
    private fun Char.coef(): Int = this - 'a' + 1
    
    private fun Int.expandLeftHash(added: Char):Int
        = (HASH_BASE * this + added.coef()) % HASH_MOD
    
    private fun Int.expandRightHash(added: Char, factor: Int): Int
        = (this + factor * added.coef()) % HASH_MOD
    
    private fun Int.shrinkRightHash(removed: Char): Int
        = ((HASH_BASE_MULT_INVERSE * (this - removed.coef())) % HASH_MOD).toInt()
    
    private fun String.telescopingEquality(leftStart: Int, rightStart: Int): Boolean {
        for (offset in 0 .. leftStart) {
            if (get(leftStart - offset) != get(rightStart + offset)) return false
        }
        return true
    }
    
    fun shortestPalindrome(s: String): String {
        if (s.isEmpty()) return ""
        
        var leftHash = 0 
        var rightHash = 0
        var factor = 1
        var len = 0
        var palindromeLen = 1
        while (2 * (len + 1) <= s.length) {
            ++len
            leftHash = leftHash.expandLeftHash(s[len - 1])
            rightHash = rightHash.expandRightHash(s[2 * len - 1], factor)
            if (leftHash == rightHash && s.telescopingEquality(len - 1, len)) {
                palindromeLen = 2 * len
            }
            
            if (2 * len + 1 <= s.length) {
                rightHash = rightHash.shrinkRightHash(s[len])
                rightHash = rightHash.expandRightHash(s[2 * len], factor)
                if (leftHash == rightHash && s.telescopingEquality(len - 1, len + 1)) {
                    palindromeLen = 2 * len + 1
                }
            }
            
            factor = factor.expandFactor()
        }
        return StringBuilder(s.substring(palindromeLen).reversed()).append(s).toString()
    }
}
