// https://leetcode.com/problems/design-linked-list/

class MyLinkedList() {
    
  companion object {
      const val INVALID = -1
  }
  
  private data class Node(var value: Int, var next: Node?)
  
  // Sentinel node with invalid value always at head.
  private var head = Node(INVALID, null)
  
  // Would make sense to have this be another sentinel if we did doubly linked,
  // but not in this case.
  private var tail: Node? = null
  
  private var size = 0

  fun get(index: Int): Int {
      return if (index >= 0 && index < size) {
          var curr = head.next!!
          repeat(index) {
              curr = curr.next!!
          }
          curr.value
      } else {
          -1
      }
  }

  fun addAtHead(`val`: Int) {
      val value = `val`
      head.next = Node(value, head.next)
      if (size == 0) tail = head.next
      ++size
  }

  fun addAtTail(`val`: Int) {
      val value = `val`
      if (size == 0) {
          head.next = Node(value, null)
          tail = head.next
      } else {
          tail?.let {
              it.next = Node(value, null)
              tail = it.next
          }
      }
      ++size
  }

  fun addAtIndex(index: Int, `val`: Int) {
      val value = `val`
      if (index < size) {
          var prev = head
          var curr = head.next!!
          repeat(index) {
              prev = curr
              curr = curr.next!!
          }
          prev.next = Node(value, curr)
          ++size
      } else if (index == size) {
          addAtTail(value)
      }
  }

  fun deleteAtIndex(index: Int) {
      if (index >= 0 && index < size) {
          var prev = head
          var curr = head.next!!
          repeat(index) {
              prev = curr
              curr = curr.next!!
          }
          prev.next = curr.next
          curr.next = null
          if (index == size - 1) tail = prev
          --size
      }
  }

}

/**
* Your MyLinkedList object will be instantiated and called as such:
* var obj = MyLinkedList()
* var param_1 = obj.get(index)
* obj.addAtHead(`val`)
* obj.addAtTail(`val`)
* obj.addAtIndex(index,`val`)
* obj.deleteAtIndex(index)
*/
