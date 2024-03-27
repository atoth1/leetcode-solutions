// https://leetcode.com/problems/find-k-th-smallest-pair-distance/

#include <algorithm>
#include <iterator>
#include <span>

class Solution {
public:
    static int smallestDistancePair(const std::span<const int> nums, const int k) {
        std::vector<int> sortedNums(nums.begin(), nums.end());
        std::sort(sortedNums.begin(), sortedNums.end());
        if (sortedNums.front() == sortedNums.back()) return 0;
        
        auto validDistance = [&](const int candidateDist) {
            int pairCount = 0;
            auto end = sortedNums.begin();
            for (auto begin = sortedNums.begin(); begin != sortedNums.end(); ++begin) {
                while (end != sortedNums.end() && *end - *begin <= candidateDist) {
                    ++end;
                }
                pairCount += std::distance(begin, end) - 1;
            }
            return pairCount >= k;
        };
        
        int l = -1;
        int r = sortedNums.back() - sortedNums.front();
        while (l + 1 != r) {
            const int m = l + (r - l) / 2;
            if (validDistance(m)) {
                r = m;
            } else {
                l = m;
            }
        }
        return r;
    }
};
