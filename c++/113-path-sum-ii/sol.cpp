// https://leetcode.com/problems/path-sum-ii/

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

namespace
{
    void pathSumImpl(TreeNode* root,
                    std::vector<std::vector<int>>& results,
                    std::vector<int>& currentPath,
                    int currentSum,
                    int targetSum)
    {
        if (!root->left && !root->right)
        {
            if (root->val + currentSum == targetSum)
            {
                currentPath.push_back(root->val);
                results.push_back(currentPath);
                currentPath.pop_back();
            }
        }
        else
        {
            currentPath.push_back(root->val);
            currentSum += root->val;
            if (root->left)
            {
                pathSumImpl(root->left, results, currentPath, currentSum, targetSum);
            }
            if (root->right)
            {
                pathSumImpl(root->right, results, currentPath, currentSum, targetSum);
            }
            currentPath.pop_back();
        }
    }
}

class Solution {
public:
    vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
        if (!root) return {};
        std::vector<std::vector<int>> results;
        std::vector<int> currentPath;
        pathSumImpl(root, results, currentPath, 0, targetSum);
        return results;
    }
};
