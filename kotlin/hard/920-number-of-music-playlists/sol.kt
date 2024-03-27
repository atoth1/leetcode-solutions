// https://leetcode.com/problems/number-of-music-playlists/

private const val MOD = 1000000007

private infix fun Int.modPlus(other: Int): Int {
    return ((toLong() + other) % MOD).toInt()
}

private infix fun Int.modTimes(other: Int): Int {
    return ((toLong() * other) % MOD).toInt()
}

class Solution {
    
    private data class State(val len: Int, val unique: Int)
    
    private fun impl(n: Int, k: Int, state: State, cache: MutableMap<State, Int>): Int {
        return if (state.len == 0 && state.unique == 0) {
            1
        } else if (state.unique == 0 || state.len < state.unique) {
            0
        } else {
            cache.getOrPut(state) {
                var ret = (n - state.unique + 1) modTimes impl(n, k, State(state.len - 1, state.unique - 1), cache)
                if (state.unique > k) {
                    ret = ret modPlus ((state.unique - k) modTimes impl(n, k, State(state.len - 1, state.unique), cache))
                }
                ret
            }
        }
    }
    
    fun numMusicPlaylists(n: Int, goal: Int, k: Int): Int {
        return impl(n, k, State(goal, n), mutableMapOf<State, Int>())
    }
}
