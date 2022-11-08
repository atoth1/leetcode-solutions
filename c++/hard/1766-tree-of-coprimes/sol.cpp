// https://leetcode.com/problems/tree-of-coprimes/

#include <algorithm>
#include <memory>
#include <numeric>

class Solution {
public:
    vector<int> getCoprimes(vector<int>& nums, vector<vector<int>>& edges) {
        // Set up graph structure
        const int N = nums.size();
        std::vector<std::shared_ptr<TreeNode>> nodes(N, nullptr);
        for (int id = 0; id < N; ++id) {
            nodes[id] = std::make_shared<TreeNode>();
            nodes[id]->id = id;
            nodes[id]->value = nums[id];
        }
        for (const auto& edge : edges) {
            nodes[edge[0]]->neighbors.push_back(nodes[edge[1]]);
            nodes[edge[1]]->neighbors.push_back(nodes[edge[0]]);
        }
        
        std::vector<int> sol(N, -1);
        impl(nodes[0], {}, sol);
        return sol;
    }
    
private:
    struct TreeNode {
        int id{};
        int value{};
        std::vector<std::shared_ptr<TreeNode>> neighbors{};
    };
    
    void impl(
        const std::shared_ptr<TreeNode> node, 
        std::vector<std::shared_ptr<TreeNode>> path,
        std::vector<int>& sol
    ) {
        // Save off to not recurse back through this node.
        const std::shared_ptr<TreeNode> prev = path.empty() ? nullptr : path.back();
        
        // Find valid ancestor if it exists.
        auto ancestor = std::find_if(path.crbegin(), path.crend(), [v = node->value] (const auto other) {
            return std::gcd(v, other->value) == 1;
        });
        if (ancestor != path.crend()) {
            sol[node->id] = (*ancestor)->id;
        }
        
        // Update path. Since only 50 unique values possible, we only care about most recent occurance of 
        // a given value, so erase previous occurance if it exists and path will have maximum length 50.
        // Seems like cheating, but whatever.
        auto occurance = std::find_if(path.cbegin(), path.cend(), [v = node->value] (const auto other) {
            return v == other->value;
        });
        if (occurance != path.cend()) {
            path.erase(occurance);
        }
        path.push_back(node);
        
        // Recurse.
        for (const auto neighbor : node->neighbors) {
            if (!prev || neighbor->id != prev->id) impl(neighbor, path, sol);
        }
    }
};
