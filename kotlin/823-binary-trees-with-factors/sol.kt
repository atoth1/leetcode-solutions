// https://leetcode.com/problems/binary-trees-with-factors/

const val modulus = 1000000007

class Solution {
    
    fun numFactoredBinaryTrees(arr: IntArray): Int {
        arr.sort()
        var total = 0
        val counts = IntArray(arr.size)
        arr.forEachIndexed { id, num ->
            // Tree of just this value
            var thisCount = 1
            
            var l = 0
            var r = id - 1
            while (l < r) {
                val prod = arr[l].toLong() * arr[r].toLong()
                if (prod < num.toLong()) {
                    ++l
                } else if (prod > num.toLong()) {
                    --r
                } else {
                    thisCount += ((2L * (counts[l].toLong() * counts[r].toLong())) % modulus).toInt()
                    thisCount %= modulus
                    ++l
                    --r
                }
            }
            
            if (l == r && arr[l].toLong() * arr[l].toLong() == num.toLong()) {

                thisCount += ((counts[l].toLong() * counts[r].toLong()) % modulus).toInt()
                thisCount %= modulus
            }
            counts[id] = thisCount
            total += thisCount
            total %= modulus
        }
        return total
    }
}
