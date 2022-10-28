// https://leetcode.com/problems/count-nice-pairs-in-an-array/

#include <cstdlib>
#include <unordered_map>

class Solution {
public:
    int countNicePairs(vector<int>& nums) {
        auto rev = [] (int num) {
            int ret = 0;
            while (num) {
                auto divmod = std::div(num, 10);
                ret = 10*ret + divmod.rem;
                num = divmod.quot;
            }
            return ret;
        };
        
        std::unordered_map<int, int> counts{};
        for (const auto num : nums) {
            int val = num - rev(num);
            ++counts[val];
        }
        
        auto sumInts = [] (const long long num) {
            static constexpr int modulus = 1000000007;
            int ret = num*(num-1)/2 % modulus;
            return ret;
        };
        
        static constexpr int modulus = 1000000009;
        int ret = 0;
        for (const auto& p : counts) {
            ret += sumInts(p.second);
            ret %= modulus;
        }
        return ret;
    }
};
