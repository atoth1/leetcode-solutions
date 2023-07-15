// https://leetcode.com/problems/find-servers-that-handled-most-number-of-requests/

import java.util.TreeMap
import java.util.TreeSet

class Solution {
    fun busiestServers(k: Int, arrival: IntArray, load: IntArray): List<Int> {
        val n = arrival.size
        val availableIds = TreeSet((0 until k).toList())
        val busyIds = TreeMap<Int, MutableList<Int>>()
        val requestsHandled = IntArray(k)
        var maxHandled = 0
        for (requestId in 0 until n) {
            while (!busyIds.isEmpty() && busyIds.firstKey() <= arrival[requestId]) {
                availableIds.addAll(busyIds.pollFirstEntry().value)
            }
           
            if (!availableIds.isEmpty()) {
                val targetServer = requestId % k
                var respondingId = availableIds.ceiling(targetServer)
                if (respondingId == null) {
                    respondingId = availableIds.first()
                }
                respondingId?.let { id ->
                    ++requestsHandled[id]
                    maxHandled = maxOf(maxHandled, requestsHandled[id])
                    
                    availableIds.remove(id)
                    val freeTime = arrival[requestId] + load[requestId]
                    busyIds[freeTime]?.let { ids ->
                        ids.add(id)
                    } ?: run {
                        busyIds[freeTime] = mutableListOf(id)
                    }
                }
            }
        }
        
        val ret = mutableListOf<Int>()
        for (serverId in 0 until k) {
            if (requestsHandled[serverId] == maxHandled) ret.add(serverId)
        }
        return ret
    }
}