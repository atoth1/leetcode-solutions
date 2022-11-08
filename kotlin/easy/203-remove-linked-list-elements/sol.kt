// https://leetcode.com/problems/remove-linked-list-elements/

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
  fun removeElements(head: ListNode?, `val`: Int): ListNode? {
      val sentinel = ListNode(INVALID).apply { next = head }
      var prev = sentinel
      var curr = head
      while (curr != null) {
          if (curr.`val` == `val`) {
              prev.next = curr.next
              curr.next = null
              curr = prev.next
          } else {
              prev = curr.also { curr = it.next }
          }
      }
      return sentinel.next
  }
  
  companion object {
      val INVALID = 0
  }
}
