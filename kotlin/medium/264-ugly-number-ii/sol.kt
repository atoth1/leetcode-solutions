// https://leetcode.com/problems/ugly-number-ii/

class Solution {
  fun nthUglyNumber(n: Int): Int {
      if (sols.isEmpty()) computeSolutions()
      return sols[n-1]
  }
  
  companion object {
      private val sols = mutableListOf<Int>()
          
      private fun computeSolutions() {
          val queue = sortedSetOf(1)
          val bound2 = Int.MAX_VALUE/2
          val bound3 = Int.MAX_VALUE/3
          val bound5 = Int.MAX_VALUE/5
          repeat(1690) {
              val first = queue.first()
              sols.add(first)
              queue.remove(first)
              if (first <= bound2) queue.add(2*first)
              if (first <= bound3) queue.add(3*first)
              if (first <= bound5) queue.add(5*first)
          }
      }
  }
}
