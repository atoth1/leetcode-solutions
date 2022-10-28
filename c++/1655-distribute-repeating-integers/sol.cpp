// https://leetcode.com/problems/distribute-repeating-integers/

#include <algorithm>
#include <unordered_map>

class Solution {
public:
    bool canDistribute(vector<int>& nums, vector<int>& quantity) {
        std::unordered_map<int, int> numToCount{};
        for (const auto num : nums) {
            ++numToCount[num];
        }
        std::sort(quantity.begin(), quantity.end(), [](const int l, const int r) {
            return l > r;
        });
        return impl(numToCount, quantity, 0);
    }
    
private:
    bool impl(
        std::unordered_map<int, int>& numToCount,
        const std::vector<int>& quantity,
        const int id
    ) {
        if (id == quantity.size()) {
            return true;
        } else {
            for (auto& p : numToCount) {
                if (quantity[id] <= p.second) {
                    p.second -= quantity[id];
                    if (impl(numToCount, quantity, id+1)) return true;
                    p.second += quantity[id];
                }
            }
            return false;
        }
    }
};

