// https://leetcode.com/problems/add-to-array-form-of-integer/

class Solution {
  fun addToArrayForm(num: IntArray, k: Int): List<Int> {
      // Strange 0 not allowed per problem spec, but still doesn't hurt to check.
      if (k == 0) return num.toList()
      
      val x = num.reversed().toMutableList()
      val y = mutableListOf<Int>()
      var n = k
      while (n != 0) {
          val tmp = n/10
          y.add(n - 10*tmp)
          n = tmp
      }
      
      var carry = false
      var xPos = 0
      var yPos = 0
      while (carry || yPos < y.size) {
          if (xPos == x.size) x.add(0)
          
          if (carry) {
              ++x[xPos]
              carry = false
          }
          
          if (yPos < y.size) {
              x[xPos] += y[yPos]
              ++yPos
          }
          
          if (x[xPos] > 9) {
              x[xPos] -= 10
              carry = true
          }
          ++xPos
      }
      x.reverse()
      return x
  }
}
