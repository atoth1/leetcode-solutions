// https://leetcode.com/problems/binary-tree-pruning/

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
  fun pruneTree(root: TreeNode?): TreeNode? {
      return root?.let { node ->
          node.left?.let { left ->
              node.left = pruneTree(left)
          }
          node.right?.let { right ->
              node.right = pruneTree(right)
          }
          if (node.left != null || node.right != null || node.`val` == 1) node else null
      }
  }
}