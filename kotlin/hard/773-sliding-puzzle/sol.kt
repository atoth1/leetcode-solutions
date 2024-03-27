// https://leetcode.com/problems/sliding-puzzle/

class Solution {
    
    private data class State(val board: List<MutableList<Int>>) {
        val rows = board.size
        
        val cols = board[0].size
        
        data class Position(val row: Int, val col: Int)
        
        fun openPos(): Position {
            var ret = Position(-1, -1)
            for (row in 0 until rows) {
                for (col in 0 until cols) {
                    if (board[row][col] == 0) ret = Position(row, col)
                }
            }
            return ret
        }
        
        infix fun isEqualTo(other: State): Boolean {
            for (row in 0 until rows) {
                for (col in 0 until cols) {
                    if (board[row][col] != other.board[row][col]) return false
                }
            }
            return true
        }
    }
    
    private fun doBfs(initState: State): Int {
        val targetState = State(listOf(mutableListOf(1, 2, 3), mutableListOf(4, 5, 0)))
        if (initState isEqualTo targetState) return 0
        
        var currStates = mutableListOf(initState)
        val seen = mutableSetOf(initState)
        var moves = 0
        while (!currStates.isEmpty()) {
            ++moves
            val nextStates = mutableListOf<State>()
            for (state in currStates) {
                val (row, col) = state.openPos()
                if (row > 0) {
                    val candidate = State(listOf(state.board[0].toMutableList(), state.board[1].toMutableList()))
                    candidate.board[row][col] = candidate.board[row - 1][col]
                    candidate.board[row - 1][col] = 0
                    if (candidate isEqualTo targetState) return moves
                    if (!seen.contains(candidate)) {
                        nextStates.add(candidate)
                        seen.add(candidate)
                    }
                }
                if (row < state.rows - 1) {
                    val candidate = State(listOf(state.board[0].toMutableList(), state.board[1].toMutableList()))
                    candidate.board[row][col] = candidate.board[row + 1][col]
                    candidate.board[row + 1][col] = 0
                    if (candidate isEqualTo targetState) return moves
                    if (!seen.contains(candidate)) {
                        nextStates.add(candidate)
                        seen.add(candidate)
                    }
                }
                if (col > 0) {
                    val candidate = State(listOf(state.board[0].toMutableList(), state.board[1].toMutableList()))
                    candidate.board[row][col] = candidate.board[row][col - 1]
                    candidate.board[row][col - 1] = 0
                    if (candidate isEqualTo targetState) return moves
                    if (!seen.contains(candidate)) {
                        nextStates.add(candidate)
                        seen.add(candidate)
                    }
                }
                if (col < state.cols - 1) {
                    val candidate = State(listOf(state.board[0].toMutableList(), state.board[1].toMutableList()))
                    candidate.board[row][col] = candidate.board[row][col + 1]
                    candidate.board[row][col + 1] = 0
                    if (candidate isEqualTo targetState) return moves
                    if (!seen.contains(candidate)) {
                        nextStates.add(candidate)
                        seen.add(candidate)
                    }
                }
            }
            currStates = nextStates
        }
        return -1
    }
    
    fun slidingPuzzle(board: Array<IntArray>): Int {
        return doBfs(State(listOf(board[0].toMutableList(), board[1].toMutableList())))
    }
}
