// https://leetcode.com/problems/unique-paths-iii/

class Solution {
    
  private data class Position(val row: Int, val col: Int)
  
  fun uniquePathsIII(grid: Array<IntArray>): Int {
      lateinit var start: Position
      lateinit var end: Position
      var walkable = 2
      for (row in 0 until grid.size) {
          for (col in 0 until grid[0].size) {
              if (grid[row][col] == 0) {
                  ++walkable
              }
              if (grid[row][col] == 1) {
                  start = Position(row, col)
              }
              if (grid[row][col] == 2) {
                  end = Position(row, col)
              }
          }
      }
      return impl(start, end, walkable, grid)
  }
  
  private fun impl(start: Position, end: Position, walkable: Int, grid: Array<IntArray>): Int {
      if (start == end) {
          return if (walkable == 1) 1 else 0
      } else {
          var sum = 0

          // Set this to obstacle so recursive calls can't return to this position
          grid[end.row][end.col] = -1

          if (end.row > 0 && grid[end.row-1][end.col] != -1) {
              sum += impl(start, Position(end.row-1, end.col), walkable-1, grid)
          }
          if (end.row < grid.size - 1 && grid[end.row+1][end.col] != -1) {
              sum += impl(start, Position(end.row+1, end.col), walkable-1, grid)
          }
          if (end.col > 0 && grid[end.row][end.col-1] != -1) {
              sum += impl(start, Position(end.row, end.col-1), walkable-1, grid)
          }
          if (end.col < grid[0].size - 1 && grid[end.row][end.col+1] != -1) {
              sum += impl(start, Position(end.row, end.col+1), walkable-1, grid)
          }

          // Unset obstacle, don't really care if it was previously 1 or 2, only needed
          // that to find initial start and end positions.
          grid[end.row][end.col] = 0

          return sum
      }
  }
}
