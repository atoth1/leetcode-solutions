// https://leetcode.com/problems/count-of-smaller-numbers-after-self/

#include <map>

class Solution {
public:
    vector<int> countSmaller(vector<int>& nums) {
        std::map<int, CountLessAndEqual> valToMostRecent{};
        std::vector<int> ret(nums.size());
        for (int idx = nums.size()-1; idx >= 0; --idx) {
            auto it = valToMostRecent.lower_bound(nums[idx]);
            int countEqual = 1;
            if (it != valToMostRecent.end() && it->first == nums[idx]) {
                countEqual += it->second.countEqual;
            }
            if (it == valToMostRecent.begin()) {
                ret[idx] = 0;
            } else {
                --it;
                ret[idx] = it->second.countLess + it->second.countEqual;
            }
            valToMostRecent[nums[idx]] = CountLessAndEqual{ret[idx], countEqual};
        }
        return ret;
    }
    
private:
    struct CountLessAndEqual {
        int countLess;
        int countEqual;
    };
};
