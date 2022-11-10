// https://leetcode.com/problems/edit-distance/

class Solution {
    
  private data class StartIds(val first: Int, val second: Int)
  
  fun minDistance(word1: String, word2: String): Int {
      val cache = mutableMapOf<StartIds, Int>()
      return impl(word1, word2, StartIds(0, 0), cache)
  }
  
  private fun impl(
      word1: String,
      word2: String,
      ids: StartIds,
      cache: MutableMap<StartIds, Int>
  ): Int {
      return cache[ids]?.let {
          it
      } ?: run {
          var id1 = ids.first
          var id2 = ids.second
          while (id1 < word1.length && id2 < word2.length && word1[id1] == word2[id2]) {
              ++id1
              ++id2
          }
          
          if (id1 == word1.length) {
              word2.length - id2
          } else if (id2 == word2.length) {
              word1.length - id1
          } else {
             // Make chars equal with a swap
              val swap = 1 + impl(word1, word2, StartIds(id1+1, id2+1), cache)
              
              // Delete char from word1
              val deleteFirst = 1 + impl(word1, word2, StartIds(id1+1, id2), cache)
              
              // Delete char from word2
              val deleteSecond = 1 + impl(word1, word2, StartIds(id1, id2+1), cache)
              
              val ret = minOf(swap, deleteFirst, deleteSecond)
              cache[ids] = ret
              ret
          }
      }
  }
}
