// https://leetcode.com/problems/count-subarrays-with-fixed-bounds/

#include <deque>

class Solution {
public:
    long long countSubarrays(vector<int>& nums, int minK, int maxK) {
        int start = 0;
        long long count = 0;
        while (start < nums.size()) {
            if (nums[start] >= minK && nums[start] <= maxK) {
                std::deque<int> minIds{};
                std::deque<int> maxIds{};
                int end = start;
                while (end < nums.size() && nums[end] >= minK && nums[end] <= maxK) {
                    if (nums[end] == minK) minIds.push_back(end);
                    if (nums[end] == maxK) maxIds.push_back(end);
                    ++end;
                }
                
                if (minK == maxK) {
                    long long n = end - start;
                    count += n*(n+1)/2;
                } else {
                    count += contribution(nums, minK, maxK, start, end, minIds, maxIds);
                }
                start = end;
            } else {
                ++start;
            }
        }
        return count;
    }
    
private:
    static long long contribution(
        const std::vector<int>& nums,
        const int min,
        const int max,
        const int start,
        const int end,
        std::deque<int>& minIds,
        std::deque<int>& maxIds
    ) {
        long long contribution = 0;
        int pos = start;
        while (!minIds.empty() && !maxIds.empty()) {
            long long diff = 0;
            if (nums[pos] == min) {
                minIds.pop_front();
                contribution += end - maxIds[0];
            } else if (nums[pos] == max) {
                maxIds.pop_front();
                contribution += end - minIds[0];
            } else {
                int firstReqdId = minIds[0] > maxIds[0] ? minIds[0] : maxIds[0];
                contribution += end - firstReqdId;
            }
            ++pos;
        }
        return contribution;
    }
};