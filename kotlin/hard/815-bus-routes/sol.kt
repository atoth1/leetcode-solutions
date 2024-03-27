// https://leetcode.com/problems/bus-routes/

class Solution {
    
    private data class Route(
        val stationIds: MutableSet<Int> = mutableSetOf(),
        val neighborRouteIds: MutableList<Int> = mutableListOf(),
        var visited: Boolean = false
    )
    
    private infix fun Route.isConnectedTo(other: Route): Boolean {
        for (stationId in stationIds) {
            if (other.stationIds.contains(stationId)) return true
        }
        return false
    }
    
    private fun makeGraph(routes: Array<IntArray>): Array<Route> {
        val n = routes.size
        val graph = Array(n) { Route() }
        for (routeId in 0 until n) {
            for (stationId in routes[routeId]) graph[routeId].stationIds.add(stationId)
        }
        
        for (routeId1 in 0 until n) {
            for (routeId2 in routeId1 + 1 until n) {
                if (graph[routeId1] isConnectedTo graph[routeId2]) {
                    graph[routeId1].neighborRouteIds.add(routeId2)
                    graph[routeId2].neighborRouteIds.add(routeId1)
                }
            }
        }
        return graph
    }
    
    private fun doBfs(source: Int, target: Int, graph: Array<Route>): Int {
        var curr = mutableListOf<Route>()
        for (route in graph) {
            if (route.stationIds.contains(source)) {
                curr.add(route)
                route.visited = true
            }
        }
        
        var count = 1
        while (!curr.isEmpty()) {
            val next = mutableListOf<Route>()
            for (route in curr) {
                if (route.stationIds.contains(target)) return count
                
                for (neighborId in route.neighborRouteIds) {
                    val candidate = graph[neighborId]
                    if (!candidate.visited) {
                        next.add(candidate)
                        candidate.visited = true
                    }
                }
            }
            
            curr = next
            ++count
        }
        return -1
    }
    
    fun numBusesToDestination(routes: Array<IntArray>, source: Int, target: Int): Int {
        return if (source == target) 0 else doBfs(source, target, makeGraph(routes))
    }
}
