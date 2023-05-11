// https://leetcode.com/problems/binary-tree-maximum-path-sum/

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

namespace {
    // Arbitrary value smaller than minumum node value (problem specifies -1000 <= val <= 1000)
    static constexpr int UNSET = -1000000;

    // Returns maximum possible path from node to one of its descendants, if positive.
    // Otherwise returns 0.
    int impl(const TreeNode* node, int& maxPath) {
        int maxToLeft = 0;
        if (node->left) maxToLeft = impl(node->left, maxPath);
        int maxToRight = 0;
        if (node->right) maxToRight = impl(node->right, maxPath);
        int maxAsRoot = node->val + maxToLeft + maxToRight;
        if (maxAsRoot > maxPath) maxPath = maxAsRoot;
        int maxToDescendant = maxToLeft > maxToRight ? node->val + maxToLeft : node->val + maxToRight;
        if (maxToDescendant > 0) {
            return maxToDescendant;
        } else {
            return 0;
        }
    }
}

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        int maxPath = UNSET;
        impl(root, maxPath);
        return maxPath;
    }
};