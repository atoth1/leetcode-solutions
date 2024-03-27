// https://leetcode.com/problems/count-valid-paths-in-a-tree/

private const val MAX_VALUE = 100000

private fun computePrimes(): Set<Int> {
    val isPrime = BooleanArray(MAX_VALUE) { true }
    val primes = mutableSetOf<Int>()
    for (n in 2 .. MAX_VALUE) {
        if (isPrime[n - 1]) {
            primes.add(n)

            var factor = n
            while (factor.toLong() * n <= MAX_VALUE.toLong()) {
                isPrime[factor * n - 1] = false
                ++factor
            }
        }
    } 
    return primes
}

private val primes = computePrimes()

private fun Int.isPrime(): Boolean = primes.contains(this)

private fun Int.chooseTwo(): Long = (this - 1).toLong() * this / 2

private data class SetNode(val label: Int) {
    var parent: SetNode? = null
    var size: Int = 1
    val neighbors: MutableList<SetNode> = mutableListOf()
    
    fun getRoot(): SetNode {
        var root = this
        while (root.parent != null) {
            root = root.parent!!
        }
        
        var node = this
        while (node.parent != null) {
            node = node.parent!!.also { node.parent = root }
        }
        return root
    }
    
    infix fun joinWith(other: SetNode) {
        var x = getRoot()
        var y = other.getRoot()
        if (x !== y) {
            if (x.size < y.size) {
                x = y.also { y = x }
            }
            x.size += y.size
            y.parent = x
        }
    }
}

private fun makeGraph(edges: Array<IntArray>): Array<SetNode> {
    val graph = Array(edges.size + 1) { SetNode(it + 1) }
    for ((id1, id2) in edges) {
        val prime1 = id1.isPrime()
        val prime2 = id2.isPrime()
        if (!prime1 && !prime2) {
            graph[id1 - 1] joinWith graph[id2 - 1]
        } else if (prime1 && !prime2) {
            graph[id1 - 1].neighbors.add(graph[id2 - 1])
        } else if (!prime1 && prime2) {
            graph[id2 - 1].neighbors.add(graph[id1 - 1])
        }
    }
    return graph
}

class Solution {
    fun countPaths(whyIsThisHereItCanBeDeducedFromEdgesSize: Int, edges: Array<IntArray>): Long {
        val graph = makeGraph(edges)
        var ret = 0L
        for (prime in primes) {
            if (prime > graph.size) break
            val node = graph[prime - 1]
            var nodeCount = 1
            for (neighbor in node.neighbors) {
                val root = neighbor.getRoot()
                nodeCount += root.size
                ret -= root.size.chooseTwo()
            }
            ret += nodeCount.chooseTwo()
        }
        return ret
    }
}
