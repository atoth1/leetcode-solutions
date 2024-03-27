// https://leetcode.com/problems/n-queens-ii/

#include <vector>

namespace {
    struct Position {
        int row;
        int col;
    };
    
    void impl(const int n, const int row, std::vector<Position>& positions, int& count) {
        if (row == n) {
            ++count;
            return;
        }
        
        auto canPlaceAt = [&](const int col) {
            for (const auto [prevRow, prevCol] : positions) {
                const int rowDelta = row - prevRow;
                const int colDelta = col - prevCol;
                if (col == prevCol || rowDelta == colDelta || rowDelta == -colDelta) {
                    return false;
                }
            }
            return true;
        };
        
        for (int col = 0; col < n; ++col) {
            if (canPlaceAt(col)) {
                positions.push_back({ row, col });
                impl(n, row + 1, positions, count);
                positions.pop_back();
            }
        }
    }
}

class Solution {
public:
    static int totalNQueens(const int n) {
        std::vector<Position> positions{};
        int count = 0;
        impl(n, 0, positions, count);
        return count;
    }
};
