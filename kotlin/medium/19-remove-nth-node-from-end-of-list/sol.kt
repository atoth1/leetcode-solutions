// https://leetcode.com/problems/remove-nth-node-from-end-of-list/

/**
 * Example:
 * var li = ListNode(5)
 * var v = li.`val`
 * Definition for singly-linked list.
 * class ListNode(var `val`: Int) {
 *     var next: ListNode? = null
 * }
 */
class Solution {
  private data class IntWrapper(var value: Int)
  
  fun removeNthFromEnd(head: ListNode?, n: Int): ListNode? {
      return impl(head!!, n, 0, IntWrapper(0))
  }
  
  private fun impl(node: ListNode, n: Int, pos: Int, count: IntWrapper): ListNode? {
      node.next?.let { next ->
          node.next = impl(next, n, pos+1, count)
      } ?: run {
          count.value = pos+1
      }
      return if (count.value - pos == n) node.next else node 
  }
}
