// https://leetcode.com/problems/number-of-operations-to-make-network-connected/

#include <memory>
#include <unordered_set>
#include <utility>

class Solution {
public:
    int makeConnected(int n, vector<vector<int>>& connections) {
        if (connections.size() < n-1) return -1;
        
        std::vector<std::shared_ptr<SetNode>> nodes(n, nullptr);
        for (const auto& connection : connections) {
            if (!nodes[connection[0]]) {
                nodes[connection[0]] = std::make_shared<SetNode>();
                nodes[connection[0]]->id = connection[0];
            }
            if (!nodes[connection[1]]) {
                nodes[connection[1]] = std::make_shared<SetNode>();
                nodes[connection[1]]->id = connection[1];
            }
            join(nodes[connection[0]], nodes[connection[1]]);
        }
        
        std::unordered_set<int> rootIds{};
        for (int id = 0; id < nodes.size(); ++id) {
            if (!nodes[id]) {
                nodes[id] = std::make_shared<SetNode>();
                nodes[id]->id = id;
            }
            rootIds.insert(rootNode(nodes[id])->id);
        }
        return rootIds.size() - 1;
    }
    
private:
    struct SetNode {
        std::shared_ptr<SetNode> parent = nullptr;
        int rank = 0;
        int id = -1;
    };
    
    std::shared_ptr<SetNode> rootNode(const std::shared_ptr<SetNode> x) {
        auto root = x;
        while (root->parent) root = root->parent;
        
        if (root != x) {
        auto tmp1 = x;
            while (tmp1->parent != root) {
                auto tmp2 = tmp1->parent;
                tmp1->parent = root;
                tmp1 = tmp2;
            }
        }
        return root;
    }
    
    void join(const std::shared_ptr<SetNode> a, const std::shared_ptr<SetNode> b) {
        auto x = rootNode(a);
        auto y = rootNode(b);
        if (x != y) {
            if (y->rank > x->rank) std::swap(x, y);
            if (x->rank == y->rank) ++x->rank;
            y->parent = x;
        }
    }
};
