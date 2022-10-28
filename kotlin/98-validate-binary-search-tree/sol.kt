// https://leetcode.com/problems/validate-binary-search-tree/

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
  private data class IntWrapper(var value: Int? = null)
  
  fun isValidBST(root: TreeNode?): Boolean {
      // Is binary search tree iff inorder traversal is strictly increasing
      // (at least by this definition, unsure how repeated values are treated in general)
      return impl(root, IntWrapper())
  }
  
  private fun impl(node: TreeNode?, previous: IntWrapper): Boolean {
      node?.let {
          if (!impl(it.left, previous)) return@impl false
          previous.value?.let { prev -> if (it.`val` <= prev) return@impl false }
          previous.value = it.`val`
          if (!impl(it.right, previous)) return@impl false
      }
      return true
  }
}
