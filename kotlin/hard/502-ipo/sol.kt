// https://leetcode.com/problems/ipo

import java.util.PriorityQueue

class Solution {
    
    private data class Project(val profit: Int, val capital: Int)
    
    fun findMaximizedCapital(
        maxProjects: Int,
        initCapital: Int,
        profits: IntArray,
        capitals: IntArray
    ): Int {
        val projects = mutableListOf<Project>()
        for (n in 0 until profits.size) {
            projects.add(Project(profits[n], capitals[n]))
        }
        projects.sortBy { it.capital }
        
        val queue = PriorityQueue(Comparator<Project> { l, r ->
            r.profit - l.profit
        })
        
        var capital = initCapital
        var pos = 0
        for (repeat in 0 until maxProjects) {
            while (pos < projects.size && projects[pos].capital <= capital) {
                queue.add(projects[pos++])
            }
            
            if (queue.isEmpty()) break
            capital += queue.element().profit
            queue.remove()
        }
        return capital
    }
}