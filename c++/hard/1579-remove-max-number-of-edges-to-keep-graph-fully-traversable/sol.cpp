// https://leetcode.com/problems/remove-max-number-of-edges-to-keep-graph-fully-traversable/

#include <memory>
#include <utility>

class Solution {
public:
    int maxNumEdgesToRemove(int n, vector<vector<int>>& edges) {
        if (edges.size() < n - 1) return -1;
        
        auto graph1 = makeGraph(n);
        auto graph2 = makeGraph(n);
        
        int edgeCount = 0;
        for (const auto& edge : edges) {
            const int id1 = edge[1] - 1;
            const int id2 = edge[2] - 1;
            if (edge[0] == 3) {
                const bool joined1 = join(graph1[id1], graph1[id2]);
                const bool joined2 = join(graph2[id1], graph2[id2]);
                if (joined1 || joined2) ++edgeCount;
            }
        }
        
        for (const auto& edge : edges) {
            const int id1 = edge[1] - 1;
            const int id2 = edge[2] - 1;
            if ((edge[0] == 1 && join(graph1[id1], graph1[id2])) || 
                (edge[0] == 2 && join(graph2[id1], graph2[id2]))) {
                ++edgeCount;
            }
        }
        
        if (isConnected(graph1) && isConnected(graph2)) {
            return edges.size() - edgeCount;
        } else {
            return -1;
        }
    }
    
private:
    struct SetNode {
        std::shared_ptr<SetNode> parent = nullptr;
        int rank = 0;
    };
    
    static std::vector<std::shared_ptr<SetNode>> makeGraph(const int n) {
        std::vector<std::shared_ptr<SetNode>> graph(n);
        for (auto& node : graph) {
            node = std::make_shared<SetNode>();
        }
        return graph;
    }
    
    static std::shared_ptr<SetNode> getRoot(std::shared_ptr<SetNode> node) {
        auto root = node;
        while (root->parent) {
            root = root->parent;
        }
        
        while (node->parent) {
            node = std::exchange(node->parent, root);
        }
        return root;
    }

    static bool isRoot(const std::shared_ptr<SetNode> node) {
        return node == getRoot(node);
    }

    static bool join(std::shared_ptr<SetNode> x, std::shared_ptr<SetNode> y) {
        x = getRoot(x);
        y = getRoot(y);
        if (x == y) {
            return false;
        } else {
            if (x->rank < y->rank) std::swap(x, y);
            if (x->rank == y->rank) ++x->rank;
            y->parent = x;
            return true;
        }
    }
    
    static bool isConnected(const std::vector<std::shared_ptr<SetNode>>& graph) {
        int componentCount = 0;
        for (const auto node : graph) {
            if (isRoot(node)) ++componentCount;
        }
        return componentCount == 1;
    }
};
