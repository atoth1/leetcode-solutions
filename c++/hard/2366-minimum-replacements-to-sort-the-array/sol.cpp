// https://leetcode.com/problems/minimum-replacements-to-sort-the-array/

#include <cstddef>
#include <iterator>
#include <vector>

class Solution {
public:
    long long minimumReplacement(const std::vector<int>& nums) {
        long long count = 0;
        int bound = nums.back();
        for (auto it = std::next(nums.rbegin()); it != nums.rend(); ++it) {
            if (*it > bound) {
                const auto divmod = std::div(*it, bound);
                if (divmod.rem) {
                    count += divmod.quot;
                    bound = *it / (divmod.quot + 1);
                } else {
                    count += divmod.quot - 1;
                }
            } else {
                bound = *it;
            }
        }
        return count;
    }
};
