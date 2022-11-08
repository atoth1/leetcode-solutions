// https://leetcode.com/problems/flatten-a-multilevel-doubly-linked-list/

/**
 * Definition for a Node.
 * class Node(var `val`: Int) {
 *     var prev: Node? = null
 *     var next: Node? = null
 *     var child: Node? = null
 * }
 */

class Solution {
    
  fun flatten(root: Node?): Node? {
      return root?.let {
          flattenImpl(it)
          it
      } ?: null
  }
  
  private fun flattenImpl(head: Node): Node {
      var node = head
      while (node.next != null) {
          val next = node.next!!
          node.child?.let { flattenedHead ->
              val flattenedTail = flattenImpl(flattenedHead)
              node.next = flattenedHead
              flattenedHead.prev = node
              flattenedTail.next = next
              next.prev = flattenedTail
              node.child = null
          }
          node = next
      }
      return node.child?.let { flattenedHead ->
          val flattenedTail = flattenImpl(flattenedHead)
          node.next = flattenedHead
          flattenedHead.prev = node
          node.child = null
          flattenedTail
      } ?: node
  }
}
