// https://leetcode.com/problems/maximum-sum-of-3-non-overlapping-subarrays/

#include <queue>
#include <utility>

class Solution {
public:
    vector<int> maxSumOfThreeSubarrays(vector<int>& nums, int k) {
        std::vector<int> kSums(nums.size()-k+1, 0);
        {
            int sum = 0;
            auto lit = nums.cbegin();
            auto rit = nums.cbegin();
            auto it = kSums.begin();
            while (rit != nums.cend())
            {
                sum += *rit++;
                if (rit-lit == k)
                {
                    *it++ = sum;
                    sum -= *lit++;
                }
            }
        }
        
        using val_t = std::pair<int, int>;
        auto comp = [] (const val_t& l, const val_t& r) {
            return l.first == r.first ? l.second > r.second : l.first < r.first;
        };
        std::priority_queue<val_t, std::vector<val_t>, decltype(comp)> rightMaxes(comp);
        for (int i = 2*k; i < kSums.size(); ++i)
        {
            rightMaxes.push(std::make_pair(kSums[i], i));
        }
        
        val_t leftMax = std::make_pair(0, 0);
        std::pair<int, std::vector<int>> max = std::make_pair(0, std::vector<int>{});
        for (int i = k; i < kSums.size()-k; ++i)
        {
            if (kSums[i-k] > leftMax.first) leftMax = std::make_pair(kSums[i-k], i-k);
            while (rightMaxes.top().second < i+k) rightMaxes.pop();
            int curr = leftMax.first + kSums[i] + rightMaxes.top().first;
            if (curr > max.first) max = std::make_pair(
                curr, std::vector<int>{leftMax.second, i, rightMaxes.top().second});
        }
        return max.second;
    }
};
