// https://leetcode.com/problems/find-critical-and-pseudo-critical-edges-in-minimum-spanning-tree/

#include <algorithm>
#include <memory>
#include <numeric>
#include <optional>
#include <utility>
#include <vector>

namespace {
    class Node;
    
    using NodePtr = std::shared_ptr<Node>;
    
    struct Node {
        Node() = default;
        
        NodePtr parent{};
        int size{ 1 };
    };
    
    NodePtr getRoot(NodePtr node) {
        auto root = node;
        while (root->parent) {
            root = root->parent;
        }

        while (node->parent) {
            node = std::exchange(node->parent, root);
        }
        return root;
    }

    bool isRoot(NodePtr node) {
        return node == getRoot(node);
    }
    
    bool inSameSet(NodePtr first, NodePtr second) {
        return getRoot(first) == getRoot(second);
    }

    void join(NodePtr first, NodePtr second) {
        if (!inSameSet(first, second)) {
            NodePtr x = getRoot(first);
            NodePtr y = getRoot(second);
            if (x->size < y->size) std::swap(x, y);
            x->size += y->size;
            y->parent = x;
        }
    }
    
    std::vector<int> makeSortedIds(const std::vector<std::vector<int>>& edges) {
        std::vector<int> sortedIds(edges.size());
        std::iota(sortedIds.begin(), sortedIds.end(), 0);
        std::sort(sortedIds.begin(), sortedIds.end(), [&](const int l, const int r) {
            return edges[l][2] < edges[r][2];
        });
        return sortedIds;
    }
    
    std::optional<int> getMinSpanningTreeWeight(
        const int n,
        const std::vector<std::vector<int>>& edges,
        const std::vector<int> sortedIds,
        const std::optional<int> skippedEdgeId = std::nullopt,
        const std::optional<int> requiredEdgeId = std::nullopt
    ) {
        std::vector<NodePtr> nodes(n);
        for (auto& node : nodes) node = std::make_shared<Node>();
        
        int weight = 0;
        if (requiredEdgeId) {
            const int id = *requiredEdgeId;
            weight += edges[id][2];
            join(nodes[edges[id][0]], nodes[edges[id][1]]);
        }
        
        for (const int id : sortedIds) {
            auto first = nodes[edges[id][0]];
            auto second = nodes[edges[id][1]];
            if ((!skippedEdgeId || id != *skippedEdgeId) && !inSameSet(first, second)) {
                weight += edges[id][2];
                join(first, second);
            }
        }
        
        auto isConnected = [&]() {
            return getRoot(nodes[0])->size == n;
        };
        if (isConnected()) {
            return { weight };
        } else {
            return std::nullopt;
        }
        
    }
}

class Solution {
public:
    std::vector<std::vector<int>>
    findCriticalAndPseudoCriticalEdges(
        const int n,
        const std::vector<std::vector<int>>& edges
    ) {
        const auto sortedIds = makeSortedIds(edges);
        const int minWeight = *getMinSpanningTreeWeight(n, edges, sortedIds);
        std::vector<int> requiredIds{};
        std::vector<int> includedIds{};
        for (int id = 0; id < edges.size(); ++id) {
            auto weight1 = getMinSpanningTreeWeight(n, edges, sortedIds, { id });
            if (!weight1 || *weight1 != minWeight) {
                requiredIds.push_back(id);
            } else {
                auto weight2 = getMinSpanningTreeWeight(n, edges, sortedIds, std::nullopt, { id });
                if (*weight2 == minWeight) {
                    includedIds.push_back(id);
                }
            }
        }
        return { requiredIds, includedIds };
    }
};
