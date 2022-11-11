// https://leetcode.com/problems/longest-increasing-path-in-a-matrix/

class Solution {
    
  companion object {
      const val UNSET = -1
  }
  
  fun longestIncreasingPath(matrix: Array<IntArray>): Int {
      val maxPaths = Array(matrix.size) { IntArray(matrix[0].size) { UNSET } }
      var max = 0
      for (row in 0 until matrix.size) {
          for (col in 0 until matrix[0].size) { 
              val thisMax = impl(row, col, matrix, maxPaths)
              if (thisMax > max) max = thisMax
          }
      }
      return max
  }
  
  private fun impl(row: Int, col: Int, mat: Array<IntArray>, maxPaths: Array<IntArray>): Int {
      if (maxPaths[row][col] == UNSET) {
          var max = 1
          if (row > 0 && mat[row][col] < mat[row-1][col]) {
              max = 1 + impl(row-1, col, mat, maxPaths)
          }
          if (row < mat.size-1 && mat[row][col] < mat[row+1][col]) {
              val thisPath = 1 + impl(row+1, col, mat, maxPaths)
              if (thisPath > max) max = thisPath
          }
          if (col > 0 && mat[row][col] < mat[row][col-1]) {
              val thisPath = 1 + impl(row, col-1, mat, maxPaths)
              if (thisPath > max) max = thisPath
          }
          if (col < mat[0].size-1 && mat[row][col] < mat[row][col+1]) {
              val thisPath = 1 + impl(row, col+1, mat, maxPaths)
              if (thisPath > max) max = thisPath
          }
          maxPaths[row][col] = max
      }
      return maxPaths[row][col]
  }
}
