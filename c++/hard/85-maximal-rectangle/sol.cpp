// https://leetcode.com/problems/maximal-rectangle/

#include <vector>

class Solution {
public:
    static int maximalRectangle(const std::vector<std::vector<char>>& matrix) {
        const int m = matrix.size();
        const int n = matrix[0].size();
        
        std::vector<int> height(n);
        std::vector<int> lessColOnLeft(n);
        std::vector<int> lessColOnRight(n);
        int max = 0;

        auto forwardSweep = [&](const int row) {
            for (int col = 0; col < n; ++col) {
                if (matrix[row][col] == '0') {
                    height[col] = 0;
                } else {
                    ++height[col];
                }
                
                int lessCol = col - 1;
                while (lessCol >= 0 && height[col] <= height[lessCol]) {
                    lessCol = lessColOnLeft[lessCol];
                }
                lessColOnLeft[col] = lessCol;
            }
        };
        
        auto reverseSweep = [&]() {
            auto maxOf = [](const int x, const int y) { return x > y ? x : y; };
            
            for (int col = n - 1; col >= 0; --col) {
                int lessCol = col + 1;
                while (lessCol < n && height[col] <= height[lessCol]) {
                    lessCol = lessColOnRight[lessCol];
                }
                lessColOnRight[col] = lessCol;
                
                max = maxOf(max, height[col] * (lessColOnRight[col] - lessColOnLeft[col] - 1));
            }
        };
        
        for (int row = 0; row < m; ++row) {
            forwardSweep(row);
            reverseSweep();
        }
        return max;
    }
};