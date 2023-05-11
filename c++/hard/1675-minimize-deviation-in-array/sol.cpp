// https://leetcode.com/problems/minimize-deviation-in-array/

#include <iterator>
#include <set>
#include <vector>

class Solution {
public:
    int minimumDeviation(const std::vector<int>& nums) {
        std::set<int> vals{};
        for (const int num : nums) {
            if (num & 1) {
                vals.insert(2*num);
            } else {
                vals.insert(num);
            }
        }
        
        auto deviation = [&]() {
            return *std::prev(vals.end()) - *vals.begin();
        };
        
        int min = deviation();
        while (vals.size() > 1) {
            const int val = *std::prev(vals.end());
            if (val & 1) return min;
            
            vals.erase(std::prev(vals.end()));
            vals.insert(val/2);
            const int candidate = deviation();
            if (candidate < min) min = candidate;
        }
        return 0;
    }
};