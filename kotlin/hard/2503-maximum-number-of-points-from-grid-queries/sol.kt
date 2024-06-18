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

private interface TypedArrayWrapper<T> {
    operator fun get(id: Int): T

    operator fun set(id: Int, value: T)
}

private class IntArrayWrapper(private val underlying: IntArray) : TypedArrayWrapper<Int> {
    override operator fun get(id: Int): Int {
        return underlying[id]
    }

    override operator fun set(id: Int, value: Int) {
        underlying[id] = value
    }
}

private class BooleanArrayWrapper(private val underlying: BooleanArray) : TypedArrayWrapper<Boolean> {
    override operator fun get(id: Int): Boolean {
        return underlying[id]
    }

    override operator fun set(id: Int, value: Boolean) {
        underlying[id] = value
    }
}

private operator fun <T, Wrapper: TypedArrayWrapper<T>> Array<Wrapper>.get(pos: Position): T {
    return this[pos.row][pos.col]
}

private operator fun <T, Wrapper: TypedArrayWrapper<T>> Array<Wrapper>.set(pos: Position, value: T) {
    this[pos.row][pos.col] = value
}

class Solution {
    fun maxPoints(grid: Array<IntArray>, queries: IntArray): IntArray {
        val sortedIds = MutableList(queries.size) { it }
        sortedIds.sortBy { queries[it] }
        
        val rows = grid.size
        val cols = grid[0].size
        
        val gridWrapper = Array(rows) { IntArrayWrapper(grid[it]) }
        val reachable = mutableListOf<Position>()
        val unreachable = PriorityQueue<Position> { x, y -> gridWrapper[x] - gridWrapper[y] }
        val visited = Array(rows) { BooleanArrayWrapper(BooleanArray(cols)) }
        
        unreachable.add(Position(0, 0))
        visited[unreachable.peek()] = true
        
        var score = 0
        val ret = IntArray(queries.size)
        for (id in sortedIds) {
            while (!unreachable.isEmpty() && queries[id] > gridWrapper[unreachable.peek()]) {
                reachable.add(unreachable.poll())
                ++score
            }
            
            while (!reachable.isEmpty()) {
                val pos = reachable.removeLast()
                
                for (dir in dirs) {
                    val newPos = pos + dir
                    if (newPos.inBounds(rows, cols) && !visited[newPos]) {
                        visited[newPos] = true
                        if (queries[id] > gridWrapper[newPos]) {
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

