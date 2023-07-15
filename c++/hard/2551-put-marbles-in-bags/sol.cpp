// https://leetcode.com/problems/put-marbles-in-bags/

#include <algorithm>
#include <vector>

class Solution {
public:
    long long putMarbles(const std::vector<int>& weights, int k) {
        const int n = weights.size();
        if (n == k) return 0;
        
        std::vector<int> boundarySums(n - 1);
        for (int id = 0; id < n - 1; ++id) boundarySums[id] = weights[id] + weights[id + 1];
        std::sort(boundarySums.begin(), boundarySums.end());
        
        long long diff = 0;
        for (int offset = 0; offset < k - 1; ++offset) {
            diff -= boundarySums[offset]; 
            diff += boundarySums[n - offset - 2];
        }
        return diff;
    }
};