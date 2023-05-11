// https://leetcode.com/problems/similar-string-groups/

class Solution {
    
    companion object {
    
        private data class SetNode(var parent: SetNode? = null, var rank: Int = 0)

        private fun SetNode.getRoot(): SetNode {
            var root = this
            while (root.parent != null) {
                root = root.parent!!
            }

            var node = this
            while (node.parent != null) {
                val tmp = node.parent!!
                node.parent = root
                node = tmp
            }
            return root
        }

        private fun SetNode.isRoot(): Boolean {
            return this === getRoot()
        }

        private infix fun SetNode.join(other: SetNode) {
            var x = getRoot()
            var y = other.getRoot()
            if (x !== y) {
                if (x.rank < y.rank) x = y.also { y = x }
                if (x.rank == y.rank) ++x.rank
                y.parent = x
            }
        }

        private infix fun String.isSimilarTo(other: String): Boolean {
            var differCount = 0
            for (id in 0 until length) {
                if (get(id) != other[id]) ++differCount
            }
            return differCount == 0 || differCount == 2
        }

        private fun solve(strs: Array<String>): Int {
            val nodes = Array(strs.size) { SetNode() }
            for (id1 in 0 until nodes.size-1) {
                for (id2 in id1+1 until nodes.size) {
                    if (strs[id1] isSimilarTo strs[id2]) {
                        nodes[id1] join nodes[id2]
                    }
                }
            }

            var count = 0
            for (node in nodes) {
                if (node.isRoot()) ++count
            }
            return count
        }
    
    }
    
    fun numSimilarGroups(strs: Array<String>): Int {
        return solve(strs)
    }
}
