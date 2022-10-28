// https://leetcode.com/problems/flood-fill/

class Solution {
  private data class Position(val row: Int, val col: Int)
  
  fun floodFill(image: Array<IntArray>, sr: Int, sc: Int, color: Int): Array<IntArray> {
      val oldColor = image[sr][sc]
      if (color != oldColor) {
          val pos = mutableSetOf(Position(sr, sc))
          while (!pos.isEmpty()) {
              val curr = pos.first()
              pos.remove(curr)
              image[curr.row][curr.col] = color
              if (curr.row != 0 && image[curr.row - 1][curr.col] == oldColor) {
                  pos.add(Position(curr.row - 1, curr.col))
              }
              if (curr.row != image.size - 1 && image[curr.row + 1][curr.col] == oldColor) {
                  pos.add(Position(curr.row + 1, curr.col))
              }
              if (curr.col != 0 && image[curr.row][curr.col - 1] == oldColor) {
                  pos.add(Position(curr.row, curr.col - 1))
              }
              if (curr.col != image[0].size - 1 && image[curr.row][curr.col + 1] == oldColor) {
                  pos.add(Position(curr.row, curr.col + 1))
              }
          }
      }
      return image
  }
}
