// https://leetcode.com/problems/transpose-matrix/

class Solution {
public:
    vector<vector<int>> transpose(vector<vector<int>>& matrix) {
        // Transpose blockSize x blockSize blocks for better cache efficiency
        constexpr int blockSize = 16;
        int rows = matrix.size();
        int rowBlocks = rows/blockSize;
        if (rows - rowBlocks*blockSize != 0) ++rowBlocks;
        int cols = matrix[0].size();
        int colBlocks = cols/blockSize;
        if (cols - colBlocks*blockSize) ++colBlocks;
        
        std::vector<std::vector<int>> ret(cols, std::vector<int>(rows));
        for (int rowBlock = 0; rowBlock < rowBlocks; ++rowBlock) {
            for (int colBlock = 0; colBlock < colBlocks; ++colBlock) {
                int rowBegin = rowBlock * blockSize;
                int rowEnd = (rowBlock+1) * blockSize;
                if (rowEnd > rows) rowEnd = rows;
                int colBegin = colBlock * blockSize;
                int colEnd = (colBlock+1) * blockSize;
                if (colEnd > cols) colEnd = cols;
                for (int row = rowBegin; row < rowEnd; ++row) {
                    for (int col = colBegin; col < colEnd; ++col) {
                        ret[col][row] = matrix[row][col];
                    }
                }
            }
        }
        return ret;
    }
};

