// https://leetcode.com/problems/first-missing-positive/

class Solution {
public:
    int firstMissingPositive(vector<int>& nums) {
        auto in_range = [&] (int i) { return i >= 0 && i < nums.size(); };
        for (int i = 0; i < nums.size(); ++i)
        {
            if (nums[i] <= 0) continue;
            int curr = i;
            int next = nums[curr]-1;
            while (next != curr && in_range(next))
            {
                curr = next;
                next = nums[curr] - 1;
                nums[curr] = curr + 1;
            }
        }
        
        for (int i = 0; i < nums.size(); ++i)
        {
            if (nums[i] != i+1) return i+1;
        }
        return nums.size()+1;
    }
};
