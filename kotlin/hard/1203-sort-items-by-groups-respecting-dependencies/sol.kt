// https://leetcode.com/problems/sort-items-by-groups-respecting-dependencies/

import java.util.Stack

class Solution {
    
    private data class Node(
        val incoming: MutableSet<Int> = mutableSetOf(),
        val outgoing: MutableSet<Int> = mutableSetOf()
    )
    
    private fun topoSort(ids: List<Int>, reqs: List<Pair<Int, Int>>): List<Int> {
        val idToNode = mutableMapOf<Int, Node>()
        for (id in ids) idToNode[id] = Node()
        for ((id, prereqId) in reqs) {
            idToNode[id]!!.incoming.add(prereqId)
            idToNode[prereqId]!!.outgoing.add(id)
        }
        
        val noIncoming = Stack<Int>()
        for ((id, node) in idToNode) {
            if (node.incoming.isEmpty()) noIncoming.push(id)
        }
        
        val ret = mutableListOf<Int>()
        while (!noIncoming.empty()) {
            val id = noIncoming.peek()
            noIncoming.pop()
            ret.add(id)
            
            for (dependentId in idToNode[id]!!.outgoing) {
                val dependentNode = idToNode[dependentId]!!
                dependentNode.incoming.remove(id)
                if (dependentNode.incoming.isEmpty()) noIncoming.push(dependentId)
            }
        }
        return ret
    }
    
    fun sortItems(n: Int, m: Int, group: IntArray, beforeItems: List<List<Int>>): IntArray {
        val idToGroupId = mutableListOf<Int>()
        val groupIdToIds = mutableMapOf<Int, MutableList<Int>>()
        var groupCount = m
        for (groupId in 0 until m) groupIdToIds[groupId] = mutableListOf()
        for (id in 0 until n) {
            var groupId = group[id]
            if (groupId == -1) {
                groupId = groupCount++
            }
            idToGroupId.add(groupId)
            groupIdToIds.getOrPut(groupId) { mutableListOf() }.add(id)
        }
        
        val groupReqs = mutableListOf<Pair<Int, Int>>()
        val inGroupReqs = Array(groupCount) { mutableListOf<Pair<Int, Int>>() }
        for (id in 0 until n) {
            for (otherId in beforeItems[id]) {
                if (idToGroupId[id] == idToGroupId[otherId]) {
                    inGroupReqs[idToGroupId[id]].add(Pair(id, otherId))
                } else {
                    groupReqs.add(Pair(idToGroupId[id], idToGroupId[otherId]))
                }
            }
        }
        
        val sortedGroupIds = topoSort((0 until groupCount).toList(), groupReqs)
        val sortedInGroupIds = Array(groupCount) { topoSort(groupIdToIds[it]!!, inGroupReqs[it]) }
        val ret = mutableListOf<Int>()
        for (groupId in sortedGroupIds) {
            ret.addAll(sortedInGroupIds[groupId])
        }
        return if (ret.size == n) ret.toIntArray() else IntArray(0)
    }
}
