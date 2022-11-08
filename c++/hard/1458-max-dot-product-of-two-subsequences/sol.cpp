// https://leetcode.com/problems/max-dot-product-of-two-subsequences/

#include <algorithm>

class Solution {
public:
    int maxDotProduct(vector<int>& nums1, vector<int>& nums2) {
        const int m = nums1.size();
        const int n = nums2.size();
        std::vector<std::vector<int>> maxEndingAt(m, std::vector<int>(n, 0));
        std::vector<std::vector<int>> maxPriorTo(m, std::vector<int>(n, 0));
        int max = -1000000000;
        for (int id1 = 0; id1 < m; ++id1) {
            for (int id2 = 0; id2 < n; ++id2) {
                if (id1 > 0 && id2 > 0) {
                        maxPriorTo[id1][id2] = std::max({ maxEndingAt[id1-1][id2-1],
                            maxPriorTo[id1][id2-1], maxPriorTo[id1-1][id2] });
                }
                maxEndingAt[id1][id2] = nums1[id1] * nums2[id2] + maxPriorTo[id1][id2];
                if (maxEndingAt[id1][id2] > max) max = maxEndingAt[id1][id2];
            }
        }
        return max;
    }
};
