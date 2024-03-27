// https://leetcode.com/problems/grid-illumination/

private data class Position(val row: Int, val col: Int)

private data class Direction(val rowDelta: Int, val colDelta: Int)

private operator fun Position.plus(dir: Direction): Position = Position(row + dir.rowDelta, col + dir.colDelta)

private val stencil = listOf(
    Direction(-1, -1), Direction(-1, 0), Direction(-1, 1),
    Direction(0, -1), Direction(0, 0), Direction(0, 1),
    Direction(1, -1), Direction(1, 0), Direction(1, 1)
)

class Solution {
    fun gridIllumination(n: Int, lamps: Array<IntArray>, queries: Array<IntArray>): IntArray {
        val rowCounts = mutableMapOf<Int, Int>()
        val colCounts = mutableMapOf<Int, Int>()
        val rowPlusColCounts = mutableMapOf<Int, Int>()
        val rowMinusColCounts = mutableMapOf<Int, Int>()
        val positions = mutableSetOf<Position>()
        for ((row, col) in lamps) {
            val pos = Position(row, col)
            if (!positions.contains(pos)) {
                rowCounts[row] = 1 + rowCounts.getOrPut(row) { 0 }
                colCounts[col] = 1 + colCounts.getOrPut(col) { 0 }
                rowPlusColCounts[row + col] = 1 + rowPlusColCounts.getOrPut(row + col) { 0 }
                rowMinusColCounts[row - col] = 1 + rowMinusColCounts.getOrPut(row - col) { 0 }
                positions.add(pos)
            }
        }
        
        val reduceCount = { countMap: MutableMap<Int, Int>, key: Int ->
            countMap[key]?.let { count ->
                if (count > 1) {
                    countMap[key] = count - 1
                } else {
                    countMap.remove(key)
                }
            }
        }
        
        val ret = IntArray(queries.size)
        for (id in 0 until queries.size) {
            val pos = Position(queries[id][0], queries[id][1])
            with (pos) {
                if (
                    rowCounts.contains(row) ||
                    colCounts.contains(col) ||
                    rowPlusColCounts.contains(row + col) ||
                    rowMinusColCounts.contains(row - col)
                ) {
                    ret[id] = 1
                }
            }
            
            for (dir in stencil) {
                val neighbor = pos + dir
                if (positions.contains(neighbor)) {
                    with (neighbor) {
                        reduceCount(rowCounts, row)
                        reduceCount(colCounts, col)
                        reduceCount(rowPlusColCounts, row + col)
                        reduceCount(rowMinusColCounts, row - col)
                    }
                    positions.remove(neighbor)
                }
            }
        }
        return ret
    }
}
