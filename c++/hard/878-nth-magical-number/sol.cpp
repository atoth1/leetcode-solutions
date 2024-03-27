// https://leetcode.com/problems/nth-magical-number/

#include <algorithm>
#include <numeric>

class Solution {
public:
  static int nthMagicalNumber(const int n, const int a, const int b) {
    if (n == 1)
      return std::min(a, b);

    // Return count of magic numbers <= k
    auto objective = [a = a, b = b, lcm = std::lcm(a, b)](const long long k) { return k / a + k / b - k / lcm; };

    long long l = 0;
    long long r = static_cast<long long>(n) * std::min(a, b);
    while (l + 1 != r) {
      const long long m = l + (r - l) / 2;
      if (objective(m) < n) {
        l = m;
      } else {
        r = m;
      }
    }
    static constexpr int MOD = 1000000007;
    return r % MOD;
  }
};
