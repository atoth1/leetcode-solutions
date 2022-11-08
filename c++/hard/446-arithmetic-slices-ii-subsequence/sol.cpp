// https://leetcode.com/problems/arithmetic-slices-ii-subsequence/

class Solution {
public:
    int numberOfArithmeticSlices(vector<int>& nums) {
        std::map<std::vector<int>, int> prevDiscoveredToCount;
        for (int k = 2; k < nums.size(); ++k)
        {
            // Check if this value extends any previously discovered valid subsequences
            std::vector<std::pair<std::vector<int>, int>> newSequences;
            for (const auto& prev : prevDiscoveredToCount)
            {
                long diff = static_cast<long>(*(prev.first.end()-1)) - *(prev.first.end()-2);
                if (nums[k] == *(prev.first.end()-1) + diff)
                {
                    auto newSequence = prev.first;
                    newSequence.push_back(nums[k]);
                    newSequences.push_back({std::move(newSequence), prev.second});
                }
            }
            for (auto& newSequence : newSequences)
            {
                prevDiscoveredToCount[std::move(newSequence.first)] += newSequence.second;
            }
            
            // Check for length-3 subsequences ending here
            for (int j = k-1; j > 0; --j)
            {
                long diff = static_cast<long>(nums[k]) - nums[j];
                long target = nums[j] - diff;
                for (int i = j-1; i >= 0; --i)
                {
                    if (nums[i] == target)
                    {
                        ++prevDiscoveredToCount[{nums[i], nums[j], nums[k]}];
                    }
                }
            }
        }
        
        int count = 0;
        for (const auto p : prevDiscoveredToCount)
        {
            count += p.second;
        }
        return count;
    }
};
