//https://leetcode.com/problems/shortest-path-in-a-grid-with-obstacles-elimination/

#include <unordered_map>
#include <utility>

class Solution {
public:
    int shortestPath(vector<vector<int>>& grid, int k) {
        const int m = grid.size();
        const int n = grid[0].size();
        
        // Can blast all obstacles to make any direct path of rights and downs
        if (k >= m + n - 3) return m + n - 2;
        
        State initState{ 0, 0, 0 };
        std::vector<State> curr{ initState };
        std::vector<State> next{};
        std::unordered_map<std::pair<int, int>, int, HashPos> minErasures{ std::make_pair(std::make_pair(0, 0), 0) };
        
        auto newState = [&](const int row, const int col, const int prevErasures) {
            if (row >= 0 && row < m && col >= 0 && col < n) {
                int erasures = grid[row][col] == 0 ? prevErasures : prevErasures+1;
                if (erasures <= k) {
                    auto pos = std::make_pair(row, col);
                    auto it = minErasures.find(pos);
                    // Consider new candidate if new cell or took fewer erasures to reach
                    // previously visited cell
                    if (it == minErasures.end() || erasures < it->second) {
                        next.push_back(State{ row, col, erasures });
                        minErasures[pos] = erasures;
                    }
                }
            }
        };
        
        int moves = 0;
        while (!curr.empty()) {
            ++moves;
            
            for (const auto state : curr) {
                if ((state.row == m-1 && state.col == n-2) || (state.row == m-2 && state.col == n-1)) {
                    return moves;
                }
                
                newState(state.row-1, state.col, state.erasures);
                newState(state.row+1, state.col, state.erasures);
                newState(state.row, state.col-1, state.erasures);
                newState(state.row, state.col+1, state.erasures);
            }
            std::swap(curr, next);
            next.clear();
        }
        return -1;
    }
    
private:
    struct State {
        int row{};
        int col{};
        int erasures{};
    };
    
    struct HashPos {
        static constexpr int MAX = 40;
        
        std::size_t operator()(const std::pair<int, int>& x) const {
            return MAX * x.first + x.second;
        }
    };
};
