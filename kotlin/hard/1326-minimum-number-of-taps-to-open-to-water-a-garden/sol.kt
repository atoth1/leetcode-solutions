// https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/

import java.util.PriorityQueue

class Solution {
    
    private data class Interval(val begin: Int, val end: Int)
    
    fun minTaps(n: Int, ranges: IntArray): Int {
        val queue = PriorityQueue<Interval> { x, y -> x.begin - y.begin }
        for (id in 0 until ranges.size) queue.add(Interval(id - ranges[id], id + ranges[id]))
        
        var begin = 0
        var count = 0
        while (!queue.isEmpty()) {
            ++count
            var end = begin
            while (!queue.isEmpty() && queue.peek().begin <= begin) {
                end = maxOf(end, queue.poll().end)
                if (end >= n) return count
            }
            
            if (end == begin) {
                return -1;
            } else {
                begin = end;
            }
        }
        return -1
    }
}
