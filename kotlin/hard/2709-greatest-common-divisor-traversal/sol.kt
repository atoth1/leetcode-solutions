// https://leetcode.com/problems/greatest-common-divisor-traversal/

class Solution {
    
    companion object {
        private const val MAX_NUM = 100000

        private fun generatePrimeFactors(): Array<MutableList<Int>> {
            val isPrime = BooleanArray(MAX_NUM + 1) { true }
            val ret = Array(MAX_NUM + 1) { mutableListOf<Int>() }
            for (num in 2 .. MAX_NUM) {
                if (isPrime[num]) {
                    ret[num].add(num)
                    var factor = 2
                    while (num * factor <= MAX_NUM) {
                        ret[num * factor].add(num)
                        isPrime[num * factor++] = false
                    }
                }
            }
            return ret
        }
        val primeFactors = generatePrimeFactors()
        
        private data class SetNode(var parent: SetNode? = null, var rank: Int = 1) {
            fun getRoot(): SetNode {
                var root = this
                while (root.parent != null) {
                    root = root.parent!!
                }
                
                var node = this
                while (node.parent != null) {
                    node.parent = root.also { node = node.parent!! }
                }
                return root
            }
            
            infix fun join(other: SetNode) {
                var x = getRoot()
                var y = other.getRoot()
                if (x !== y) {
                    if (x.rank < y.rank) x = y.also { y = x }
                    if (x.rank == y.rank) ++x.rank
                    y.parent = x
                }
            }
        }
    }
    
    fun canTraverseAllPairs(nums: IntArray): Boolean {
        if (nums.size == 1) return true
        if (nums.min()!! < 2) return false
        
        val numToSetNode = mutableMapOf<Int, SetNode>()
        for (num in nums) {
            val factors = primeFactors[num]
            val firstNode = numToSetNode.getOrPut(factors[0]) { SetNode() }
            for (factor in factors) {
                firstNode join numToSetNode.getOrPut(factor) { SetNode() }
            }
        }
        
        val firstRoot = numToSetNode.asIterable().first().value.getRoot()
        for (node in numToSetNode.values) {
            if (node.getRoot() !== firstRoot) return false
        }
        return true
    }
}