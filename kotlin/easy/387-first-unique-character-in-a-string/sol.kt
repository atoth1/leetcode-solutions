// https://leetcode.com/problems/first-unique-character-in-a-string/

class Solution {
    fun firstUniqChar(s: String): Int {
        val firstOccurance = IntArray(26) { UNSET }
        s.forEachIndexed { id, c ->
            if (firstOccurance[c-'a'] == UNSET) {
                firstOccurance[c-'a'] = id
            } else {
                firstOccurance[c-'a'] = s.length
            }
        }
        
        var first = s.length
        firstOccurance.forEach { id ->
            if (id >= 0 && id < s.length) {
                if (id < first) first = id
            }
        }
        return if (first == s.length) UNSET else first
    }
    
    companion object {
        const val UNSET = -1
    }
}

