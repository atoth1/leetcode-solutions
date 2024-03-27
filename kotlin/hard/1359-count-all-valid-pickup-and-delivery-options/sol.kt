// https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/

const val MOD = 1000000007

private data class State(val active: Int, val remaining: Int)

private val baseState = State(0, 0)

private infix fun Int.safeTimes(other: Int): Int {
    return ((toLong() * other) % MOD).toInt()
}

private fun impl(state: State, cache: MutableMap<State, Int>): Int {
    if (state == baseState) return 1
    return cache.getOrPut(state) {
        var ret = 0
        if (state.active > 0) {
            val newState = State(state.active - 1, state.remaining)
            ret = (ret + (state.active safeTimes impl(newState, cache))) % MOD
        }
        if (state.remaining > 0) {
            val newState = State(state.active + 1, state.remaining - 1)
            ret = (ret + (state.remaining safeTimes impl(newState, cache))) % MOD
        }
        ret
    }
}

class Solution {
    fun countOrders(n: Int): Int {
        return impl(State(0, n), mutableMapOf())
    }
}
