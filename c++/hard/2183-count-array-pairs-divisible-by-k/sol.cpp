// https://leetcode.com/problems/count-array-pairs-divisible-by-k/

#include <numeric>
#include <vector>

class Solution {
public:
  static long long countPairs(const std::vector<int>& nums, const int k) {
    std::vector<int> residueCounts(k);
    for (const int num : nums) {
      ++residueCounts[num % k];
    }

    auto longTimes = [](long long n1, const int n2) {
      n1 *= n2;
      return n1;
    };

    const int n = nums.size();
    long long ret = 0;
    for (int residue1 = 0; residue1 < k; ++residue1) {
      if ((longTimes(residue1, residue1) % k) == 0) {
        ret += longTimes(residueCounts[residue1] - 1, residueCounts[residue1]) / 2;
      }

      const int gcd = std::gcd(residue1, k);
      if (gcd > 1) {
        const int residue2 = k / gcd;
        const int initCoef = (residue1 + residue2) / residue2;
        for (int coef = initCoef; coef * residue2 < k; ++coef) {
          ret += longTimes(residueCounts[residue1], residueCounts[coef * residue2]);
        }
      }
    }
    return ret;
  }
};