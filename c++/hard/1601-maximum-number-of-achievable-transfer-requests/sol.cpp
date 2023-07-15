// https://leetcode.com/problems/maximum-number-of-achievable-transfer-requests/

#include <algorithm>
#include <cstdint>
#include <vector>

class Solution {
public:
    int maximumRequests(int n, const std::vector<std::vector<int>>& requests) {
        auto popCount = [](std::uint32_t mask) {
            int count = 0;
            while (mask) {
                if (mask & 1) ++count;
                mask >>= 1;
            }
            return count;
        };
        
        std::vector<int> netChange(n);
        int max = 0;
        for (std::uint32_t mask = 1; mask < (1 << requests.size()); ++mask) {
            const int satisfiedRequests = popCount(mask);
            if (satisfiedRequests <= max) continue;
            
            std::fill(netChange.begin(), netChange.end(), 0);
            for (int requestId = 0; requestId < requests.size(); ++requestId) {
                if (mask & (1 << requestId)) {
                    --netChange[requests[requestId][0]];
                    ++netChange[requests[requestId][1]];
                }
            }
            
            if (std::all_of(netChange.cbegin(), netChange.cbegin() + n, [](const int num) { return num == 0; })) {
                if (satisfiedRequests > max) max = satisfiedRequests;
            }
        }
        return max;
    }
};
