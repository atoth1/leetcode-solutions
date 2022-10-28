// https://leetcode.com/problems/check-if-two-string-arrays-are-equivalent/

class Solution {
  fun arrayStringsAreEqual(word1: Array<String>, word2: Array<String>): Boolean {
      val builder1 = StringBuilder()
      for (word in word1) builder1.append(word)
      val builder2 = StringBuilder()
      for (word in word2) builder2.append(word)
      val str1 = builder1.toString()
      val str2 = builder2.toString()
      if (str1.length != str2.length) return false
      for (id in 0 until str1.length) {
          if (str1[id] != str2[id]) return false
      }
      return true
  }
}
