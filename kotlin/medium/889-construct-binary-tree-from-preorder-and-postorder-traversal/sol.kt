// https://leetcode.com/problems/construct-binary-tree-from-preorder-and-postorder-traversal/

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
  fun constructFromPrePost(preorder: IntArray, postorder: IntArray): TreeNode? {
      // One node is guaranteed, but probably still good to do size-0 check
      return if (preorder.size == 0) {
          null
      } else {
          impl(preorder, 0, preorder.size - 1, postorder, 0, postorder.size - 1)
      }
  }
  
  private fun impl(
      preorder: IntArray,
      preorderStart: Int,
      preorderEnd: Int,
      postorder: IntArray,
      postorderStart: Int,
      postorderEnd: Int
  ): TreeNode {
      // postorder[postorderEnd] should be the same value
      return TreeNode(preorder[preorderStart]).apply{
          // Should only need to check one of these, but whatever
          if (preorderStart != preorderEnd && postorderStart != postorderEnd) {
              // preorderStart + 1 is root of an existing left subtree, and postorderEnd - 1
              // is root of an existing right subtree. If the values are the same, there is
              // only one subtree of this node. We'll just stick it on the left
              if (preorder[preorderStart + 1] == postorder[postorderEnd - 1]) {
                  left = impl(preorder, preorderStart + 1, preorderEnd,
                              postorder, postorderStart, postorderEnd - 1)
              } else {
                  var leftCount = 1
                  while (preorder[preorderStart + 1 + leftCount] != postorder[postorderEnd - 1]) {
                      ++leftCount
                  }
                  left = impl(preorder, preorderStart + 1, preorderStart + leftCount,
                              postorder, postorderStart, postorderStart + leftCount - 1)
                  right = impl(preorder, preorderStart + leftCount + 1, preorderEnd,
                               postorder, postorderStart + leftCount , postorderEnd - 1)
              }
          }
      }
  }
}
