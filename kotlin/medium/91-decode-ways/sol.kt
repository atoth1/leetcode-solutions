// https://leetcode.com/problems/decode-ways/

class Solution {
  fun numDecodings(s: String): Int {
      return impl(s, 0, IntArray(s.length) {-1})
  }
  
  private fun impl(s: String, pos: Int, cache: IntArray): Int {
      if (pos == s.length) return 1
      
      if (cache[pos] == -1) {
          if (s[pos] == '0') cache[pos] = 0
          else {
              cache[pos] = impl(s, pos+1, cache)
              if (pos < s.length-1 && (s[pos] == '1' || (s[pos] == '2' && (s[pos+1] >= '0' && s[pos+1] <= '6')))) {
                  cache[pos] += impl(s, pos+2, cache)
              }
          }
      }
      return cache[pos]
  }
}
