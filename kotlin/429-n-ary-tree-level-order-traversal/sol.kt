// https://leetcode.com/problems/n-ary-tree-level-order-traversal/

/**
 * Ugh, very dumb definition. Children should be of type
 * List<Node>. No children would be an empty list. A
 * null child in this list has no meaning and shouldn't be allowed.
 * Just causes extra typing to deal with null safety for no reason.
 * Definition for a Node.
 * class Node(var `val`: Int) {
 *     var children: List<Node?> = listOf()
 * }
 */

class Solution {
  fun levelOrder(root: Node?): List<List<Int>> {
      if (root == null) return emptyList()
      var curr = mutableListOf(root!!)
      var next = mutableListOf<Node>()
      val ret = mutableListOf<List<Int>>()
      while (!curr.isEmpty()) {
          val currLevelValues = mutableListOf<Int>()
          for (node in curr) {
              currLevelValues.add(node.`val`)
              for (child in node.children) {
                  child?.let { next.add(it) }
              }
          }
          ret.add(currLevelValues)
          curr = next.also { next = curr }
          next.clear()
      }
      return ret
  }
}