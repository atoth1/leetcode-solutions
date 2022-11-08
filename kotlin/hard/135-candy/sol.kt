// https://leetcode.com/problems/candy/

enum class Status {
    UNASSIGNED,
    ASSIGNED
}

class Solution {
    fun candy(ratings: IntArray): Int {
        var indices = IntArray(ratings.size) { it }
        val comp = Comparator<Int> { l, r -> ratings[l] - ratings[r] }
        val sortedIndices = indices.sortedWith(comp)
        
        var total = 0
        var scores = Array<Int>(ratings.size) { 0 }
        for (id in sortedIndices) {
            var leftScore = 0
            if (id > 0 && ratings[id - 1] < ratings[id]) {
                    leftScore = scores[id - 1]
            }
            var rightScore = 0
            if (id < ratings.size - 1 && ratings[id + 1] < ratings[id]) {
                    rightScore = scores[id + 1]
            }
            scores[id] += maxOf(leftScore, rightScore) + 1
            total += scores[id]
        }
        return total
    }
}
