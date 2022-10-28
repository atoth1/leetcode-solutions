// https://leetcode.com/problems/global-and-local-inversions/

class Solution {
  fun isIdealPermutation(nums: IntArray): Boolean {
      var prevMax= nums[0]
      for (id in 2 until nums.size) {
          if (prevMax > nums[id]) return false
          if (nums[id-1] > prevMax) prevMax= nums[id-1]
      }
      return true
  }
}
