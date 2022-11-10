// https://leetcode.com/problems/binary-tree-maximum-path-sum/

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
  
  fun maxPathSum(root: TreeNode?): Int {
      return root?.let {
          val max = IntWrapper(UNSET)
          impl(it, max)
          max.value
      } ?: -1
  }
  
  private fun impl(node: TreeNode, max: IntWrapper): Int {
      var maxToLeftLeaf = UNSET
      node.left?.let { left ->
          maxToLeftLeaf  = impl(left, max)
      } 
      var maxToRightLeaf = UNSET
      node.right?.let { right ->
          maxToRightLeaf = impl(right, max)
      }
      
      var maxAsRoot = node.`val`
      if (maxToLeftLeaf > 0) maxAsRoot += maxToLeftLeaf
      if (maxToRightLeaf > 0) maxAsRoot += maxToRightLeaf
      if (maxAsRoot > max.value) max.value = maxAsRoot
      
      return if (maxToLeftLeaf > maxToRightLeaf && maxToLeftLeaf > 0) {
          node.`val` + maxToLeftLeaf
      } else if (maxToRightLeaf > maxToLeftLeaf && maxToRightLeaf > 0) {
          node.`val` + maxToRightLeaf
      } else {
          node.`val`
      }
  }
  
  companion object {
      const val UNSET = -1000000000
  }
}
