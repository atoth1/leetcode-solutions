// https://leetcode.com/problems/count-all-possible-routes/

import kotlin.math.abs

private const val MOD = 1000000007

class Solution {
    
    private data class Route(val start: Int, val finish: Int, val fuel: Int)
    
    private fun impl(locations: IntArray, route: Route, cache: MutableMap<Route, Int>): Int {
        return if (route.fuel <= 0) 0 else cache.getOrPut(route) {
            var ways = if (
                route.start != route.finish &&
                route.fuel >= abs(locations[route.start] - locations[route.finish])
            ) {
                1
            } else {
                0
            }
            
            for (id in 0 until locations.size) {
                if (id != route.start) {
                    val requiredFuel = abs(locations[route.start] - locations[id])
                    val nextRoute = Route(id, route.finish, route.fuel - requiredFuel)
                    ways = (ways + impl(locations, nextRoute, cache)) % MOD
                }
            }
            
            // Same number of ways to start -> finish as finish -> start
            cache[route] = ways
            if (route.start != route.finish) {
                cache[Route(route.finish, route.start, route.fuel)] = ways
            }
            ways
        }
    }
    
    fun countRoutes(locations: IntArray, start: Int, finish: Int, fuel: Int): Int {
        val ways = impl(locations, Route(start, finish, fuel), mutableMapOf())
        return if (start != finish) ways else ways + 1
    }
}
