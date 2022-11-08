// https://leetcode.com/problems/increasing-triplet-subsequence/

class Solution {
  fun increasingTriplet(nums: IntArray): Boolean {
      var middleId = -1
      var maxId = nums.size - 1
      for (id in nums.size - 2 downTo 0) {
          if (nums[id] > nums[maxId]) {
              maxId = id
          } else if (nums[id] < nums[maxId]) {
              if (middleId == -1 || nums[id] > nums[middleId]) {
                  middleId = id
              } else if (nums[id] < nums[middleId]) {
                  return true
              }
          }
      }
      return false
  }
}
