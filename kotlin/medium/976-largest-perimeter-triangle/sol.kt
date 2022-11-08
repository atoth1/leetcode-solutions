// https://leetcode.com/problems/largest-perimeter-triangle/

class Solution {
  fun largestPerimeter(nums: IntArray): Int {
      nums.sort()
      
      var max = 0
      for (id in 0 until nums.size - 2) {
          var sum = nums[id] + nums[id + 1]
          if (nums[id + 2] < sum) {
              sum += nums[id + 2]
              if (sum > max) max = sum
          }
      }
      return max
  }
}
