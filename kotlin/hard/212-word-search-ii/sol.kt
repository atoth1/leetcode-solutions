// https://leetcode.com/problems/word-search-ii/

private data class Position(val row: Int, val col: Int)

private const val MAX_LEN = 10

private class TrieNode {
    
    private val children: MutableMap<Char, TrieNode> = mutableMapOf<Char, TrieNode>()
    
    fun insert(pos: Position, len: Int, board: Array<CharArray>, visited: MutableSet<Position>) {
        if (len < MAX_LEN && !visited.contains(pos)) {
            visited.add(pos)
            val child = children.getOrPut(board[pos.row][pos.col]) { TrieNode() }
            val m = board.size
            val n = board[0].size
            if (pos.row > 0) child.insert(Position(pos.row - 1, pos.col), len + 1, board, visited)
            if (pos.row < m - 1) child.insert(Position(pos.row + 1, pos.col), len + 1, board, visited)
            if (pos.col > 0) child.insert(Position(pos.row, pos.col - 1), len + 1, board, visited)
            if (pos.col < n - 1) child.insert(Position(pos.row, pos.col + 1), len + 1, board, visited)
            visited.remove(pos)
        }
    }
    
    fun contains(word: String, id: Int): Boolean {
        return if (id == word.length) {
            true
        } else {
            children[word[id]]?.contains(word, id + 1) ?: false
        }
    }
}

private class Trie {
    
    private val root = TrieNode()
    
    fun insert(pos: Position, board: Array<CharArray>) {
        val visited = mutableSetOf<Position>()
        root.insert(pos, 0, board, visited)
    }
    
    fun contains(word: String): Boolean {
        return root.contains(word, 0)
    }
}

private fun makeTrie(board: Array<CharArray>): Trie {
    val m = board.size
    val n = board[0].size
    val trie = Trie()
    for (row in 0 until m) {
        for (col in 0 until n) {
            trie.insert(Position(row, col), board)
        }
    }
    return trie
}

class Solution {
    fun findWords(board: Array<CharArray>, words: Array<String>): List<String> {
        val lookup = makeTrie(board)
        val ret = mutableListOf<String>()
        for (word in words) if (lookup.contains(word)) ret.add(word)
        return ret
    }
}
