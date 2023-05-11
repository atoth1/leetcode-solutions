// https://leetcode.com/problems/paths-in-matrix-whose-sum-is-divisible-by-k/description/

class Solution {
public:
    int numberOfPaths(vector<vector<int>>& grid, int k) {
        int m = grid.size();
        int n = grid[0].size();

        auto initDp = [&]() {
            std::vector<std::vector<std::vector<int>>>
                dp(m, std::vector<std::vector<int>>(n, std::vector<int>(k)));
            int initSum = grid[0][0] % k;
            dp[0][0][initSum] = 1;
            int rowSum = initSum;
            for (int col = 1; col < n; ++col) {
                rowSum = (rowSum + grid[0][col]) % k;
                dp[0][col][rowSum] = 1;
            }
            int colSum = initSum;
            for (int row = 1; row < m; ++row) {
                colSum = (colSum + grid[row][0]) % k;
                dp[row][0][colSum] = 1;
            }
            return dp;
        };
        auto dp = initDp();

        auto doDp = [&]() {
            for (int row = 1; row < m; ++row) {
                for (int col = 1; col < n; ++col) {
                    for (int prevRem = 0; prevRem < k; ++prevRem) {
                        int rem = (grid[row][col] + prevRem) % k;
                        dp[row][col][rem] = (dp[row-1][col][prevRem] + dp[row][col-1][prevRem]) % MODULUS;
                    }
                }
            }
        };
        doDp();

        return dp[m-1][n-1][0];
    }

private:
    static constexpr int MODULUS = 1000000007;
};
