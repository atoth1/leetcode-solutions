// https://leetcode.com/problems/word-break-ii/

private class TrieNode {
    val children = mutableMapOf<Char, TrieNode>()
    
    var isTerminal = false
    
    fun insert(word: String, pos: Int) {
        if (pos == word.length) {
            isTerminal = true
        } else if (pos < word.length) {
            children.getOrPut(word[pos]) { TrieNode() }.insert(word, pos + 1)
        }
    }
    
    fun query(word: String, pos: Int, successLengths: MutableList<Int>) {
        if (isTerminal) {
            successLengths.add(pos)
        }
        
        if (pos < word.length) {
            children[word[pos]]?.query(word, pos + 1, successLengths)
        }
    }
}

private class Trie(words: List<String>) {
    private val root = TrieNode()
    
    init {
        for (word in words) {
            root.insert(word, 0)
        } 
    }
    
    fun query(word: String, successLengths: MutableList<Int>) {
        root.query(word, 0, successLengths)
    }
}

class Solution {
    fun wordBreak(s: String, wordDict: List<String>): List<String> {
        val lookup = Trie(wordDict)
        val dp = Array(s.length) { emptyList<String>() }
        for (pos in s.length - 1 downTo 0) {
            val validLengths = mutableListOf<Int>()
            lookup.query(s.substring(pos, s.length), validLengths)
            
            val validStrs = mutableListOf<String>()
            for (length in validLengths) {
                if (pos + length == s.length) {
                    validStrs.add(s.substring(pos, s.length))
                } else {
                    for (remainder in dp[pos + length]) {
                        val builder = StringBuilder()
                        builder.append(s.substring(pos, pos + length)).append(" ").append(remainder)
                        validStrs.add(builder.toString())
                    }
                }
            }
            dp[pos] = validStrs
        }
        return dp[0]
    }
}
