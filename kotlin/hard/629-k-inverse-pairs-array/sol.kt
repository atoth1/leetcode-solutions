// https://leetcode.com/problems/k-inverse-pairs-array/

private const val modulus = 1000000007
private const val kMax = 1000

class Solution {
    fun kInversePairs(n: Int, k: Int): Int {
        val kBound = n * (n - 1) / 2
        return if (k > kBound) {
            return 0
        } else {
            var result = 1
            cache[n]?.apply {
                result = get(k)
            } ?: run {
                val allResults = mutableListOf(result)
                cache[n] = allResults
                for (j in 1..minOf(kBound, kMax)) {
                    result += kInversePairs(n - 1, j)
                    result %= modulus
                    if (j >= n) {
                        result -= kInversePairs(n - 1, j - n)
                        if (result < 0) result += modulus
                    }
                    allResults.add(result)
                }
                result = allResults[k]
            }
            result
        }
    }
    
    companion object {
        val cache = mutableMapOf<Int, MutableList<Int>>(1 to mutableListOf(1))
    }
}
