// https://leetcode.com/problems/minimum-swaps-to-arrange-a-binary-grid/

class Solution {
    
  fun minSwaps(grid: Array<IntArray>): Int {
      val n = grid.size
      val lastOnePos = IntArray(n)
      grid.forEachIndexed { row, rowValues ->
          var pos = n - 1
          while (pos >= 0 && rowValues[pos] == 0) --pos
          lastOnePos[row] = pos
      }
      
      var swaps = 0
      for (id in lastOnePos.indices) {
          var validId = id
          while (validId < n && lastOnePos[validId] > id) ++validId
          if (validId == n) return -1
          for (swapId in validId downTo id + 1) {
              lastOnePos[swapId] = lastOnePos[swapId - 1].also {
                  lastOnePos[swapId - 1] = lastOnePos[swapId]
              }
              ++swaps
          }
      }
      return swaps
  }
}
