// https://leetcode.com/problems/equal-rational-numbers/

class Solution {
    
  companion object {
      const val eps = 1.0e-14
  }
  
  fun isRationalEqual(s: String, t: String): Boolean {
      // Check relative difference when both non-zero
      val sd = s.toDouble()
      val td = t.toDouble()
      return if (sd < eps) {
          td < eps
      } else if (sd < eps) {
          sd < eps
      } else {
          kotlin.math.abs((sd-td)/sd) < eps
      }
  }
  
  private fun String.toDouble(): Double {
      var ret = 0.0
      var id = 0
      
      // Get whole number part
      while (id != length && get(id) != '.') {
          ret = 10*ret + (get(id) - '0').toDouble()
          ++id
      }
      
      if (id != length) {
          // Bypass decimal point
          ++id

          // Non-repeating
          var factor = 0.1
          while (id != length && get(id) != '(') {
              ret += factor * (get(id) - '0')
              factor /= 10
              ++id
          }

          // Repeating
          if (id != length) {
              var num = 0
              var denom = 0
              // length-1 is ')'
              for (tmp in id+1 until length-1) {
                  num = 10*num + (get(tmp) - '0').toInt()
                  denom = 10*denom + 9
              }
              if (denom != 0) {
                  ret += 10*factor*num/denom
              }
          }
      }
      return ret
  }
}
