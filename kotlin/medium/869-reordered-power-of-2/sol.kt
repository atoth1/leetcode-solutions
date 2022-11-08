// https://leetcode.com/problems/reordered-power-of-2/

class Solution {
  fun reorderedPowerOf2(n: Int): Boolean {
      if (powerOfTwoDigitCounts.isEmpty()) init()
      return powerOfTwoDigitCounts.contains(digitCounts(n))
  }
  
  companion object {
      // Equality comparison of IntArray doesn't work as I'd like, so
      // need to convert to lists
      private val powerOfTwoDigitCounts = mutableSetOf<List<Int>>()
      
      private fun init() {
          var num = 1 shl 30
          while (num > 0) {
              powerOfTwoDigitCounts.add(digitCounts(num))
              num /= 2
          }
      }
      
      private fun digitCounts(n: Int): List<Int> {
          var tmp = n
          val ret = IntArray(10)
          while (tmp != 0) {
              val quot = tmp/10
              val rem = tmp - 10*quot
              ++ret[rem]
              tmp = quot
          }
          return ret.toList()
      }
  }
}
