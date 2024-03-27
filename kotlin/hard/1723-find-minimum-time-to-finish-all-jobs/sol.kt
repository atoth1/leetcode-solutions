// https://leetcode.com/problems/find-minimum-time-to-finish-all-jobs/

class Solution {
    
    private data class IntWrapper(var value: Int)
    
    private fun impl(
        jobs: IntArray,
        jobId: Int,
        buckets: IntArray,
        currMax: Int,
        limit: Int,
        min: IntWrapper
    ) {
        if (jobId == jobs.size) {
            min.value = minOf(min.value, currMax)
        } else {
            for (bucketId in 0 until buckets.size) {
                if (buckets[bucketId] < limit) {
                    buckets[bucketId] += jobs[jobId]
                    impl(jobs, jobId + 1, buckets, maxOf(currMax, buckets[bucketId]), limit, min)
                    buckets[bucketId] -= jobs[jobId]
                }
                
                if (buckets[bucketId] == 0) {
                    break
                }
            }
        }
    }
    
    fun minimumTimeRequired(jobs: IntArray, k: Int): Int {
        val buckets = IntArray(k)
        val currMax = 0
        val limit = (jobs.reduce { sum, num -> sum + num } + k - 1) / k
        val ret = IntWrapper(Int.MAX_VALUE)
        impl(jobs, 0, buckets, currMax, limit, ret)
        return ret.value
    }
}
