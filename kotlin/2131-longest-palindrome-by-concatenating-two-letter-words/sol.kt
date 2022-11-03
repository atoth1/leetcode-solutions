// https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/

class Solution {
  fun longestPalindrome(words: Array<String>): Int {
      val counts = mutableMapOf<String, Int>()
      for (word in words) { 
          counts[word] = counts[word]?.let { it + 1 } ?: 1
      }
      
      var sum = 0
      var unmatchedMiddle = false
      for (first in 'a' .. 'z') {
          val same = counts["$first$first"] ?: 0
          val quot = same/2
          val rem = same - 2*quot
          sum += 4 * quot
          if (rem == 1) unmatchedMiddle = true
          for (second in (first+1) .. 'z') {
              val forward = counts["$first$second"] ?: 0
              val backward = counts["$second$first"] ?: 0
              sum += 4 * minOf(forward, backward)
          }
      }
      return if (unmatchedMiddle) sum + 2 else sum
  }
}
