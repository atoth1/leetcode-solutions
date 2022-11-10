// https://leetcode.com/problems/number-of-excellent-pairs/

class Solution {

  private fun Int.popcount(): Int {
      val mask = 1
      var count = 0
      for (bit in 0 until 31) {
          val shifted = mask shl bit
          val bitExists = this and shifted
          if (bitExists != 0) ++count
      }
      return count
  }
  
  private data class Data(val value: Int, val popcount: Int)
  
  fun countExcellentPairs(nums: IntArray, k: Int): Long {
      val data = Array<Data>(nums.size) {
          Data(nums[it], nums[it].popcount())
      }
      
      val comp = Comparator<Data> { l, r ->
          if (l.popcount == r.popcount) {
              l.value - r.value
          } else {
              r.popcount - l.popcount
          }
      }
      data.sortWith(comp)
      
      val unique = mutableListOf<Data>()
      for (id in 0 until data.size) {
          if (id == 0 || data[id].value != data[id-1].value) {
              unique.add(data[id])
          }
      }
      
      var count = 0.toLong()
      var begin = 0
      var end = unique.size
      while (begin != end) {
          if (2*unique[begin].popcount < k) break
          // Pair of value with itself
          ++count
          
          while (begin != end && unique[begin].popcount + unique[end-1].popcount < k) --end
          // 2x for (a, b)/(b, a) swap
          count += 2*(end - begin - 1)
          ++begin
      }
      return count
  }
}
