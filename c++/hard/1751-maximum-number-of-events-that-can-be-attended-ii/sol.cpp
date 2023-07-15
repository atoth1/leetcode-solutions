// https://leetcode.com/problems/maximum-number-of-events-that-can-be-attended-ii/

#include <algorithm>
#include <vector>

class Solution {
public:
    int maxValue(std::vector<std::vector<int>>& events, int k) {
        auto comp = [](const std::vector<int>& l, const std::vector<int>& r) {
            return l[0] < r[0];
        };
        std::sort(events.begin(), events.end(), comp);
        
        auto maxOf = [](const int x, const int y) { return x > y ? x : y; };
        
        const int n = events.size();
        std::vector<std::vector<int>> dp(k + 1, std::vector<int>(n + 1));
        
        for (int index = n - 1; index >= 0; --index) {
            const int nextIndex = std::upper_bound(events.cbegin(),
                events.cend(), std::vector<int>{ events[index][1] }, comp) - events.cbegin();
            for (int count = 1; count <= k; ++count) {
                dp[count][index] = maxOf(dp[count][index + 1], events[index][2] + dp[count - 1][nextIndex]);
            }
        }
        return dp[k][0];
    }
};
