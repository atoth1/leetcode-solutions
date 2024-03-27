// https://leetcode.com/problems/sudoku-solver/

private data class Row(val contents: MutableSet<Char> = mutableSetOf())

private data class Column(val contents: MutableSet<Char> = mutableSetOf())

private data class Square(val contents: MutableSet<Char> = mutableSetOf())

private fun toSquareId(row: Int, col: Int): Int {
    return 3 * (row / 3) + (col / 3)
}

private fun nextPos(row: Int, col: Int): Pair<Int, Int> {
    return if (col < 8) {
        Pair(row, col + 1)
    } else {
        Pair(row + 1, 0)
    }
}

private class Board(val contents: Array<CharArray>) {
    val rows = Array(9) { Row() }
    val cols = Array(9) { Column() }
    val squares = Array(9) { Square() }
    val frozen = Array(9) { BooleanArray(9) }
    
    init {
        for (row in 0 until 9) {
            for (col in 0 until 9) {
                if (contents[row][col] != '.') {
                    val value = contents[row][col]
                    rows[row].contents.add(value)
                    cols[col].contents.add(value)
                    squares[toSquareId(row, col)].contents.add(value)
                    frozen[row][col] = true
                }
            }
        }
    }
    
    fun insert(row: Int, col: Int, value: Char): Boolean {
        if (
            rows[row].contents.contains(value) ||
            cols[col].contents.contains(value) ||
            squares[toSquareId(row, col)].contents.contains(value)
        ) {
            return false
        }
        
        contents[row][col] = value
        rows[row].contents.add(value)
        cols[col].contents.add(value)
        squares[toSquareId(row, col)].contents.add(value)
        return true
    }
    
    fun reset(row: Int, col: Int) {
        val value = contents[row][col]
        contents[row][col] = '.'
        rows[row].contents.remove(value)
        cols[col].contents.remove(value)
        squares[toSquareId(row, col)].contents.remove(value)
    }
}

private fun impl(board: Board, row: Int, col: Int): Boolean {
    if (row == 9) return true
    
    val (nextRow, nextCol) = nextPos(row, col)
    if (board.frozen[row][col]) return impl(board, nextRow, nextCol)
    
    for (candidate in '1' .. '9') {
        if (board.insert(row, col, candidate)) {
            if (impl(board, nextRow, nextCol)) {
                return true
            }
            board.reset(row, col)
        }
        
    }
    return false
}

class Solution {
    fun solveSudoku(board: Array<CharArray>): Unit {
        impl(Board(board), 0, 0)
    }
}
