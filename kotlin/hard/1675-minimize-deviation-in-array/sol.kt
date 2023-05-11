// https://leetcode.com/problems/minimize-deviation-in-array/

class Solution {
  fun minimumDeviation(nums: IntArray): Int {
      val values = sortedSetOf<Int>()
      nums.forEach { num ->
          if ((num and 1) == 0) {
              values.add(num)
          } else {
              values.add(2*num)
          }
      }
      
      val deviation = { set: SortedSet<Int> -> set.last() - set.first() }
      var min = deviation(values)
      while (values.size > 1) {
          val largest = values.last()
          if ((largest and 1) == 1) break
          
          values.remove(largest)
          values.add(largest/2)
          min = minOf(min, deviation(values))
      }
      return min
  }
}