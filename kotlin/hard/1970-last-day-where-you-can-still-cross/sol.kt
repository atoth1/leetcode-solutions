// https://leetcode.com/problems/last-day-where-you-can-still-cross/

class Solution {
    
    private data class SetNode(
        var touchesLeft: Boolean,
        var touchesRight: Boolean,
        var parent: SetNode? = null,
        var rank: Int = 0
    ) {
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
                if (y.touchesLeft) x.touchesLeft = true
                if (y.touchesRight) x.touchesRight = true
                if (x.rank == y.rank) ++x.rank
                y.parent = x
            }
        }
    }
    
    fun latestDayToCross(m: Int, n: Int, cells: Array<IntArray>): Int {
        val nodes = Array(m) { Array<SetNode?>(n) { null } }
        
        val attemptJoin = { x: SetNode, r: Int, c: Int ->
            if (r >= 0 && r < m) {
                    if (c >= 0 && c < n) {
                        nodes[r][c]?.let { y -> x join y }
                }
            }
        }
        
        var day = 0
        for (cell in cells) {
            val r = cell[0] - 1
            val c = cell[1] - 1
            val node = SetNode(c == 0, c == n - 1)
            attemptJoin(node, r - 1, c - 1)
            attemptJoin(node, r - 1, c)
            attemptJoin(node, r - 1, c + 1)
            attemptJoin(node, r, c - 1)
            attemptJoin(node, r, c + 1)
            attemptJoin(node, r + 1, c - 1)
            attemptJoin(node, r + 1, c)
            attemptJoin(node, r + 1, c + 1)
            val root = node.getRoot()
            if (root.touchesLeft && root.touchesRight) return day
            nodes[r][c] = node
            ++day
        }
        return -1
    }
}
