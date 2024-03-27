// https://leetcode.com/problems/escape-a-large-maze/


private const val GRID_SIZE = 1000000

private const val MAX_ENCLOSURE = 20000

private data class Position(val row: Int, val col: Int) {
    fun isInBounds(): Boolean {
        return row >= 0 && row < GRID_SIZE && col >= 0 && col < GRID_SIZE
    }
}

private data class Direction(val rowDelta: Int, val colDelta: Int)

private val directions: List<Direction> = listOf(
    Direction(-1, 0), Direction(0, -1), Direction(0, 1), Direction(1, 0)
)

private operator fun Position.plus(dir: Direction): Position {
    return Position(row + dir.rowDelta, col + dir.colDelta)
}

private enum class Status { END_FOUND, BOUNDED, UNBOUNDED }

private fun bfs(start: Position, end: Position?, blockLookup: Set<Position>): Status {
    var curr = mutableListOf(start)
    val visited = mutableSetOf(start)
    while (!curr.isEmpty() && visited.size < MAX_ENCLOSURE) {
        val next = mutableListOf<Position>()
        for (pos in curr) {
            for (dir in directions) {
                val neighbor = pos + dir
                if (neighbor == end) {
                    return Status.END_FOUND
                }

                if (neighbor.isInBounds() && !visited.contains(neighbor) && !blockLookup.contains(neighbor)) {
                    visited.add(neighbor)
                    next.add(neighbor)
                }
            }
        }
        curr = next
    }
    return if (curr.isEmpty()) Status.BOUNDED else Status.UNBOUNDED
}

class Solution {
    fun isEscapePossible(blocked: Array<IntArray>, source: IntArray, target: IntArray): Boolean {
        // Only impossible if blocked positions partitions the grid into multiple parts, and
        // source and target are in different parts. Number of blocked positions is capped at
        // 200 per problem spec, so enclosed parts can't be too large. A fixed-length bfs from source
        // and target can be used to determine whether source and target are contained within
        // different enclosures.
        val blockLookup = mutableSetOf<Position>()
        for ((row, col) in blocked) {
            blockLookup.add(Position(row, col))
        }
        
        val startPos = Position(source[0], source[1])
        val endPos = Position(target[0], target[1])
        val status = bfs(startPos, endPos, blockLookup)
        return when (status) {
            Status.END_FOUND -> true
            Status.BOUNDED -> false
            Status.UNBOUNDED -> bfs(endPos, null, blockLookup) == Status.UNBOUNDED
        }
    }
}