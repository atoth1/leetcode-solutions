// https://leetcode.com/problems/jump-game-iv/

class Solution {
    fun minJumps(arr: IntArray): Int {
        val equalValue = mutableMapOf<Int, MutableSet<Int>>();
        for (pos in 0 until arr.size) {
            equalValue[arr[pos]]?.let {
                it.add(pos)
                true
            } ?: run { equalValue[arr[pos]] = mutableSetOf(pos) }
        }
        
        val visited = BooleanArray(arr.size)
        visited[0] = true
        var curr = mutableListOf(0)
        var next = mutableListOf<Int>()
        var count = 0
        while (true) {
            for (currId in curr) {
                if (currId == arr.size - 1) return count
                
                if (currId  > 0 && !visited[currId - 1]) {
                    next.add(currId - 1)
                    visited[currId - 1] = true
                }
                
                if (!visited[currId + 1]) {
                    next.add(currId + 1)
                    visited[currId + 1] = true
                }
                
                for (nextId in equalValue[arr[currId]]!!) {
                    if (!visited[nextId]) {
                        next.add(nextId)
                        visited[nextId] = true
                    }
                }
                // Never need to iterate through this set again.
                equalValue[arr[currId]]!!.clear()
            }
            ++count
            curr = next.also { next = curr }
            next.clear()
        }
        // Unreachable
        return -1
    }
}
