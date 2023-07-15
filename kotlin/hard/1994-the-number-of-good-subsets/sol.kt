// https://leetcode.com/problems/the-number-of-good-subsets/

private val candidates = intArrayOf(
    2, 3, 5, 6, 7, 10, 11, 13, 14, 15, 17, 19, 21, 22, 23, 26, 29, 30
)

private fun gcd(a: Long, b: Long): Long {
   if (b == 0L) return a
   return gcd(b, a % b)
}

private fun initValidSubsets(): List<List<Int>> {
    val bound = 1 shl candidates.size
    val subsets = mutableListOf<List<Int>>()
    for (i in 1 until bound) {
        val subset = mutableListOf<Int>()
        var prod = 1L
        var validSubset = true
        for (candidateId in 0 until candidates.size) {
            if (i and (1 shl candidateId) != 0) {
                if (gcd(prod, candidates[candidateId].toLong()) != 1L) {
                    validSubset = false
                    break
                }
                subset.add(candidates[candidateId])
                prod *= candidates[candidateId]
            }
        }
        if (validSubset) {
            subsets.add(subset)
        }
    }
    return subsets
}
private val validSubsets = initValidSubsets()

private const val MOD = 1000000007


class Solution {
    fun numberOfGoodSubsets(nums: IntArray): Int {
        val getCounts: () -> IntArray = {
            val maxN = 30
            val counts = IntArray(maxN)
            for (num in nums) {
                ++counts[num - 1]
            }
            counts
        };
        val counts = getCounts()
        
        val getValidSubsetCountOmittingOnes: () -> Int = {
            var count = 0
            for (subset in validSubsets) {
                var prod = 1
                for (num in subset) {
                    prod = ((prod.toLong() * counts[num - 1]) % MOD).toInt()
                }
                count = (count + prod) % MOD
            }
            count
        }
        
        val twoToN = { n: Int ->
            var ret = 1
            repeat (n) {
                ret = (2 * ret) % MOD
            }
            ret
        }
        
        return ((twoToN(counts[0]).toLong() * getValidSubsetCountOmittingOnes()) % MOD).toInt();
    }
}