// https://leetcode.com/problems/dungeon-game/

#include <utility>
#include <vector>

class Solution {
public:
    int calculateMinimumHP(const std::vector<std::vector<int>>& mat) {
        const int m = mat.size();
        const int n = mat[0].size();
        
        auto maxOf = [](const int x, const int y) { return x > y ? x : y; };
        auto minOf = [](const int x, const int y) { return x < y ? x : y; };
        
        std::vector<int> prev(n);
        std::vector<int> curr(n);
        curr[n - 1] = maxOf(1, 1 - mat[m - 1][n - 1]);
        for (int col = n - 2; col >= 0; --col) {
            curr[col] = maxOf(1, curr[col + 1] - mat[m - 1][col]);
        }
        
        for (int row = m - 2; row >= 0; --row) {
            prev[n - 1] = maxOf(1, curr[n - 1] - mat[row][n - 1]);
            for (int col = n - 2; col >= 0; --col) {
                prev[col] = maxOf(1, minOf(curr[col], prev[col + 1]) - mat[row][col]);
            }
            std::swap(curr, prev);
        }
        return curr[0];
    }
};
