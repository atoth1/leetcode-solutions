// https://leetcode.com/problems/count-and-say/

class Solution {
  fun countAndSay(n: Int): String {
      return if (n == 1) {
          "1"
      } else {
          val prev = countAndSay(n-1)
          val builder = StringBuilder()
          var start = 0;
          while (start < prev.length) {
              var end = start+1
              while (end < prev.length && prev[end] == prev[start]) ++end
              builder.append((end-start).toString()).append(prev[start])
              start = end
          }
          builder.toString()
      }
  }
}
