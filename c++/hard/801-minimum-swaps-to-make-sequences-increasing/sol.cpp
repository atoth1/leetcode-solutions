// https://leetcode.com/problems/minimum-swaps-to-make-sequences-increasing/

class Solution {
public:
    int minSwap(vector<int>& nums1, vector<int>& nums2) {
        auto min = [] (const int l, const int r) { return l < r ? l : r; };
        
        int n = nums1.size();
        // Would normally do debug check on array sizes
        int minNoPrevSwap = 0;
        int minWithPrevSwap = 1;
        for (int i = 1; i < n; ++i)
        {
            int tmp1 = 0;
            int tmp2 = 0;
            
            // First, if we don't swap at index i
            if (nums1[i-1] >= nums1[i] || nums2[i-1] >= nums2[i])
            {
                // Need to swap at previous index
                tmp1 = minWithPrevSwap;
            }
            else if (nums2[i-1] >= nums1[i] || nums1[i-1] >= nums2[i])
            {
                // Can't swap at previous index
                tmp1 = minNoPrevSwap;
            }
            else
            {
                // Could swap or not swap at previous index, pick one with fewer swaps
                tmp1 = min(minNoPrevSwap, minWithPrevSwap);
            }
            
            // Now, if we swap at position i
            if (nums2[i-1] >= nums1[i] || nums1[i-1] >= nums2[i])
            {
                // Need to swap at previous index
                tmp2 = minWithPrevSwap + 1;
            }
            else if (nums1[i-1] >= nums1[i] || nums2[i-1] >= nums2[i])
            {
                // Can't swap both at this index and at previous index
                tmp2 = minNoPrevSwap + 1;
            }
            else
            {
                // Could swap or not swap at previous index, pick one with fewer swaps
                tmp2 = min(minNoPrevSwap, minWithPrevSwap) + 1;
            }
            
            minNoPrevSwap = tmp1;
            minWithPrevSwap = tmp2;
        }
        return min(minNoPrevSwap, minWithPrevSwap);
    }
};
