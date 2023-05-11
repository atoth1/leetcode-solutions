// https://leetcode.com/problems/checking-existence-of-edge-length-limited-paths/

class Solution {
    
    private data class SetNode(var parent: SetNode? = null, var rank: Int = 0)
    
    private fun SetNode.getRoot(): SetNode {
        var root = this
        while (root.parent != null) {
            root = root.parent!!
        }
        
        var node = this
        while (node.parent != null) {
            val tmp = node.parent!!
            node.parent = root
            node = tmp
        }
        return root
    }
    
    private infix fun SetNode.join(other: SetNode) {
        var x = getRoot()
        var y = other.getRoot()
        if (x !== y) {
            if (x.rank < y.rank) x = y.also { y = x }
            if (x.rank == y.rank) ++x.rank
            y.parent = x
        }
    }
    
    private infix fun SetNode.inSameSetAs(other: SetNode): Boolean {
        return getRoot() === other.getRoot()
    }
    
    fun distanceLimitedPathsExist(n: Int, edgeList: Array<IntArray>, queries: Array<IntArray>): BooleanArray {
        edgeList.sortBy { it[2] }
        val ids = Array(queries.size) { it }
        ids.sortBy { queries[it][2] }
        
        val nodes = Array(n) { SetNode() }
        val ret = BooleanArray(queries.size)
        var edgeId = 0
        for (queryId in ids) {
            val query = queries[queryId]
            while (edgeId < edgeList.size && edgeList[edgeId][2] < query[2]) {
                var edge = edgeList[edgeId]
                nodes[edge[0]] join nodes[edge[1]]
                ++edgeId
            }
            if (nodes[query[0]] inSameSetAs nodes[query[1]]) {
                ret[queryId] = true
            }
        }
        return ret
    }
}
