// https://leetcode.com/problems/maximum-number-of-darts-inside-of-a-circular-dartboard/

import kotlin.math.sqrt

private data class Point(val x: Double, val y: Double)

private val IntArray.x: Int
    get() = get(0)

private val IntArray.y: Int
    get() = get(1)

private fun getCandidateCenters(pt1: IntArray, pt2: IntArray, radius: Int): List<Point> {
    val deltaX = pt2.x - pt1.x
    val deltaY = pt2.y - pt1.y
    val distSq = deltaX * deltaX + deltaY * deltaY
    if (distSq > 4 * radius * radius) {
        return emptyList()
    } else if (distSq == 4 * radius * radius) {
        return listOf(Point(0.5 * (pt1.x + pt2.x), 0.5 * (pt1.y + pt2.y)))
    } else {
        val a = deltaX * (pt1.x + pt2.x) + deltaY * (pt1.y + pt2.y)
        if (deltaX != 0) {
            val b = 0.5 * a / deltaX
            val c = deltaY.toDouble() / deltaX
            val d = b - pt1.x
            val u = c * c + 1
            val v = c * d + pt1.y
            val w = d * d + pt1.y * pt1.y - radius * radius
            val root = sqrt(v * v - u * w)
            val y1 = (v + root) / u
            val x1 = b - c * y1
            val y2 = (v - root) / u
            val x2 = b - c * y2
            return listOf(Point(x1, y1), Point(x2, y2))
        } else {
            val b = 0.5 * a / deltaY
            val c = deltaX.toDouble() / deltaY
            val d = b - pt1.y
            val u = c * c + 1
            val v = c * d + pt1.x
            val w = d * d + pt1.x * pt1.x - radius * radius
            val root = sqrt(v * v - u * w)
            val x1 = (v + root) / u
            val y1 = b - c * x1
            val x2 = (v - root) / u
            val y2 = b - c * x2
            return listOf(Point(x1, y1), Point(x2, y2))
        }
    }
}

private class Circle(private val center: Point, private val radius: Int) {
    
    companion object {
        // Tiny little padding since we're dealing with floating point comparisons
        const val epsilon = 1.0e-14
    }
    
    fun contains(point: IntArray): Boolean {
        val xDelta = center.x - point.x
        val yDelta = center.y - point.y
        val paddedRadius = radius + epsilon
        return xDelta * xDelta + yDelta * yDelta <= paddedRadius * paddedRadius
    }
}

class Solution {
    fun numPoints(darts: Array<IntArray>, r: Int): Int {
        var max = 1
        for (id1 in 0 until darts.size) {
            for (id2 in id1 + 1 until darts.size) {
                val candidates = getCandidateCenters(darts[id1], darts[id2], r)
                for (candidate in candidates) {
                    val circle = Circle(candidate, r)
                    max = maxOf(max, darts.count { circle.contains(it) })
                }
            }
        }
        return max
    }
}
