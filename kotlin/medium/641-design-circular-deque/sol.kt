// https://leetcode.com/problems/design-circular-deque/

class MyCircularDeque(k: Int) {

  private var begin = 0
  private var end = 0
  private var size = 0
  private val storage = IntArray(k)
  
  fun insertFront(value: Int): Boolean {
      return if (isFull()) {
          false
      } else {
          begin = wrappedDecrement(begin)
          storage[begin] = value
          ++size
          true
      }
  }

  fun insertLast(value: Int): Boolean {
      return if (isFull()) {
          false
      } else {
          storage[end] = value
          end = wrappedIncrement(end)
          ++size
          true
      }
  }

  fun deleteFront(): Boolean {
      return if (isEmpty()) {
          false
      } else {
          begin = wrappedIncrement(begin)
          --size
          true
      }
  }

  fun deleteLast(): Boolean {
      return if (isEmpty()) {
          false
      } else {
          end = wrappedDecrement(end)
          --size
          true
      }
  }

  fun getFront(): Int {
      return if (isEmpty()) -1 else storage[begin]
  }

  fun getRear(): Int {
      return if (isEmpty()) -1 else storage[wrappedDecrement(end)]
  }

  fun isEmpty(): Boolean {
      return size == 0
  }

  fun isFull(): Boolean {
      return size == storage.size
  }
  
  private fun wrappedIncrement(n: Int): Int {
      return if (n == storage.size-1) 0 else n+1
  }
  
  private fun wrappedDecrement(n: Int): Int {
      return if (n == 0) storage.size-1 else n-1
  }

}

/**
* Your MyCircularDeque object will be instantiated and called as such:
* var obj = MyCircularDeque(k)
* var param_1 = obj.insertFront(value)
* var param_2 = obj.insertLast(value)
* var param_3 = obj.deleteFront()
* var param_4 = obj.deleteLast()
* var param_5 = obj.getFront()
* var param_6 = obj.getRear()
* var param_7 = obj.isEmpty()
* var param_8 = obj.isFull()
*/
