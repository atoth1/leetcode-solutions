// https://leetcode.com/problems/path-with-maximum-probability/

import java.util.PriorityQueue

class Solution {
    
    private data class IdWithProb(val id: Int, val prob: Double = 1.0)
    
    private data class Edge(val toId: Int, val prob: Double)
    
    private data class Node(val edges: MutableList<Edge> = mutableListOf<Edge>())
    
    private fun makeGraph(n: Int, edges: Array<IntArray>, probs: DoubleArray): Array<Node> {
        val graph = Array(n) { Node() }
        for (id in 0 until edges.size) {
            graph[edges[id][0]].edges.add(Edge(edges[id][1], probs[id]))
            graph[edges[id][1]].edges.add(Edge(edges[id][0], probs[id]))
        }
        return graph
    }
    
    fun maxProbability(
        n: Int,
        edges: Array<IntArray>,
        probs: DoubleArray,
        start: Int,
        end: Int
    ): Double {
        if (start == end) return 1.0
        
        val graph = makeGraph(n, edges, probs)
        val queue = PriorityQueue { l: IdWithProb, r: IdWithProb ->
            if (l.prob > r.prob) -1 else if (l.prob < r.prob) 1 else 0
        }
        queue.add(IdWithProb(start))
        val visited = BooleanArray(n)
        
        while (!queue.isEmpty()) {
            val curr = queue.poll()
            if (curr.id == end) return curr.prob
            
            if (!visited[curr.id]) {
                visited[curr.id] = true
                for (edge in graph[curr.id].edges) {
                    if (!visited[edge.toId]) queue.add(IdWithProb(edge.toId, edge.prob * curr.prob))
                }
            }
        }
        return 0.0
    }
}
