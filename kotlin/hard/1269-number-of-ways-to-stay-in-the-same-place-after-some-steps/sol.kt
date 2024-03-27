// https://leetcode.com/problems/number-of-ways-to-stay-in-the-same-place-after-some-steps/

class Solution {
    
    private fun modAdd(x: Int, y: Int): Int {
        val MOD = 1000000007
        return (x + y) % MOD
    }
    
    private fun IntArray.assign(num: Int) {
        for (id in 0 until size) {
            set(id, num)
        }
    }
    
    fun numWays(steps: Int, arrLen: Int): Int {
        if (arrLen == 1) return 1
        
        val bound = minOf(arrLen, 1 + steps / 2)
        var curr = IntArray(bound)
        curr[0] = 1
        var next = IntArray(bound)
        repeat (steps) {
            next[0] = modAdd(curr[0], curr[1])
            next[bound - 1] = modAdd(curr[bound - 2], curr[bound - 1])
            for (id in 1 until bound - 1) {
                next[id] = modAdd(modAdd(curr[id - 1], curr[id]), curr[id + 1])
            }
            curr = next.also { next = curr }
            next.assign(0)
        }
        return curr[0]
    }
}
