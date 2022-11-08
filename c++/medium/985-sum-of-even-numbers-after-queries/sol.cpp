// https://leetcode.com/problems/sum-of-even-numbers-after-queries/

#include <algorithm>

class Solution {
public:
    vector<int> sumEvenAfterQueries(vector<int>& nums, vector<vector<int>>& queries) {
        int sum = 0;
        std::vector<int> ret{};
        std::for_each(nums.cbegin(), nums.cend(), [&](const int x) {if ((x&1) == 0) sum += x;});
        std::for_each(queries.cbegin(), queries.cend(), [&](const std::vector<int>& whyIsntThisPair) {
            int update = whyIsntThisPair[0];
            int id = whyIsntThisPair[1];
            if ((nums[id]&1) == 0) sum -= nums[id];
            nums[id] += update;
            if ((nums[id]&1) == 0) sum += nums[id];
            ret.push_back(sum);
        });
        return ret;
    }
};
