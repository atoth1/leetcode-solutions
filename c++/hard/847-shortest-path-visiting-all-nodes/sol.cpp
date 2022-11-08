// https://leetcode.com/problems/shortest-path-visiting-all-nodes/

#include <memory>
#include <unordered_set>
#include <utility>

class Solution {
public:
    int shortestPathLength(vector<vector<int>>& graph) {
        const int n = graph.size();
        if (n == 1) return 0;
        std::vector<NodePtr> nodes(n, nullptr);
        for (int id = 0; id < n; ++id)
        {
            if (!nodes[id])
            {
                nodes[id] = std::make_shared<Node>();
                nodes[id]->id = id;
            }
            for (const auto neighbor : graph[id])
            {
                if (!nodes[neighbor])
                {
                    nodes[neighbor] = std::make_shared<Node>();
                    nodes[neighbor]->id = neighbor;
                }
                nodes[id]->neighbors.push_back(nodes[neighbor]);
            }
        }
        
        std::vector<std::pair<NodePtr, std::uint16_t>> candidates{};
        candidates.reserve(n);
        std::vector<std::pair<NodePtr, std::uint16_t>> next{};
        std::vector<std::unordered_set<std::uint16_t>> seen;
        seen.reserve(n);
        for (const auto node : nodes)
        {
            candidates.push_back(std::make_pair(nodes[node->id], 1 << node->id));
            seen.push_back({});
            seen.back().insert(1 << node->id);
        }
        std::uint16_t target = (1 << n) - 1;
        int moves = 0;
        while (!candidates.empty())
        {
            ++moves;
            for (const auto candidate : candidates)
            {
                for (const auto neighbor : candidate.first->neighbors)
                {
                    std::uint16_t newMask = candidate.second | (1 << neighbor->id);
                    if (newMask == target) return moves;
                    if (seen[neighbor->id].count(newMask) == 0)
                    {
                        seen[neighbor->id].insert(newMask);
                        next.push_back(std::make_pair(nodes[neighbor->id], newMask));
                    }
                }
            }
            std::swap(candidates, next);
            next.clear();
        }
        // Should never get here
        return -1;
    }
    
private:
    struct Node;
    using NodePtr = std::shared_ptr<Node>;
    struct Node
    {
        int id{-1};
        std::vector<NodePtr> neighbors{};
    };
};
