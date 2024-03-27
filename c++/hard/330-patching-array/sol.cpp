// https://leetcode.com/problems/patching-array/

#include <span>

class Solution {
public:
    static int minPatches(const std::span<const int> nums, const int n) {
        // Problem spec guarantees sorted nums, otherwise should copy and sort.
        int addedCount = 0;
        long long maxReachable = 0;
        auto it = nums.begin();
        while (maxReachable < n) {
            if (it != nums.end() && *it <= maxReachable + 1) {
                maxReachable += *it++;
            } else {
                maxReachable += maxReachable + 1;
                ++addedCount;
            }
        }
        return addedCount;
    }
};