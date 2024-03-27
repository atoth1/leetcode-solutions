// https://leetcode.com/problems/recover-a-tree-from-preorder-traversal/

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
  static TreeNode* recoverFromPreorder(const std::string& traversal) {
    auto toInt = [](auto begin, const auto end) {
      int ret = 0;
      while (begin != end) {
        ret = 10 * ret + *begin++ - '0';
      }
      return ret;
    };

    auto tokenize = [&](const std::string& str) {
      auto it = std::find(str.begin(), str.end(), '-');

      std::vector depths{0};
      std::vector vals{toInt(str.begin(), it)};

      while (it != str.end()) {
        auto numBegin = std::find_if(it, str.end(), [](const char c) { return c != '-'; });
        auto numEnd = std::find(numBegin, str.end(), '-');
        depths.push_back(numBegin - it);
        vals.push_back(toInt(numBegin, numEnd));
        it = numEnd;
      }
      return std::pair(depths, vals);
    };
    const auto [depths, vals] = tokenize(traversal);

    auto [left, right] = parseChildren(depths, vals, 1, depths.size());
    return new TreeNode(vals[0], left, right);
  }

private:
  static std::pair<TreeNode*, TreeNode*> parseChildren(const std::vector<int>& depths, const std::vector<int>& vals,
                                                       const int beginId, const int endId) {
    if (beginId == endId) {
      return {nullptr, nullptr};
    }

    const auto midId =
        std::find(depths.begin() + beginId + 1, depths.begin() + endId, depths[beginId]) - depths.begin();
    const auto [leftLeft, leftRight] = parseChildren(depths, vals, beginId + 1, midId);
    const auto left = new TreeNode(vals[beginId], leftLeft, leftRight);

    TreeNode* right = nullptr;
    if (midId != endId) {
      const auto [rightLeft, rightRight] = parseChildren(depths, vals, midId + 1, endId);
      right = new TreeNode(vals[midId], rightLeft, rightRight);
    }
    return {left, right};
  }
};
