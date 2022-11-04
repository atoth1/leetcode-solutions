// https://leetcode.com/problems/reverse-vowels-of-a-string/

class Solution {
  fun reverseVowels(s: String): String {
      val ret = s.toCharArray()
      var first = 0
      var last = s.length - 1
      while (first < last) {
          while (first < last && !s[first].isVowel()) ++first
          if (first == last) break
          while (first < last && !s[last].isVowel()) --last
          if (first == last) break
          ret[first] = s[last].also { ret[last] = s[first] }
          ++first
          --last
      }
      return ret.joinToString("")
  }
  
  private fun Char.isVowel(): Boolean {
      return equals('a') || equals('e') || equals('i') || equals('o') || equals('u') ||
          equals('A') || equals('E') || equals('I') || equals('O') || equals('U')
  }
}
