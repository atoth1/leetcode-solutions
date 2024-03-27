// https://leetcode.com/problems/maximum-number-of-points-from-grid-queries/

import java.util.PriorityQueue

private data class Position(val row: Int, val col: Int)
        
private data class Direction(val rowDelta: Int, val colDelta: Int)

private val dirs = listOf(Direction(-1, 0), Direction(0, -1), Direction(0, 1), Direction(1, 0))

private fun Position.inBounds(rows: Int, cols: Int): Boolean {
    return row >= 0 && row < rows && col >= 0 && col < cols
}

private operator fun Position.plus(dir: Direction): Position {
    return Position(row + dir.rowDelta, col + dir.colDelta)
}

/*
  Would prefer to do something like:
  
  private operator fun <T> Array<List<T>>.get(pos: Position): T {
      return get(pos.row)[pos.col]
  }

  private operator fun <T> Array<MutableList<T>>.set(pos: Position, value: T) {
      get(pos.row).set(pos.col, value)
  }

  but unsure how to accomplish this generically with the typed arrays
 */

private operator fun Array<IntArray>.get(pos: Position): Int {
    return get(pos.row)[pos.col]
}

private operator fun Array<BooleanArray>.get(pos: Position): Boolean {
    return get(pos.row)[pos.col]
}

private operator fun Array<BooleanArray>.set(pos: Position, value: Boolean) {
    get(pos.row).set(pos.col, value)
}

class Solution {
    fun maxPoints(grid: Array<IntArray>, queries: IntArray): IntArray {
        val sortedIds = MutableList(queries.size) { it }
        sortedIds.sortBy { queries[it] }
        
        val rows = grid.size
        val cols = grid[0].size
        
        val reachable = mutableListOf<Position>()
        val unreachable = PriorityQueue<Position> { x, y -> grid[x] - grid[y] }
        val visited = Array(rows) { BooleanArray(cols) }
        
        unreachable.add(Position(0, 0))
        visited[unreachable.peek()] = true
        
        var score = 0
        val ret = IntArray(queries.size)
        for (id in sortedIds) {
            while (!unreachable.isEmpty() && queries[id] > grid[unreachable.peek()]) {
                val newlyReachable = unreachable.poll()
                reachable.add(newlyReachable)
                ++score
            }
            
            while (!reachable.isEmpty()) {
                val pos = reachable.removeLast()
                
                for (dir in dirs) {
                    val newPos = pos + dir
                    if (newPos.inBounds(rows, cols) && !visited[newPos]) {
                        visited[newPos] = true
                        if (queries[id] > grid[newPos]) {
                            reachable.add(newPos)
                            ++score
                        } else {
                            unreachable.add(newPos)
                        }
                    }
                }
            }
            ret[id] = score
        }
        return ret
    }
}
