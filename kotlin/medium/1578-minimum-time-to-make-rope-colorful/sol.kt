// https://leetcode.com/problems/minimum-time-to-make-rope-colorful/

class Solution {
  fun minCost(colors: String, neededTime: IntArray): Int {
      val n = colors.length
      var total = 0
      var pos = 0
      while (pos < n - 1) {
          var end = pos + 1
          var sum = neededTime[pos]
          var max = neededTime[pos]
          while (end < n && colors[pos] == colors[end]) {
              sum += neededTime[end]
              max = if (neededTime[end] > max) neededTime[end] else max
              ++end
          }
          total += sum - max
          pos = end
      }
      return total
  }
}
