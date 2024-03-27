// https://leetcode.com/problems/sum-of-imbalance-numbers-of-all-subarrays/

#include <algorithm>
#include <iterator>
#include <vector>

class Solution {
public:
    int sumImbalanceNumbers(const std::vector<int>& nums) {
        int sum = 0;
        std::vector<bool> seen(nums.size());
        for (auto it1 = nums.begin(); it1 != nums.end(); ++it1) {
            std::fill(seen.begin(), seen.end(), false);
            seen[*it1 - 1] = true;
            int imbalance = 0;
            for (auto it2 = std::next(it1); it2 != nums.end(); ++it2) {
                if (!seen[*it2 - 1]) {
                    seen[(*it2 - 1)] = true;
                    ++imbalance;
                    if (*it2 >= 2 && seen[*it2 - 2]) {
                        --imbalance;
                    }
                    if (*it2 < nums.size() && seen[*it2]) {
                        --imbalance;
                    }
                }
                sum += imbalance;
            }
        }
        return sum;
    }
};
