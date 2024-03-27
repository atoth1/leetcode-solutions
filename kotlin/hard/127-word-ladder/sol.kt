// https://leetcode.com/problems/word-ladder/

private data class Node(
    val str: String,
    val neighbors: MutableList<Node> = mutableListOf(),
    var visited: Boolean = false
)

private const val WILDCARD = '*'

private fun String.wildcardedList(): List<String> {
    val strs = mutableListOf<String>()
    for (id in 0 until length) {
        val builder = StringBuilder()
        builder
            .append(substring(0, id))
            .append(WILDCARD)
            .append(substring(id + 1, length))
        strs.add(builder.toString())
    }
    return strs
}

private fun makeGraph(beginWord: String, words: Set<String>): Map<String, Node> {
    val graph = mutableMapOf<String, Node>()
    graph[beginWord] = Node(beginWord)
    
    val matchLookup = mutableMapOf<String, MutableList<String>>()
    for (wildcarded in beginWord.wildcardedList()) {
        matchLookup.getOrPut(wildcarded) { mutableListOf() }.add(beginWord)
    }
    
    for (word in words) {
        val thisNode = graph.getOrPut(word) { Node(word) }
        for (wildcarded in word.wildcardedList()) {
            val matches = matchLookup.getOrPut(wildcarded) { mutableListOf() }
            for (match in matches) {
                val otherNode = graph.getOrPut(match) { Node(match) }
                thisNode.neighbors.add(otherNode)
                otherNode.neighbors.add(thisNode)
            }
            matches.add(word)
        }
    }
    return graph
}

class Solution {
    fun ladderLength(beginWord: String, endWord: String, wordList: List<String>): Int {
        val wordSet = wordList.toMutableSet()
        wordSet.remove(beginWord)
        if (!wordList.contains(endWord)) return 0
        
        val graph = makeGraph(beginWord, wordSet)
        var curr = mutableListOf(graph[beginWord]!!)
        curr[0].visited = true
        var len = 1
        while (!curr.isEmpty()) {
            ++len
            val next = mutableListOf<Node>()
            for (node in curr) {
                for (neighbor in node.neighbors) {
                    if (!neighbor.visited) {
                        if (neighbor.str == endWord) {
                            return len
                        }
                        neighbor.visited = true
                        next.add(neighbor)
                    }
                }
            }
            curr = next
        }
        return 0
    }
}
