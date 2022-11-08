// https://leetcode.com/problems/vertical-order-traversal-of-a-binary-tree/

#include <algorithm>
#include <deque>
#include <memory>
#include <utility>

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        if (!root) return {};
        std::vector<std::vector<TreeNode*>> curr{ std::vector<TreeNode*>{root} };
        bool continueLooping = true;
        std::deque<std::vector<int>> values(1);
        while (continueLooping) {
            continueLooping = false;
            std::vector<std::vector<TreeNode*>> next(curr.size()+2);
            
            for (int id = 0; id < curr.size(); id += 2) {
                std::vector<int> newValues{};
                for (const auto node : curr[id]) {
                    newValues.push_back(node->val);
                    if (node->left) {
                        next[id].push_back(node->left);
                        continueLooping = true;
                    }
                    if (node->right) {
                        next[id+2].push_back(node->right);
                        continueLooping = true;
                    }
                }
                std::sort(newValues.begin(), newValues.end());
                std::copy(newValues.begin(), newValues.end(), std::back_inserter(values[id]));
            }
            if (continueLooping) {
                values.push_front(std::vector<int>{});
                values.push_back(std::vector<int>{});
            }
            std::swap(curr, next);
        }
        
        std::vector<std::vector<int>> ret;
        auto it = values.begin();
        while (it->empty()) ++it;
        while (it != values.end() && !it->empty()) {
            ret.push_back(std::move(*it));
            ++it;
        }
        return ret;
    }
};
