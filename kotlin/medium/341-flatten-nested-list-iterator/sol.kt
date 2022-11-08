// https://leetcode.com/problems/flatten-nested-list-iterator/

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *     // Constructor initializes an empty nested list.
 *     constructor()
 *
 *     // Constructor initializes a single integer.
 *     constructor(value: Int)
 *
 *     // @return true if this NestedInteger holds a single integer, rather than a nested list.
 *     fun isInteger(): Boolean
 *
 *     // @return the single integer that this NestedInteger holds, if it holds a single integer
 *     // Return null if this NestedInteger holds a nested list
 *     fun getInteger(): Int?
 *
 *     // Set this NestedInteger to hold a single integer.
 *     fun setInteger(value: Int): Unit
 *
 *     // Set this NestedInteger to hold a nested list and adds a nested integer to it.
 *     fun add(ni: NestedInteger): Unit
 *
 *     // @return the nested list that this NestedInteger holds, if it holds a nested list
 *     // Return null if this NestedInteger holds a single integer
 *     fun getList(): List<NestedInteger>?
 * }
 */

class NestedIterator(val nestedList: List<NestedInteger>) {
  fun next(): Int {
      val ret = currentVal
      advance()
      return ret
  }
  
  fun hasNext(): Boolean {
      return id < nestedList.size
  }
  
  private var id = INVALID_ID
  private var currentVal = INVALID_VAL
  private var currentIter: NestedIterator? = null
  
  init {
      advance()
  }
  
  private fun advance() {
      var success = false
      while (id < nestedList.size && !success) {
          if (id == INVALID_ID || nestedList[id].isInteger()|| !currentIter!!.hasNext()) {
              ++id
              currentIter = null
          }
          
          if (id < nestedList.size) {
              if (nestedList[id].isInteger()) {
                  currentVal = nestedList[id].getInteger()
                  success = true
              } else {
                  if (currentIter == null) {
                      currentIter = NestedIterator(nestedList[id].getList())
                  }
                  // Does it know currentIter non-null here without the scope function?
                  currentIter?.let {
                      if (it.hasNext()) {
                          currentVal = it.next()
                          success = true
                      }
                  }
              }
          }
      }
  }
  
  companion object {
      private const val INVALID_ID = -1
      private const val INVALID_VAL = -1000000000
  }
}

/**
* Your NestedIterator object will be instantiated and called as such:
* var obj = NestedIterator(nestedList)
* var param_1 = obj.next()
* var param_2 = obj.hasNext()
*/