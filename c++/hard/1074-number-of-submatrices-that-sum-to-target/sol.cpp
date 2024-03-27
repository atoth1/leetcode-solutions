// https://leetcode.com/problems/number-of-submatrices-that-sum-to-target/

#include <unordered_map>
#include <vector>

class Solution {
public:
    static int numSubmatrixSumTarget(const std::vector<std::vector<int>>& matrix, const int k) {
        const int m = matrix.size();
        const int n = matrix[0].size();
        
        auto makePrefixSums = [&]() {
            std::vector prefix(m + 1, std::vector<int>(n + 1));
            for (int row = 0; row < m; ++row) {
                int rowSum = 0;
                for (int col = 0; col < n; ++col) {
                    rowSum += matrix[row][col];
                    prefix[row + 1][col + 1] = rowSum + prefix[row][col + 1];
                }
            }
            return prefix;
        };
        
        auto submatrixSum = [prefix = makePrefixSums()](const int fromRow, const int toRow, const int fromCol, const int toCol) {
            return prefix[toRow + 1][toCol + 1] - prefix[toRow + 1][fromCol]
                - prefix[fromRow][toCol + 1] + prefix[fromRow][fromCol];
        };
        
        int count = 0;
        for (int startRow = 0; startRow < m; ++startRow) {
            for (int endRow = startRow; endRow < m; ++endRow) {
                std::unordered_map<int, int> seenPrefixCounts{ { 0, 1 } };
                for (int endCol = 0; endCol < n; ++endCol) {
                    const int sum = submatrixSum(startRow, endRow, 0, endCol);
                    const int target = sum - k;
                    if (const auto it = seenPrefixCounts.find(target); it != seenPrefixCounts.end()) {
                        count += it->second;
                    }
                    ++seenPrefixCounts[sum];
                }
            }
        }
        return count;
    }
};
