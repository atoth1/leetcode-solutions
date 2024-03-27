// https://leetcode.com/problems/preimage-size-of-factorial-zeroes-function/

class Solution {
public:
    static int preimageSizeFZF(const int k) {
        if (k == 0) {
            return 5;
        }
        
        auto factorialZeroCount = [](long long n) {
            long long ret = 0;
            while (n) {
                n /= 5;
                ret += n;
            }
            return ret;
        };
        
        long long l = 0;
        long long r = 5ll * k + 1;
        while (l + 1 != r) {
            const auto m = l + (r - l) / 2;
            const auto count = factorialZeroCount(m);
            if (count < k) {
                l = m;
            } else if (count > k) {
                r = m;
            } else {
                return 5;
            }
        }
        return 0;
    }
};
