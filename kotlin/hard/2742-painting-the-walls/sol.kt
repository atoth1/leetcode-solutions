// https://leetcode.com/problems/painting-the-walls/

private const val FAIL_VALUE = Int.MAX_VALUE / 2

private data class State(val pos: Int, val remaining: Int)

private fun impl(cost: IntArray, time: IntArray, state: State, cache: MutableMap<State, Int>): Int {
    val n = cost.size
    val (pos, remaining) = state
    return if (remaining <= 0) {
        0
    } else if (pos == n) {
        FAIL_VALUE
    } else {
        cache.getOrPut(state) {
            val includeState = State(pos + 1, remaining - time[pos] - 1)
            val skipState = State(pos + 1, remaining)
            minOf(cost[pos] + impl(cost, time, includeState, cache), impl(cost, time, skipState, cache))
        }
    }
}

class Solution {
    fun paintWalls(cost: IntArray, time: IntArray): Int {
        return impl(cost, time, State(0, cost.size), mutableMapOf<State, Int>())
    }
}
