// https://leetcode.com/problems/serialize-and-deserialize-binary-tree/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

#include <sstream>
#include <utility>

class Codec {
public:

    // Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        std::vector<TreeNode*> curr{ root };
        std::vector<TreeNode*> next{};
        std::ostringstream ret{};
        while (!curr.empty()) {
            for (const auto node : curr) {
                if (node) {
                    ret << node->val << ',';
                    next.push_back(node->left);
                    next.push_back(node->right);
                } else {
                    ret << "n,";
                }
            }
            std::swap(curr, next);
            next.clear();
        }
        return ret.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
        auto parseNext = [&](std::string::size_type& pos) {
            TreeNode* ret = nullptr;
            if (data[pos] == 'n') {
                pos += 2; // Advance past "n,"
            } else {
                const auto commaPos = data.find(',', pos);
                ret = new TreeNode(std::stoi(data.substr(pos, commaPos - pos)));
                pos = commaPos + 1;
            }
            return ret;
        };
        
        std::string::size_type pos = 0;
        TreeNode* root = parseNext(pos);
        std::vector<TreeNode*> curr{ root };
        std::vector<TreeNode*> next{};
        while (pos < data.size()) {
            for (auto node : curr) {
                if (node) {
                    node->left = parseNext(pos);
                    node->right = parseNext(pos);
                    next.push_back(node->left);
                    next.push_back(node->right);
                }
            }
            std::swap(curr, next);
            next.clear();
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));
