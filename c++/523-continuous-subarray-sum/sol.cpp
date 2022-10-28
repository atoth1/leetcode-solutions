// https://leetcode.com/problems/continuous-subarray-sum/

#include <unordered_map>
#include <utility>

class Solution {
public:
    bool checkSubarraySum(vector<int>& nums, int k) {
        if (nums.size()  < 2) return false;
        
        int sum = nums[0] % k;
        std::unordered_map<int, int> prefixSums{ std::make_pair(sum, 0) };
        for (int id = 1; id < nums.size(); ++id) {
            // Probably don't need cast here per problem specs (total sum fits in int)
            sum = (sum + nums[id]) % k;
            
            auto it = prefixSums.find(sum);
            if (sum == 0 || (it != prefixSums.end() && it->second != id-1)) return true;
            if (it == prefixSums.end()) prefixSums[sum] = id;
        }
        return false;
    }
};
