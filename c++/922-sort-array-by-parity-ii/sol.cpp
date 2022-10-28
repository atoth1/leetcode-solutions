// https://leetcode.com/problems/sort-array-by-parity-ii/

#include <utility>

class Solution {
public:
    vector<int> sortArrayByParityII(vector<int>& nums) {
        int evensBegin = 0;
        int evensEnd = 0;
        int oddsBegin = 1;
        int oddsEnd = 1;
        int pos = 0;
        while (pos < nums.size()) {
            if ((pos&1) == 0 && (nums[pos]&1) == 1) {
                std::swap(nums[pos], nums[oddsEnd]);
                oddsEnd += 2;
            } else if ((pos&1) == 1 && (nums[pos]&1) == 0) {
                std::swap(nums[pos], nums[evensEnd]);
                evensEnd += 2;
            } else {
                if ((pos&1) == 0 && pos == evensEnd) evensEnd += 2;
                if ((pos&1) == 1 && pos == oddsEnd) oddsEnd += 2;
                ++pos;
            }
        }
        return nums;
    }
};
