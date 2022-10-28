// https://leetcode.com/problems/find-the-k-beauty-of-a-number/

class Solution {
  fun divisorSubstrings(num: Int, k: Int): Int {
      // num > 0 guaranteed, otherwise check here
      val digits = mutableListOf<Int>()
      var tmp = num
      while (tmp != 0) {
          val quot = tmp/10
          val rem = tmp - 10*quot
          digits.add(rem)
          tmp = quot
      }
      
      var window = 0
      var factor = 1
      for (digit in 0 until k) {
          window += factor * digits[digit]
          factor *= 10
      }
      factor /= 10
      
      var ret = 0
      for (digit in k until digits.size) {
          if (window != 0 && num % window  == 0) ++ret
          window /= 10
          window += factor * digits[digit]
      }
      if (num % window == 0) ++ret
      return ret
  }
}
