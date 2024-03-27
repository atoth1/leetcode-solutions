// https://leetcode.com/problems/the-skyline-problem/

import java.util.PriorityQueue
import java.util.TreeMap

class Solution {
    
    private data class ActiveBuilding(val end: Int, val height: Int)
    
    fun getSkyline(buildings: Array<IntArray>): List<List<Int>> {
        val activeBuildings = PriorityQueue<ActiveBuilding> { x, y -> x.end - y.end }
        val activeHeightCounts = TreeMap<Int, Int>()
        
        val getNextCoord = { nextBuilding: Int ->
            val nextActivationCoord = if (nextBuilding < buildings.size) {
                buildings[nextBuilding][0]
            } else {
                Int.MAX_VALUE
            }
            val nextDeactivationCoord = if (!activeBuildings.isEmpty()) {
                activeBuildings.peek().end
            } else {
                Int.MAX_VALUE 
            }
            minOf(nextActivationCoord, nextDeactivationCoord)
        }
        
        val activateBuilding = { building: ActiveBuilding ->
            activeBuildings.add(building)
            activeHeightCounts[building.height] = 1 + (activeHeightCounts[building.height] ?: 0)
        }
        
        val deactivateBuilding = {
            val deactivated = activeBuildings.poll()
            val count = activeHeightCounts[deactivated.height]!!
            if (count == 1) {
                activeHeightCounts.remove(deactivated.height)
            } else {
                activeHeightCounts[deactivated.height] = count - 1
            }
        }
        
        val ret = mutableListOf<List<Int>>()
        var nextBuilding = 0
        while (nextBuilding < buildings.size || !activeBuildings.isEmpty()) {
            val nextCoord = getNextCoord(nextBuilding)
            
            while (!activeBuildings.isEmpty() && activeBuildings.peek().end == nextCoord) {
                deactivateBuilding()
            }
            
            while (nextBuilding < buildings.size && buildings[nextBuilding][0] == nextCoord) {
                activateBuilding(ActiveBuilding(buildings[nextBuilding][1], buildings[nextBuilding][2]))
                ++nextBuilding
            }
            
            val newHeight = if (activeHeightCounts.isEmpty()) 0 else activeHeightCounts.lastKey()
            if (ret.isEmpty() || newHeight != ret.last()[1]) {
                ret.add(listOf(nextCoord, newHeight))
            }
        }
        return ret
    }
}
