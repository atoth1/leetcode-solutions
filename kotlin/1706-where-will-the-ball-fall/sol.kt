// https://leetcode.com/problems/where-will-the-ball-fall/

class Solution {
  fun findBall(grid: Array<IntArray>): IntArray {
      val n = grid[0].size
      
      // Easy short circuit
      if (n == 1) return IntArray(1) { -1 }
      
      // Pure simulation
      val pos = IntArray(n) { it }
      grid.forEach { row ->
          pos.forEachIndexed { id, col ->
              if (col != -1) {
                  pos[id] = if (((col == 0 || row[col-1] == 1) && row[col] == -1) ||
                          ((col == n-1 || row[col+1] == -1) && row[col] == 1)) {
                      -1
                  } else if (row[col] == -1) {
                      col - 1
                  } else {
                      col + 1
                  }
              }
          }
      }
      return pos
  }
}
