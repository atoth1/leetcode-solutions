// https://leetcode.com/problems/tuple-with-same-product/

class Solution {
  fun tupleSameProduct(nums: IntArray): Int {
      val prodToCount = mutableMapOf<Int, Int>()
      for (first in 0 until nums.size-1) {
          for (second in first+1 until nums.size) {
              val prod = nums[first] * nums[second]
              prodToCount[prod] = prodToCount[prod]?.let {
                  it+1
              } ?: run {
                  1
              }
          }
      }
      
      var total = 0
      for ((prod, count) in prodToCount) {
          total += (count*(count-1))/2
      }
      return 8*total
  }
}
