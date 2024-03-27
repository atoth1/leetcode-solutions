// https://leetcode.com/problems/maximum-candies-you-can-get-from-boxes/

class Solution {
    
    private fun processNewBoxes(
        newBoxIds: IntArray,
        openBoxIds: MutableList<Int>,
        closedBoxIds: MutableSet<Int>,
        keyIds: MutableSet<Int>,
        status: IntArray
    ) {
        for (boxId in newBoxIds) {
            if (status[boxId] == 1 || keyIds.contains(boxId)) {
                openBoxIds.add(boxId)
            } else {
                closedBoxIds.add(boxId)
            }
        }
    }
    
    private fun unlockBoxes(
        openBoxIds: MutableList<Int>,
        closedBoxIds: MutableSet<Int>,
        newKeyIds: IntArray,
        keyIds: MutableSet<Int>
    ) {
        for (keyId in newKeyIds) {
            keyIds.add(keyId)
            if (closedBoxIds.contains(keyId)) {
                closedBoxIds.remove(keyId)
                openBoxIds.add(keyId)
            }
        }
    }
    
    fun maxCandies(
        status: IntArray,
        candies: IntArray,
        keys: Array<IntArray>,
        containedBoxes: Array<IntArray>,
        initialBoxes: IntArray
    ): Int {
        val openBoxIds = mutableListOf<Int>()
        val closedBoxIds = mutableSetOf<Int>()
        val keyIds = mutableSetOf<Int>()
        processNewBoxes(initialBoxes, openBoxIds, closedBoxIds, keyIds, status)
        
        var sum = 0
        while (!openBoxIds.isEmpty()) {
            val boxId = openBoxIds.last()
            openBoxIds.removeLast()
            sum += candies[boxId]
            processNewBoxes(containedBoxes[boxId], openBoxIds, closedBoxIds, keyIds, status)
            unlockBoxes(openBoxIds, closedBoxIds, keys[boxId], keyIds)
        }
        return sum
    }
}
