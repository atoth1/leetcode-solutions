// https://leetcode.com/problems/delete-columns-to-make-sorted-iii/

#include <algorithm>
#include <string>
#include <vector>

class Solution {
public:
    static int minDeletionSize(const std::vector<std::string>& strs) {
        const int rows = strs.size();
        const int cols = strs[0].size();
        
        auto canExtendPrevCol = [&](const int col, const int prevCol) {
            for (int row = 0; row < rows; ++row) {
                if (strs[row][col] < strs[row][prevCol]) {
                    return false;
                }
            }
            return true;
        };
        
        std::vector<int> dp(cols);
        int min = cols - 1;
        for (int col = 1; col < cols; ++col) {
            dp[col] = col;
            for (int prevCol = 0; prevCol < col; ++prevCol) {
                if (canExtendPrevCol(col, prevCol)) {
                    dp[col] = std::min(dp[col], dp[prevCol] + col - prevCol - 1);
                }
            }
            min = std::min(min, dp[col] + cols - col - 1);
        }
        return min;
    }
};
