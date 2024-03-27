// https://leetcode.com/problems/jump-game-v/

#include <algorithm>
#include <numeric>
#include <vector>

class Solution {
public:
    int maxJumps(const std::vector<int>& arr, const int d) {
        const int n = arr.size();
        std::vector<int> sortedIds(n);
        std::iota(sortedIds.begin(), sortedIds.end(), 0);
        std::sort(sortedIds.begin(), sortedIds.end(), [&](const int l, const int r) { return arr[l] < arr[r]; });
        std::vector<int> sols(n, 1);
        int max = 0;
        auto maxOf = [](const int x, const int y) { return x > y ? x : y; };
        for (const int id : sortedIds) {
            for (int jump = 1; jump <= d; ++jump) {
                if (id - jump < 0 || arr[id - jump] >= arr[id]) break;
                sols[id] = maxOf(sols[id], 1 + sols[id - jump]);
            }
            for (int jump = 1; jump <= d; ++jump) {
                if (id + jump >= n || arr[id + jump] >= arr[id]) break;
                sols[id] = maxOf(sols[id], 1 + sols[id + jump]);
            }
            max = maxOf(max, sols[id]);
        }
        return max;
    }
};
