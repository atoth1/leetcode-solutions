// https://leetcode.com/problems/pseudo-palindromic-paths-in-a-binary-tree/

/**
 * Example:
 * var ti = TreeNode(5)
 * var v = ti.`val`
 * Definition for a binary tree node.
 * class TreeNode(var `val`: Int) {
 *     var left: TreeNode? = null
 *     var right: TreeNode? = null
 * }
 */
class Solution {
  private data class IntWrapper(var value: Int)
  
  fun pseudoPalindromicPaths (root: TreeNode?): Int {
      val count = IntWrapper(0)
      val counts = IntArray(9)
      root?.let { node ->
          impl(node, count, counts)
      }
      return count.value
  }
  
  private fun impl(node: TreeNode, count: IntWrapper, counts: IntArray) {
      counts[node.`val` - 1] += 1
      if (node.left != null || node.right != null) {
          node.left?.let { impl(it, count, counts) }
          node.right?.let { impl(it, count, counts) }
      } else {
          var oddCount = 0
          for (it in counts) {
              if (it%2 == 1) ++oddCount
          }
          if (oddCount < 2) ++count.value
      }
      counts[node.`val` - 1] -= 1
  }
}
