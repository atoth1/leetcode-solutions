// https://leetcode.com/problems/jump-game-v/

class Solution {
    fun maxJumps(arr: IntArray, d: Int): Int {
        val n = arr.size
        val sortedIds = IntArray(n) { it }.sortedBy { arr[it] }
        val sols = IntArray(n) { 1 }
        var max = 0
        for (id in sortedIds) {
            for (jump in 1 .. d) {
                if (id - jump < 0 || arr[id - jump] >= arr[id]) break
                sols[id] = maxOf(sols[id], 1 + sols[id - jump])
            }
            for (jump in 1 .. d) {
                if (id + jump >= n || arr[id + jump] >= arr[id]) break
                sols[id] = maxOf(sols[id], 1 + sols[id + jump])
            }
            max = maxOf(max, sols[id])
        }
        return max
    }
}
