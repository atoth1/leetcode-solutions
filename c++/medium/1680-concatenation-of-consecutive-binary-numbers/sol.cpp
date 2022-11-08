// https://leetcode.com/problems/concatenation-of-consecutive-binary-numbers/

class Solution {
public:
    int concatenatedBinary(int n) {
        static constexpr int MODULUS = 1000000007;
        static std::vector<int> cache{1};
        cache.reserve(100000);
        if (cache.size() == 1) {
            for (int k = 2; k <= 100000; ++k) {
                int tmp = k;
                long long next = cache.back();
                while (tmp) {
                    tmp >>= 1;
                    next <<= 1;
                }
                next += k;
                next %= MODULUS;
                cache.push_back(next);
            }
        }
        return cache[n-1];
    }
};
