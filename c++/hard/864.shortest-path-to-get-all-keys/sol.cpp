// https://leetcode.com/problems/shortest-path-to-get-all-keys/

#include <cstdint>
#include <memory>
#include <string>
#include <tuple>
#include <unordered_set>
#include <utility>
#include <vector>

namespace {
    
    static constexpr int maxGridLen = 30;
    
    static constexpr int maxKeyCount = 6;
    
    struct Position {
        int row{ -1 };
        int col{ -1 };
        
        constexpr bool operator==(const Position other) const noexcept {
            return row == other.row && col == other.col;
        }
    };
    
    struct Node;
    
    using NodePtr = std::shared_ptr<Node>;
    
    struct Node {
        std::vector<NodePtr> neighbors{};
        Position pos{ -1, -1 };
    };
    
    using graph_t = std::vector<std::vector<NodePtr>>;
    
    std::tuple<graph_t, NodePtr, int> makeGraph(const std::vector<std::string>& grid) {
        const int m = grid.size();
        const int n = grid[0].size();
        
        graph_t graph(m, std::vector<NodePtr>(n));
        auto isTravelable = [](const char c) { return c != '#'; };
        
        NodePtr startNodePtr{};
        auto isStartPos = [](const char c) { return c == '@'; };
        
        int keyCount = 0;
        auto isKey = [](const char c) { return c >= 'a' && c < 'a' + maxKeyCount; };
        
        for (int row = 0; row < m; ++row) {
            for (int col = 0; col < n; ++col) {
                if (isTravelable(grid[row][col])) {
                    graph[row][col] = std::make_shared<Node>();
                    graph[row][col]->pos = Position{ row, col };
                    
                    if (isStartPos(grid[row][col])) startNodePtr = graph[row][col];
                    if (isKey(grid[row][col])) ++keyCount;
                    
                    if (row > 0 && isTravelable(grid[row - 1][col])) {
                        graph[row][col]->neighbors.push_back(graph[row - 1][col]);
                        graph[row - 1][col]->neighbors.push_back(graph[row][col]);
                    }
                    
                    if (col > 0 && isTravelable(grid[row][col - 1])) {
                        graph[row][col]->neighbors.push_back(graph[row][col - 1]);
                        graph[row][col - 1]->neighbors.push_back(graph[row][col]);
                    }
                }
            }
        }
        return { graph, startNodePtr, keyCount };
    }
    
    struct State {
        NodePtr node{};
        std::uint8_t mask{};
    };
    
    struct StateEqual {
        bool operator()(const State l, const State r) const noexcept {
            return l.node->pos == r.node->pos && l.mask == r.mask;
        }
    };
    
    struct StateHash {
        std::size_t operator()(const State x) const noexcept {
            constexpr int maxMaskCount = 1 << maxKeyCount;
            std::size_t hash = x.node->pos.row;
            hash = maxGridLen * hash + x.node->pos.col;
            hash = maxMaskCount * hash + x.mask;
            return hash;
        }
    };
    
    using set_t = std::unordered_set<State, StateHash, StateEqual>;
    
    int doBfs(const std::vector<std::string>& grid) {
        const auto [graph, startNodePtr, keyCount] = makeGraph(grid);
        State startState{ startNodePtr };
        std::vector<State> curr{ startState };
        std::vector<State> next{};
        set_t visited{ startState };
        std::uint8_t targetMask = (1 << keyCount)  - 1;
        
        auto isLock = [](const char c) { return c >= 'A' && c < 'A' + maxKeyCount; };
        auto isKey = [](const char c) { return c >= 'a' && c < 'a' + maxKeyCount; };
        auto attemptAddKey = [&](const char c, std::uint8_t& mask) {
            if (isKey(c)) {
              int offset = c - 'a';
              mask |= 1 << offset;
            }
        };
        auto haveKey = [](const char c, const std::uint8_t mask) {
            int offset = c - 'A';
            return mask & (1 << offset);
        };
        
        int moves = 0;
        while (!curr.empty()) {
            ++moves;
            for (const auto currState : curr) {
                for (const auto neighborNode : currState.node->neighbors) {
                    const char c = grid[neighborNode->pos.row][neighborNode->pos.col];
                    if (!isLock(c) || haveKey(c, currState.mask)) {
                        State candidateState{ neighborNode, currState.mask };
                        attemptAddKey(c, candidateState.mask);

                        if (candidateState.mask == targetMask) return moves;
                        
                        if (visited.count(candidateState) == 0) {
                            next.push_back(candidateState);
                            visited.insert(candidateState);
                        }
                        
                    }
                }
            }
            std::swap(curr, next);
            next.clear();
        }
        return -1;
    }
}

class Solution {
public:
    int shortestPathAllKeys(const std::vector<std::string>& grid) {
        return doBfs(grid);
    }
};
