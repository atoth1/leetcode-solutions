// https://leetcode.com/problems/last-day-where-you-can-still-cross/submissions/

#include <memory>
#include <utility>
#include <vector>

namespace {
    struct SetNode {
        SetNode* parent{};
        int rank{};
        bool touchesLeft{};
        bool touchesRight{};
            
        SetNode* getRoot() {
            SetNode* root{ this };
            while (root->parent) {
                root = root->parent;
            }
            
            SetNode* node{ this };
            while (node->parent) {
                node = std::exchange(node->parent, root);
            }
            return root;
        }
        
        void join(SetNode* other) {
            SetNode* x = getRoot();
            SetNode* y = other->getRoot();
            if (x != y) {
                if (x->rank < y->rank) std::swap(x, y);
                if (y->touchesLeft) x->touchesLeft = true;
                if (y->touchesRight) x->touchesRight = true;
                if (x->rank == y->rank) ++x->rank;
                y->parent = x;
            }
        }
    };
}

class Solution {
public:
    int latestDayToCross(int m, int n, const std::vector<std::vector<int>>& cells) {
        using nodes_t = std::vector<std::vector<std::unique_ptr<SetNode>>>;
        nodes_t nodes{};
        for (int row = 0; row < m; ++row) {
            std::vector<std::unique_ptr<SetNode>> init{};
            for (int col = 0; col < n; ++col) init.push_back(nullptr);
            nodes.push_back(std::move(init));
        }
        
        auto attemptJoin = [&](SetNode* x, int r, int c) {
            if (r >= 0 && r < m) {
                    if (c >= 0 && c < n) {
                        if (nodes[r][c]) x->join(nodes[r][c].get());
                }
            }
        };
        
        int day = 0;
        for (const auto& cell : cells) {
            const int r = cell[0] - 1;
            const int c = cell[1] - 1;
            
            auto node = std::make_unique<SetNode>();
            node->touchesLeft = c == 0;
            node->touchesRight = c == n - 1;
            
            attemptJoin(node.get(), r - 1, c - 1);
            attemptJoin(node.get(), r - 1, c);
            attemptJoin(node.get(), r - 1, c + 1);
            attemptJoin(node.get(), r, c - 1);
            attemptJoin(node.get(), r, c + 1);
            attemptJoin(node.get(), r + 1, c - 1);
            attemptJoin(node.get(), r + 1, c);
            attemptJoin(node.get(), r + 1, c + 1);
                
            SetNode* root = node->getRoot();
            if (root->touchesLeft && root->touchesRight) return day;
            nodes[r][c] = std::move(node);
            ++day;
        }
        return -1;
    }
};
