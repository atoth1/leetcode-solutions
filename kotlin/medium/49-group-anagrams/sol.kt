// https://leetcode.com/problems/group-anagrams/

class Solution {
  fun groupAnagrams(strs: Array<String>): List<List<String>> {
      val countsToStrList = mutableMapOf<List<Int>, MutableList<String>>()
      for (str in strs) {
          val counts = IntArray(26)
          for (c in str) {
              ++counts[c - 'a']
          }
          val list = counts.toList()
          countsToStrList[list]?.let {
              it.add(str)
              true
          } ?: run {
              countsToStrList[list] = mutableListOf(str)
          }
      }
      
      val ret = mutableListOf<List<String>>()
      for ((_, list) in countsToStrList) {
          ret.add(list)
      }
      return ret
  }
}
