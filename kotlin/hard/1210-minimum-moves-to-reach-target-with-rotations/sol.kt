// https://leetcode.com/problems/minimum-moves-to-reach-target-with-rotations/

class Solution {
    
    private data class TailPosition(val row: Int, val col: Int)
    
    private enum class Orientation {
        HORIZONTAL,
        VERTICAL;
        
        fun flip(): Orientation {
            return when (this) {
                HORIZONTAL -> VERTICAL
                VERTICAL -> HORIZONTAL
            }
        }
    }
    
    private data class State(val tailPos: TailPosition, val orient: Orientation)
    
    fun minimumMoves(grid: Array<IntArray>): Int {
        val n = grid.size
        if (n < 2 || grid[0][0] == 1 || grid[0][1] == 1 || grid[n - 1][n - 2] == 1 || grid[n - 1][n - 1] == 1) {
            return -1
        }
        
        val initialState = State(TailPosition(0, 0), Orientation.HORIZONTAL)
        val targetState = State(TailPosition(n - 1, n - 2), Orientation.HORIZONTAL)
        var curr = mutableListOf(initialState)
        val visited = mutableSetOf(initialState)
        var moves = 0
        
        val isValidSpace = { row: Int, col: Int -> row < n && col < n && grid[row][col] == 0 }
        
        val isValidState = { state: State ->
            if (isValidSpace(state.tailPos.row, state.tailPos.col)) {
                if (state.orient == Orientation.HORIZONTAL) {
                    isValidSpace(state.tailPos.row, state.tailPos.col + 1)
                } else {
                    isValidSpace(state.tailPos.row + 1, state.tailPos.col)
                }
            } else {
                false
            }
        }
        
        val getMoves = { state: State ->
            val candidate1 = state.copy(tailPos = TailPosition(state.tailPos.row, state.tailPos.col + 1))
            val state1 = if (isValidState(candidate1)) candidate1 else null
            val candidate2 = state.copy(tailPos = TailPosition(state.tailPos.row + 1, state.tailPos.col))
            val state2 = if (isValidState(candidate2)) candidate2 else null
            val candidate3 = state.copy(orient = state.orient.flip())
            val state3 = if (isValidSpace(state.tailPos.row + 1, state.tailPos.col + 1) && isValidState(candidate3)) {
                candidate3
            } else {
                null
            }
            Triple(state1, state2, state3)
        }
        
        val success = { state: State? -> state == targetState }
        
        val addUnvisitedState = { next: MutableList<State>, state: State? ->
            if (state != null && !visited.contains(state)) {
                next.add(state)
                visited.add(state)
            }
        }
        
        while (!curr.isEmpty()) {
            ++moves
            val next = mutableListOf<State>()
            for (state in curr) {
                val (rightState, downState, rotatedState) = getMoves(state)
                if (success(rightState) || success(downState) || success(rotatedState)) return moves
                addUnvisitedState(next, rightState)
                addUnvisitedState(next, downState)
                addUnvisitedState(next, rotatedState)
            }
            curr = next
        }
        return -1
    }
}
