// https://leetcode.com/problems/n-queens/

#include <cstdlib>

namespace
{
    struct Queen
    {
        int row;
        int col;
    };
    
    
    int abs(int i)
    {
        return i < 0 ? -i : i;
    }
    
    void solveNQueensImpl(std::vector<std::vector<std::string>>& sol,
                          std::vector<Queen>& curr,
                          int dim)
    {
        int row = curr.size();
        for (int col = 0; col < dim; ++col)
        {
            Queen candidate{row,col};
            bool valid = true;
            for (const auto& prev : curr)
            {
                if (candidate.col == prev.col ||
                    abs(candidate.row - prev.row) == abs(candidate.col - prev.col))
                {
                    valid = false;
                    break;
                }
            }
            if (valid)
            {
                if (row == dim -1)
                {
                    std::vector<std::string> tmp;
                    tmp.reserve(dim);
                    for (const auto& q : curr)
                    {
                        tmp.emplace_back(dim, '.');
                        tmp.back()[q.col] = 'Q';
                    }
                    tmp.emplace_back(dim, '.');
                    tmp.back()[candidate.col] = 'Q';
                    sol.push_back(std::move(tmp));
                    break;
                }
                else
                {
                    curr.push_back(candidate);
                    solveNQueensImpl(sol, curr, dim);
                    curr.pop_back();
                }
            }
        }
    }
}

class Solution {
public:
    vector<vector<string>> solveNQueens(int n) {
        std::vector<std::vector<std::string>> ret;
        std::vector<Queen> curr;
        solveNQueensImpl(ret, curr, n);
        return ret;
    }
};
