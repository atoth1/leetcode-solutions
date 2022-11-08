// https://leetcode.com/problems/maximum-number-of-words-found-in-sentences/

class Solution {
  fun mostWordsFound(sentences: Array<String>): Int {
      var max = 0
      for (sentence in sentences) {
          val thisCount = 1 + sentence.count { it == ' ' }
          if (thisCount > max) max = thisCount
      }
      return max
  }
}
