// https://leetcode.com/problems/tuple-with-same-product/

#include <unordered_map>

class Solution {
public:
    int tupleSameProduct(vector<int>& nums) {
        std::unordered_map<int, int> prodToCount{};
        for (auto l = nums.cbegin(); l != nums.cend()-1; ++l) {
            for (auto r = l+1; r != nums.cend(); ++r) {
                ++prodToCount[*l * *r];
            }
        }
        
        int total = 0;
        for (const auto p : prodToCount) {
            int count = p.second;
            total += (count*(count-1))/2;
        }
        return 8*total;
    }
};
