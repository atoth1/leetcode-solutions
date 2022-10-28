// https://leetcode.com/problems/product-of-array-except-self/

class Solution {
  fun productExceptSelf(nums: IntArray): IntArray {
      val n =  nums.size
      val prefix = IntArray(n)
      prefix[0] = 1
      val postfix = IntArray(n)
      postfix[n - 1] = 1
      for (id in 1 until n) {
          prefix[id] = prefix[id - 1] * nums[id - 1]
          postfix[n - 1 - id] = postfix[n - id] * nums[n - id]
      }
      
      val ret = IntArray(nums.size)
      for (id in nums.indices) {
          ret[id] = prefix[id] * postfix[id]
      }
      return ret
  }
}
