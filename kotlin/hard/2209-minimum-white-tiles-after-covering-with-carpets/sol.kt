// https://leetcode.com/problems/minimum-white-tiles-after-covering-with-carpets/

class Solution {
    
    private fun String.getPostfixSums(): IntArray {
        val postfix = IntArray(length)
        var sum = 0
        for (id in length - 1 downTo 0) {
            sum += get(id) - '0'
            postfix[id] = sum
        }
        return postfix
    }
    
    private data class State(val id: Int, val remainingCarpets: Int)
    
    private fun impl(
        floor: String,
        postfix: IntArray,
        carpetLen: Int,
        state: State,
        cache: MutableMap<State, Int>
    ): Int {
        return if (state.id >= floor.length) {
            0
        } else if (state.remainingCarpets == 0) {
            postfix[state.id]
        } else cache.getOrPut(state) {
            val thisContrib = if (floor[state.id] == '0') 0 else 1
            val candidate1 =  State(state.id + 1, state.remainingCarpets)
            val candidate2 = State(state.id + carpetLen, state.remainingCarpets - 1)
            minOf(
                thisContrib + impl(floor, postfix, carpetLen, candidate1, cache),
                impl(floor, postfix, carpetLen, candidate2, cache)
            )
        }
    }
    
    fun minimumWhiteTiles(floor: String, numCarpets: Int, carpetLen: Int): Int {
        return if (numCarpets * carpetLen >= floor.length) {
            0
        } else {
            impl(floor, floor.getPostfixSums(), carpetLen, State(0, numCarpets), mutableMapOf())
        }
    }
}
