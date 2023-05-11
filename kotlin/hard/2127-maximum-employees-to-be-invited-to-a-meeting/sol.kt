// https://leetcode.com/problems/maximum-employees-to-be-invited-to-a-meeting/

import java.util.LinkedList

class Solution {
    
    private data class Node(
        val children: LinkedList<Node> = LinkedList<Node>()
    )
    
    private fun makeGraph(values: IntArray): Array<Node> {
        val nodes = Array(values.size) { Node() }
        for (id in 0 until values.size) {
            nodes[values[id]].children.add(nodes[id])
        }
        return nodes
    }
    
    private fun findCycleIds(values: IntArray): List<Int> {
        val visited = BooleanArray(values.size)
        val ids = mutableListOf<Int>()
        for (id in 0 until values.size) {
            var curr = id
            val seen = mutableSetOf<Int>()
            while (!visited[curr]) {
                visited[curr] = true
                seen.add(curr)
                val next = values[curr]
                if (seen.contains(next)) ids.add(next)
                curr = next
            }
        }
        return ids
    }
    
    private data class ProcessResult(
        val pairs: List<Pair<Int, Int>>,
        val maxCycleLen: Int
    )
    
    private fun processCycleIds(
        values: IntArray,
        startIds: List<Int>
    ): ProcessResult {
        val pairs = mutableListOf<Pair<Int, Int>>()
        var maxLen = 0
        for (startId in startIds) {
            var len = 0
            var curr = startId
            do {
                ++len
                curr = values[curr]
            } while (curr != startId)
            if (len == 2) {
                pairs.add(Pair(curr, values[curr]))
            }
            maxLen = maxOf(len, maxLen)
        }
        return ProcessResult(pairs, maxLen)
    }
    
    private fun breakCycle(first: Node, second: Node) {
        val firstIter = first.children.listIterator()
        while (firstIter.hasNext()) {
            if (firstIter.next() === second) {
                firstIter.remove()
            }
        }
        
        val secondIter = second.children.listIterator()
        while (secondIter.hasNext()) {
            if (secondIter.next() === first) {
                secondIter.remove()
            }
        }
    }
    
    private fun depth(node: Node): Int {
        var childrenDepth = 0
        for (child in node.children) {
            childrenDepth = maxOf(childrenDepth, depth(child))
        }
        return childrenDepth + 1
    }
    
    private fun solve(
        graph: Array<Node>,
        cycleInfo: ProcessResult
    ): Int {
        var sum = 0
        for (pair in cycleInfo.pairs) {
            breakCycle(graph[pair.first], graph[pair.second])
            sum += depth(graph[pair.first])
            sum += depth(graph[pair.second])
        }
        return maxOf(sum, cycleInfo.maxCycleLen)
    }
    
    fun maximumInvitations(favorite: IntArray): Int {
        val graph = makeGraph(favorite)
        val cycleIds = findCycleIds(favorite)
        val cycleInfo = processCycleIds(favorite, cycleIds)
        return solve(graph, cycleInfo)
    }
}