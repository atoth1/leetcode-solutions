// https://leetcode.com/problems/find-duplicate-subtrees/

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

#include <map>
#include <unordered_map>
#include <utility>

class Solution {
public:
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        std::unordered_map<const TreeNode*, int, NodeHash, NodeEqual> counts{};
        traverse(root, counts);
        return multipleCounts(counts);
    }
    
private:
    struct NodeHash {
        mutable std::unordered_map<const TreeNode*, std::size_t> cache{};
        
        std::size_t operator()(const TreeNode* node) const {
            if (!node) return 23;
            if (auto it = cache.find(node); it != cache.end()) return it->second;
                
            static constexpr int MOD = 1000000007;
            std::size_t ret = node->val;
            ret = 13 * (ret + (*this)(node->left)) % MOD;
            ret = 19 * (ret + (*this)(node->right)) % MOD;
            cache[node] = ret;
            return ret;
        }
    };
    
    struct NodeEqual {
        mutable std::map<std::pair<const TreeNode*, const TreeNode*>, bool> cache{};
        
        bool operator()(const TreeNode* l, const TreeNode* r) const {
            if (l == nullptr && r == nullptr) return true;
            else if (l == nullptr && r != nullptr) return false;
            else if (l != nullptr & r == nullptr) return false;
            
            auto it1 = cache.find(std::make_pair(l, r));
            if (it1 != cache.end()) return it1->second;
            auto it2 = cache.find(std::make_pair(r, l));
            if (it2 != cache.end()) return it2->second;
            
            bool ret = l->val == r->val && (*this)(l->left, r->left) && (*this)(l->right, r->right);
            cache[std::make_pair(l, r)] = ret;
            return ret;
        }
    };
    
    void traverse(
        const TreeNode* node,
        std::unordered_map<const TreeNode*, int, NodeHash, NodeEqual>& counts
    ) {
        if (node) {
            ++counts[node];
            traverse(node->left, counts);
            traverse(node->right, counts);
        }
    }
    
    std::vector<TreeNode*> multipleCounts(
        const std::unordered_map<const TreeNode*, int, NodeHash, NodeEqual>& counts
    ) {
        std::vector<TreeNode*> ret{};
        for (const auto& p : counts) {
            if (p.second > 1) ret.push_back(const_cast<TreeNode*>(p.first));
        }
        return ret;
    }
};