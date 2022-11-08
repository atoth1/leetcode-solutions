// https://leetcode.com/problems/number-of-islands/

class Solution {
  fun numIslands(grid: Array<CharArray>): Int {
      val m = grid.size
      val n = grid[0].size
      
      val nodes = Array(m) { Array<SetNode?>(n) { null } }
      for (row in 0 until m) {
          for (col in 0 until n) {
              if (grid[row][col] == '1') {
                  nodes[row][col] = SetNode(id = col + row*n)
                  if (col > 0) nodes[row][col-1]?.let { it join nodes[row][col]!! }
                  if (row > 0) nodes[row-1][col]?.let { it join nodes[row][col]!! }
              }
          }
      }
      
      val roots = mutableSetOf<SetNode>()
      for (row in 0 until m) {
          for (col in 0 until n) {
              nodes[row][col]?.let { roots.add(it.rootNode()) }
          }
      }
      return roots.size
  }
  
  private data class SetNode(
      var parent: SetNode? = null,
      var rank: Int = 0,
      val id: Int // Unique id to differentiate for set lookups
  )
  
  private fun SetNode.rootNode(): SetNode {
      var root = this
      while (root.parent != null) {
          root = root.parent!!
      }
      
      if (this !== root) {
          var tmp1 = this
          while (tmp1.parent !== root) {
              val tmp2 = tmp1.parent!!
              tmp1.parent = root
              tmp1 = tmp2
          }
      }
      return root
  }
  
  private infix fun SetNode.join(other: SetNode) {
      var x = rootNode()
      var y = other.rootNode()
      if (x !== y) {
          if (y.rank > x.rank) x = y.also { y = x }
          if (x.rank == y.rank) ++x.rank
          y.parent = x
      }
  }
}
