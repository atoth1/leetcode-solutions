// https://leetcode.com/problems/merge-k-sorted-lists/

/**
 * Example:
 * var li = ListNode(5)
 * var v = li.`val`
 * Definition for singly-linked list.
 * class ListNode(var `val`: Int) {
 *     var next: ListNode? = null
 * }
 */

import java.util.PriorityQueue

class Solution {
    
    companion object { const val INVALID = -1 }
    
    private data class ListNodeWrapper(var node: ListNode)
    
    private fun makeQueue(lists: Array<ListNode?>): PriorityQueue<ListNodeWrapper> {
        val comp = Comparator<ListNodeWrapper> { l, r ->
            l.node.`val` - r.node.`val`
        }
        val queue = PriorityQueue(comp)
        for (node in lists) {
            node?.let {
                queue.add(ListNodeWrapper(it))
            }
        }
        return queue
    }
    
    private fun solve(queue: PriorityQueue<ListNodeWrapper>): ListNode? {
        val sentinel = ListNode(INVALID)
        var curr = sentinel
        while (queue.size > 0) {
            val node = queue.poll()
            curr.next = ListNode(node.node.`val`)
            curr = curr.next
            node.node.next?.let {
                node.node = it
                queue.add(node)
            }
        }
        return sentinel.next
    }
    
    fun mergeKLists(lists: Array<ListNode?>): ListNode? {
        val queue = makeQueue(lists)
        return solve(queue)
    }
}
