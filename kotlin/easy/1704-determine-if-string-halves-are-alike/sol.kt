// https://leetcode.com/problems/determine-if-string-halves-are-alike/

class Solution {
  fun halvesAreAlike(s: String): Boolean {
      var leftCount = 0
      var rightCount = 0
      val n = s.length/2
      for (id in 0 until n) {
          if (s[id].isVowel()) ++leftCount
          if (s[n+id].isVowel()) ++rightCount
      }
      return leftCount == rightCount
  }
  
  private fun Char.isVowel(): Boolean {
      return this == 'a' || this == 'e' || this == 'i' || this == 'o' || this == 'u' ||
          this == 'A' || this == 'E' || this == 'I' || this == 'O' || this == 'U'
  }
}
