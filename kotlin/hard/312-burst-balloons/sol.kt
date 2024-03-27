// https://leetcode.com/problems/burst-balloons/

class Solution {
    
    private data class State(val left: Int, val right: Int)
    
    private fun impl(nums: IntArray, state: State, cache: MutableMap<State, Int>): Int {
        return if (state.left > state.right) {
            0
        } else cache.getOrPut(state) {
            with (state) {
                var ret = 0
                for (id in left .. right) {
                    val candidate = nums[left - 1] * nums[id] * nums[right + 1] +
                        impl(nums, State(left, id - 1), cache) +
                        impl(nums, State(id + 1, right), cache)
                    ret = maxOf(ret, candidate)
                }
                ret
            }
        }
    }
    
    fun maxCoins(nums: IntArray): Int {
        val paddedNums = IntArray(nums.size + 2) { id ->
            if (id == 0 || id == nums.size + 1) {
                1
            } else {
                nums[id - 1]
            }
        }
        return impl(paddedNums, State(1, paddedNums.size - 2), mutableMapOf())
    }
}
