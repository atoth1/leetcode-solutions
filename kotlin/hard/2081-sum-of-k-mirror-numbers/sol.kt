// https://leetcode.com/problems/sum-of-k-mirror-numbers/

class Solution {
  fun kMirror(k: Int, n: Int): Long {
      // 1 -- n all work, return the sum 
      if (n < k) return n.toLong()*(n+1)/2
      
      var nm2 = mutableListOf(CharArray(0))
      var nm1 = mutableListOf<CharArray>()
      var sum = 0.toLong()
      var count = k-1
      for (c in '0' until '0'+k) {
          nm1.add(CharArray(1) { c })
          sum += (c-'0')
      }
      
      var length = 2
      while (true) {
          val curr = mutableListOf<CharArray>()
          var breakOut = false
          for (arr in nm2) {
              curr.add(CharArray(length) { idx ->
                  if (idx == 0 || idx == length-1) '0'
                  else arr[idx-1]
              })
          }
          for (c in '1' until '0'+k) {
              for (arr in nm2) {
                  val next = CharArray(length) { idx ->
                      if (idx == 0 || idx == length-1) c
                      else arr[idx-1]
                  }
                  
                  val base10Val = next.toBase10(k)
                  if (base10Val.isPalindrome()) {
                      ++count
                      sum += base10Val
                  }

                  if (count == n) {
                      breakOut = true
                      break
                  }
                  curr.add(next)
              }
              if (breakOut) break
          }
          if (breakOut) break
          nm2 = nm1
          nm1 = curr
          ++length
      }
      return sum
  }
  
  private fun CharArray.toBase10(base: Int): Long {
      var sum = 0.toLong()
      var factor = 1.toLong()
      for (c in this) {
          sum += factor * (c - '0')
          factor *= base
      }
      return sum
  }
  
  private fun Long.isPalindrome(): Boolean {
      val digits = mutableListOf<Int>()
      var tmp = this
      while (tmp != 0.toLong()) {
          val quot = tmp/10
          val rem = (tmp - 10*quot).toInt()
          digits.add(rem)
          tmp = quot
      }
      for (id in 0 until digits.size/2) {
          if (digits[id] != digits[digits.size - 1 - id]) return false
      }
      return true
  }
}
