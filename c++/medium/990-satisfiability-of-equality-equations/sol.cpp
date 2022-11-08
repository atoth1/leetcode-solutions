// https://leetcode.com/problems/satisfiability-of-equality-equations/

#include <array>
#include <memory>
#include <utility>

class Solution {
public:
    bool equationsPossible(vector<string>& equations) {
        std::array<std::shared_ptr<SetNode>, 26> nodes{};
        for (auto& node : nodes) node = std::make_shared<SetNode>();
        
        // First pass, create sets of variables that must be equal
        for (const auto& equation : equations) {
            if (equation[1] == '=') {
                merge(nodes[equation[0] - 'a'], nodes[equation[3] - 'a']);
            }
        }
        
        // Second pass, check that no variables in same set are unequal
        for (const auto& equation : equations) {
            if (equation[1] == '!') {
                auto l = nodes[equation[0] - 'a'];
                auto r = nodes[equation[3] - 'a'];
                if (getRoot(l) == getRoot(r)) return false;
            }
        }
        return true;
    }
    
private:
    struct SetNode {
        std::shared_ptr<SetNode> parent = nullptr;
        int rank = 1;
    };
    
    std::shared_ptr<SetNode> getRoot(std::shared_ptr<SetNode> node) {
        auto root = node;
        while (root->parent) root = root->parent;
        if (root != node) {
            while (node->parent != root) {
                auto tmp = node->parent;
                node->parent = root;
                node = tmp;
            }
        }
        return root;
    }
    
    void merge(std::shared_ptr<SetNode> x, std::shared_ptr<SetNode> y) {
        x = getRoot(x);
        y = getRoot(y);
        if (x != y) {
            if (x->rank < y->rank) std::swap(x, y);
            if (x->rank == y->rank) ++(x->rank);
            y->parent = x;
        }
    }
};
