// https://leetcode.com/problems/minimum-operations-to-make-the-array-k-increasing/

#include <algorithm>
#include <cstdlib>
#include <vector>

class Solution {
public:
  static int kIncreasing(const std::vector<int>& arr, const int k) {
    auto stridedSubsequenceLength = [divmod = std::div(arr.size(), k)](const int startId) {
      return startId < divmod.rem ? 1 + divmod.quot : divmod.quot;
    };

    auto stridedSubsequenceMaxNonIncreasingSubsequenceLength = [&](const auto startId) {
      std::vector<int> vec{};
      for (int id = startId; id < arr.size(); id += k) {
        if (vec.empty() || arr[id] >= vec.back()) {
          vec.push_back(arr[id]);
        } else {
          const auto it = std::upper_bound(vec.begin(), vec.end(), arr[id]);
          *it = arr[id];
        }
      }
      return vec.size();
    };

    int cost = 0;
    for (int startId = 0; startId < k; ++startId) {
      cost += stridedSubsequenceLength(startId) - stridedSubsequenceMaxNonIncreasingSubsequenceLength(startId);
    }
    return cost;
  }
};
