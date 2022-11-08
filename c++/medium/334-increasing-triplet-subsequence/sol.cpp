// https://leetcode.com/problems/increasing-triplet-subsequence/

class Solution {
public:
    bool increasingTriplet(vector<int>& nums) {
        int middleId = -1;
        int maxId = nums.size() - 1;
        for (int id = nums.size() - 2; id >= 0; --id) {
            if (nums[id] > nums[maxId]) {
                maxId = id;
            } else if (nums[id] < nums[maxId]) {
                if (middleId == -1 || nums[id] > nums[middleId]) {
                    middleId = id;
                } else if (nums[id] < nums[middleId]) {
                    return true;
                }
            }
        }
        return false;
    }
};
