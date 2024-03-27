// https://leetcode.com/problems/minimum-operations-to-make-a-subsequence/

import java.util.TreeMap

class Solution {
    
    private fun makeSurrogate(target: IntArray, arr: IntArray): List<Int> {
        val idLookup = mutableMapOf<Int, Int>()
        for (id in 0 until target.size) {
            idLookup[target[id]] = id
        }
        
        val ret = mutableListOf<Int>()
        for (num in arr) {
            idLookup[num]?.let { ret.add(it) }
        }
        return ret
    }
    
    private fun List<Int>.longestIncreasingSubsequence(): Int {
        if (isEmpty()) return 0
        
        val lengthTo = TreeMap<Int, Int>()
        for (num in this) {
            val thisLength = lengthTo.floorEntry(num)?.let { (lessEqualNum, length) ->
                if (lessEqualNum < num) {
                    lengthTo[num] = length + 1
                    length + 1
                } else {
                    length
                }
            } ?: run {
                lengthTo[num] = 1
                1
            }
            
            lengthTo.higherEntry(num)?.let { (greaterNum, length) ->
                if (thisLength == length) {
                    lengthTo.remove(greaterNum)
                }
            }
        }
        return lengthTo.lastEntry().value
    }
    
    fun minOperations(target: IntArray, arr: IntArray): Int {
        return target.size - makeSurrogate(target, arr).longestIncreasingSubsequence()
    }
}
