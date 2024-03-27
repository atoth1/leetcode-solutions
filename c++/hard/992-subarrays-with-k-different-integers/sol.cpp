// https://leetcode.com/problems/subarrays-with-k-different-integers/

#include <iterator>
#include <unordered_map>
#include <vector>

class Solution {
public:
  static int subarraysWithKDistinct(const std::vector<int>& nums, const int k) {
    std::unordered_map<int, int> counts{};
    auto minimalEnd = nums.begin();
    auto maximalEnd = nums.begin();
    int ret = 0;
    for (const int num : nums) {
      while (minimalEnd < nums.end() && counts.size() < k) {
        ++counts[*minimalEnd++];
      }
      if (counts.size() < k)
        break;

      while (maximalEnd < nums.end() && counts.contains(*maximalEnd)) {
        ++maximalEnd;
      }

      ret += 1 + std::distance(minimalEnd, maximalEnd);

      --counts[num];
      if (counts[num] == 0) {
        counts.erase(num);
      }
    }
    return ret;
  }
};