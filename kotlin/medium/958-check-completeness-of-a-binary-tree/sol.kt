// https://leetcode.com/problems/check-completeness-of-a-binary-tree/

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
  fun isCompleteTree(root: TreeNode?): Boolean {
      var curr = mutableListOf(root!!)
      var next = mutableListOf<TreeNode>()
      var isComplete = true
      var fullLevelCount = 1
      while (!curr.isEmpty()) {
          var nullAtNextLevel = false
          for (node in curr) {
              if (nullAtNextLevel) {
                  // If a non-null child occurs at this point, tree is not complete
                  node.left?.let { isComplete = false }
                  node.right?.let { isComplete = false }
              } else {
                  node.left?.apply {
                      next.add(this)
                  } ?: run {
                      nullAtNextLevel = true
                  }
                  node.right?.apply {
                      if (nullAtNextLevel) {
                          isComplete = false
                      } else {
                          next.add(this)
                      }
                  } ?: run {
                      nullAtNextLevel = true
                  }
              }
          }
          if (curr.size < fullLevelCount && !next.isEmpty()) {
              isComplete = false
              break
          }
          fullLevelCount *= 2
          curr = next.also { next = curr }
          next.clear()
      }
      return isComplete
  }
}
