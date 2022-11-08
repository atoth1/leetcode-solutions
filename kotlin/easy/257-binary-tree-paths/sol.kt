// https://leetcode.com/problems/binary-tree-paths/

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
  fun binaryTreePaths(root: TreeNode?): List<String> {
      val paths = mutableListOf<String>()
      impl(root!!, "", paths)
      return paths
  }
  
  private fun impl(node: TreeNode, prevString: String, paths: MutableList<String>) {
      val thisString = if (prevString.isEmpty()) {
          node.`val`.toString()
      } else {
          val builder = StringBuilder(prevString)
          builder.append("->").append(node.`val`.toString())
          builder.toString()
      }
      if (node.left == null && node.right == null) {
          paths.add(thisString)
      } else {
          node.left?.let { left -> 
              impl(left, thisString, paths)
          }
          node.right?.let { right ->
              impl(right, thisString, paths)
          }
      }
  }
}
