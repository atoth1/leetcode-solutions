// https://leetcode.com/problems/array-with-elements-not-equal-to-average-of-neighbors/

#include <algorithm>

class Solution {
public:
    vector<int> rearrangeArray(vector<int>& nums) {
        // Check if input satisfies before more expensive operations
        bool inputWorks = true;
        for (int id = 1; id < nums.size()-1; ++id) {
            if (nums[id-1] + nums[id+1] == 2*nums[id]) {
                inputWorks = false;
                break;
            }
        }
        if (inputWorks) return nums;
        
        std::sort(nums.begin(), nums.end());
        std::vector<int> ret(nums.size());
        auto smallerIt = nums.cbegin();
        auto largerIt = nums.cbegin() + nums.size()/2;
        const int bound = 2*(nums.size()/2);
        for (int id = 0; id < bound; id += 2) {
            ret[id] = *largerIt++;
            ret[id+1] = *smallerIt++;
        }
        if (largerIt != nums.cend()) ret.back() = *largerIt;
        return ret;
    }
};
