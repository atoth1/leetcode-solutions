// https://leetcode.com/problems/cut-off-trees-for-golf-event/

#include <algorithm>
#include <iterator>
#include <map>
#include <utility>
#include <vector>

class Solution {
public:
    static int cutOffTree(const std::vector<std::vector<int>>& forest) {
        const int m = forest.size();
        const int n = forest[0].size();
        
        auto makeLookup = [&] {
            std::map<int, Position> lookup{};
            for (int row = 0; row < m; ++row) {
                for (int col = 0; col < n; ++col) {
                    if (forest[row][col] > 1) {
                        lookup[forest[row][col]] = Position{ row, col };
                    }
                }
            }
            return lookup;
        };
        
        auto minDist = [&](const Position start, const Position end, std::vector<std::vector<bool>>& visited) {
            if (start == end) return 0;
            
            std::vector<Position> curr{ start };
            std::vector<Position> next{};
            visited[start.row][start.col] = true;
            int dist = 0;
            
            auto isValidPosition = [&](const Position pos) {
                return pos.row >= 0 && pos.row < m && pos.col >= 0 && pos.col < n;
            };
            
            auto tryVisit = [&](const Position pos) {
                if (pos == end) return true;
                
                const auto [row, col] = pos;
                if (isValidPosition(pos) && !visited[row][col] && forest[row][col] > 0) {
                    next.push_back(pos);
                    visited[row][col] = true;
                }
                return false;
            };
            
            while (!curr.empty()) {
                ++dist;
                for (const auto [row, col] : curr) {
                    if (tryVisit({ row - 1, col })) return dist;
                    if (tryVisit({ row + 1, col })) return dist;
                    if (tryVisit({ row, col - 1 })) return dist;
                    if (tryVisit({ row, col + 1 })) return dist;
                }
                std::swap(curr, next);
                next.clear();
            }
            return -1;
        };
        
        std::vector visited(m, std::vector(n, false));
        auto resetVisited = [&] {
            for (auto& vec : visited) {
                std::fill(vec.begin(), vec.end(), false);
            }
        };
        
        const auto lookup = makeLookup();
        int sum = minDist(Position{ 0, 0 }, lookup.begin()->second, visited);
        if (sum == -1) {
            return -1;
        }
        resetVisited();
        
        for (auto it = lookup.begin(); it != std::prev(lookup.end()); ++it) {
            const int dist = minDist(it->second, std::next(it)->second, visited);
            if (dist == -1) {
                return -1;
            }
            sum += dist;
            resetVisited();
        }
        return sum;
    }
    
private:
    struct Position {
        int row;
        int col;
        
        bool operator==(const Position&) const noexcept = default;
    };
};