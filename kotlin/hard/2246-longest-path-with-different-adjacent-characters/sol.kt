// https://leetcode.com/problems/longest-path-with-different-adjacent-characters/

import java.util.PriorityQueue

class Solution {
    
    private data class Node(val value: Char, val childIds: MutableList<Int> = mutableListOf())
    
    private fun makeTree(parent: IntArray, s: String): Array<Node> {
        val graph = Array(parent.size) { Node(s[it]) }
        parent.forEachIndexed { id, parentId ->
            if (parentId != -1) {
                graph[parentId].childIds.add(id)
            }
        }
        return graph
    }
    
    private data class IntWrapper(var value: Int)
    
    // Returns length of longest valid path from node at nodeId to a descendant
    private fun impl(nodeId: Int, tree: Array<Node>, max: IntWrapper): Int {
        val longest = PriorityQueue<Int>()
        for (childId in tree[nodeId].childIds) {
            val candidate = impl(childId, tree, max)
            if (tree[nodeId].value != tree[childId].value) {
                if (longest.size < 2) {
                    longest.add(candidate)
                } else if (candidate > longest.peek()) {
                    longest.poll()
                    longest.add(candidate)
                }
            }
        }
        
        var maxThroughChildren = 1
        var maxDepth = 1
        while (!longest.isEmpty()) {
            val depth = longest.poll()
            maxThroughChildren += depth
            maxDepth = 1 + depth
        }
        max.value = maxOf(max.value, maxThroughChildren)
        return maxDepth
    }
    
    fun longestPath(parent: IntArray, s: String): Int {
        val ret = IntWrapper(0)
        // Told id 0 is root node
        impl(0, makeTree(parent, s), ret)
        return ret.value
    }
}
