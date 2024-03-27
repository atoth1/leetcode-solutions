// https://leetcode.com/problems/minimum-number-of-days-to-disconnect-island/

private data class Position(val row: Int, val col: Int)

private data class Node(val pos: Position) {
    var parent: Node? = null
    var rank: Int = 0
    val neighbors: MutableList<Node> = mutableListOf<Node>()
}

private fun Node.getRoot(): Node {
    var root = this
    while (root.parent != null) {
        root = root.parent!!
    }
    
    var node = this
    while (node.parent != null) {
        node = node.parent!!.also { node.parent = root }
    }
    return root
}

private fun Node.isRoot(): Boolean {
    return this === getRoot()
}

private infix fun Node.joinSets(other: Node) {
    var x = getRoot()
    var y = other.getRoot()
    if (x !== y) {
        if (x.rank < y.rank) x = y.also { y = x }
        if (x.rank == y.rank) ++x.rank
        y.parent = x
    }
}

private infix fun Node.makeNeighbors(other: Node) {
    neighbors.add(other)
    other.neighbors.add(this)
}

private fun makeGraph(grid: Array<IntArray>): Array<Array<Node?>> {
    val m = grid.size
    val n = grid[0].size
    val graph = Array(m) { Array<Node?>(n) { null } }
    for (row in 0 until m) {
        for (col in 0 until n) {
            if (grid[row][col] == 1) {
                val pos = Position(row, col)
                graph[row][col] = Node(pos = pos)
                graph[row][col]?.let { node ->
                    if (row > 0) {
                        graph[row - 1][col]?.let {
                            node joinSets it
                            node makeNeighbors it
                        }
                    }
                    if (col > 0) {
                        graph[row][col - 1]?.let {
                            node joinSets it
                            node makeNeighbors it
                        }
                    }
                }
            }
        }
    }
    return graph
}

private fun getLandCount(graph: Array<Array<Node?>>): Int {
    var count = 0
    for (row in graph) {
        for (node in row) {
            node?.let { ++count }
        }
    }
    return count
}

private fun getComponentCount(graph: Array<Array<Node?>>): Int {
    val roots = mutableSetOf<Node>()
    for (row in graph) {
        for (node in row) {
            node?.let { roots.add(it.getRoot()) }
        }
    }
    return roots.size
}

private fun Node.removalDisconnects(): Boolean {
    for (id1 in 0 until neighbors.size) {
        for (id2 in id1 + 1 until neighbors.size) {
            val visited = mutableSetOf(this)
            if (!doDfs(neighbors[id1], neighbors[id2], visited)) return true
        }
    }
    return false
}

private fun doDfs(curr: Node, target: Node, visited: MutableSet<Node>): Boolean {
    if (curr == target) return true
    
    visited.add(curr)
    for (neighbor in curr.neighbors) {
        if (!visited.contains(neighbor)) {
            if (doDfs(neighbor, target, visited)) return true
        }
    }
    return false
}

class Solution {
    fun minDays(grid: Array<IntArray>): Int {
        val m = grid.size
        val n = grid[0].size
        val graph = makeGraph(grid)
        if (getLandCount(graph) == 1) return 1
        if (getComponentCount(graph) != 1) return 0
        
        for (row in graph) {
            for (node in row) {
                if (node?.removalDisconnects() ?: false) return 1
            }
        }
        return 2
    }
}