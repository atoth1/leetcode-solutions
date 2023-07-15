// https://leetcode.com/problems/minimum-degree-of-a-connected-trio-in-a-graph

private data class Node(val id: Int, val neighbors: MutableList<Node> = mutableListOf())

private fun makeGraph(n: Int, edges: Array<IntArray>): Array<Node> {
    val graph = Array(n) { Node(it) }
    for (edge in edges) {
        graph[edge[0] - 1].neighbors.add(graph[edge[1] - 1])
        graph[edge[1] - 1].neighbors.add(graph[edge[0] - 1])
    }
    return graph
}

private fun getTrios(graph: Array<Node>): List<List<Node>> {
    var curr = graph.map { mutableListOf(it) }
    repeat(2) {
        val next = mutableListOf<MutableList<Node>>()
        for (path in curr) {
            val end = path.last()
            for (neighbor in end.neighbors) {
                if (neighbor.id > end.id) {
                    next.add(path.toMutableList().apply { add(neighbor) })
                }
            }
        }
        curr = next
    }
    return curr.filter { it[0].neighbors.contains(it[2]) }
}

private fun getDegree(trios: List<List<Node>>): Int {
    if (trios.isEmpty()) return -1
    
    var minDegree = Int.MAX_VALUE
    for (trio in trios) {
        var degree = 0
        repeat(3) {
            for (candidate in trio[it].neighbors) {
                if (!trio.contains(candidate)) {
                    ++degree
                }
            }            
        }
        minDegree = minOf(degree, minDegree)
    }
    return minDegree
}

class Solution {
    fun minTrioDegree(n: Int, edges: Array<IntArray>): Int {
        return getDegree(getTrios(makeGraph(n, edges)))
    }
}