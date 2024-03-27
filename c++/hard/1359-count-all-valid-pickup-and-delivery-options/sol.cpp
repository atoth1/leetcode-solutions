// https://leetcode.com/problems/count-all-valid-pickup-and-delivery-options/

#include <array>

namespace {
    static constexpr int MAX_N = 500;
    static constexpr int MOD = 1000000007;
    
    consteval int sumOneToN(const int n) {
        return (static_cast<long long>(n + 1) * n / 2) % MOD;
    }
    
    consteval auto initCache() {
        std::array<int, MAX_N + 1> ret{};
        ret[1] = 1;
        for (int n = 2; n <= MAX_N; ++n) {
            ret[n] = (static_cast<long long>(ret[n - 1]) * sumOneToN(2 * n - 1)) % MOD;
        }
        return ret;
    }
    static constexpr auto cache = initCache();
}

class Solution {
public:
    int countOrders(const int n) {
        return cache[n];
    }
};
