// https://leetcode.com/problems/reverse-words-in-a-string-iii/

class Solution {
  fun reverseWords(s: String): String {
      var firstWord = true
      var start = 0
      val builder = StringBuilder()
      while (start < s.length) {
          var end = start+1
          while (end < s.length && s[end] != ' ') ++end
          if (firstWord) {
              firstWord = false
          } else {
              builder.append(' ')
          }
          for (pos in (end-1) downTo start) builder.append(s[pos])
          start = end+1
      }
      return builder.toString()
  }
}
