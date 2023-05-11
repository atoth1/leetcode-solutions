// https://leetcode.com/problems/longest-cycle-in-a-graph/

class Solution {
    
    enum class Status { UNVISITED, TENTATIVE, VISITED }
    
    private fun dfs(
        id: Int,
        edges: IntArray,
        status: Array<Status>,
        cycleStartIds: MutableList<Int>
    ) {
        if (status[id] == Status.UNVISITED) {
            status[id] = Status.TENTATIVE
            if (edges[id] != -1) dfs(edges[id], edges, status, cycleStartIds)
            status[id] = Status.VISITED
        } else if (status[id] == Status.TENTATIVE) {
            cycleStartIds.add(id)
        }
    }
    
    private fun maxLength(edges: IntArray, cycleStartIds: List<Int>): Int {
        var max = -1
        for (startId in cycleStartIds) {
            var len = 0
            var id = startId
            do {
                ++len
                id = edges[id]
            } while (id != startId)
            max = maxOf(max, len)
        }
        return max
    }
    
    fun longestCycle(edges: IntArray): Int {
        val status = Array(edges.size) { Status.UNVISITED }
        val cycleStartIds = mutableListOf<Int>()
        for (id in 0 until edges.size) dfs(id, edges, status, cycleStartIds)
        return maxLength(edges, cycleStartIds)
    }
}
