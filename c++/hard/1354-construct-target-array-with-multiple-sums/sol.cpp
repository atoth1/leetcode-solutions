// https://leetcode.com/problems/construct-target-array-with-multiple-sums/

#include <numeric>
#include <queue>
#include <span>

class Solution {
public:
    static bool isPossible(const std::span<const int> target) {
        if (target.size() == 1) return target[0] == 1;
        
        long long sum = std::accumulate(target.begin(), target.end(), 0ll);
        std::priority_queue<int> queue(target.begin(), target.end());
        
        // Work backwards
        while (queue.top() > 1) {
            int largest = queue.top();
            queue.pop();
            
            sum -= largest;
            if (sum >= largest) return false;
            largest %= sum;
            if (largest == 0) largest += sum;
            
            sum += largest;
            queue.push(largest);
        }
        return true;
    }
};
