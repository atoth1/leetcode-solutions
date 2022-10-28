// https://leetcode.com/problems/add-one-row-to-tree/

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
  fun addOneRow(root: TreeNode?, `val`: Int, depth: Int): TreeNode? {
      if (depth == 1) {
          return TreeNode(`val`).apply { left = root }
      } else {
          var curr = mutableListOf<TreeNode>(root!!)
          var next = mutableListOf<TreeNode>()
          repeat(depth-2) {
              for (node in curr) {
                  node.left?.let { next.add(it) }
                  node.right?.let { next.add(it) }
              }
              curr = next.also { next = curr }
              next.clear()
          }
          
          for (node in curr) {
              node.left = TreeNode(`val`).also { it.left = node.left }
              node.right = TreeNode(`val`).also { it.right = node.right }
          }
          return root
      }
  }
}
