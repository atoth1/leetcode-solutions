// https://leetcode.com/problems/reachable-nodes-in-subdivided-graph/

import java.util.PriorityQueue

class Solution {
    
    private data class EdgeSubdivision(val count: Int, var unvisitedCount: Int)
    
    private data class Edge(val toId: Int, val subdivision: EdgeSubdivision)
    
    private data class Node(
        val edges: MutableList<Edge> = mutableListOf(),
        var visited: Boolean = false
    )
    
    private fun makeGraph(n: Int, edges: Array<IntArray>): Array<Node> {
        val graph = Array(n) { Node() }
        for ((id1, id2, count) in edges) {
            val subdivision = EdgeSubdivision(count, count)
            graph[id1].edges.add(Edge(id2, subdivision))
            graph[id2].edges.add(Edge(id1, subdivision))
        }
        return graph
    }
    
    private data class PathTerminus(val id: Int, val remainingMoves: Int)
    
    fun reachableNodes(edges: Array<IntArray>, maxMoves: Int, n: Int): Int {
        val graph = makeGraph(n, edges)
        val queue = PriorityQueue<PathTerminus> { x, y -> y.remainingMoves - x.remainingMoves }
        queue.add(PathTerminus(0, maxMoves))
        var count = 0
        while (!queue.isEmpty()) {
            val (id, remainingMoves) = queue.poll()
            if (!graph[id].visited) {
                ++count
                graph[id].visited = true
                
                for ((toId, subdivision) in graph[id].edges) {
                    val subdivisionNodesVisited = minOf(remainingMoves, subdivision.unvisitedCount)
                    count += subdivisionNodesVisited
                    subdivision.unvisitedCount -= subdivisionNodesVisited
                    
                    if (remainingMoves > subdivision.count) {
                        queue.add(PathTerminus(toId, remainingMoves - subdivision.count - 1))
                    }
                }
            }
        }
        return count
    }
}
