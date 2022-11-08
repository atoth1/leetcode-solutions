// https://leetcode.com/problems/combination-sum-iv/

class Solution {
  //data class ResultWrapper(var result: Int)
  
  fun combinationSum4(nums: IntArray, target: Int): Int {
      nums.sort()
      //val ret = ResultWrapper(0)
      val cache = mutableMapOf<Int, Int>()
      return impl(nums, target, 0, cache)
  }
  
  private fun impl(
      nums: IntArray, 
      target: Int,
      sum: Int,
      cache: MutableMap<Int, Int>
  ): Int {
      return cache[sum]?.let { cached ->
          cached
      } ?:run {
          var count = 0
          for (num in nums) {
              if (sum + num < target) {
                  count += impl(nums, target, sum + num, cache)
              } else if (sum + num == target) {
                  ++count
              } else {
                  // Sorted input, so any further sums also greater
                  break
              }
          }
          cache[sum] = count
          count
      }
  }
}
