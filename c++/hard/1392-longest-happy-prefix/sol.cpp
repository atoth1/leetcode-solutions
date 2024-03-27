// https://leetcode.com/problems/longest-happy-prefix/

#include <string>
#include <string_view>

class Solution {
public:
    std::string longestPrefix(const std::string_view s) {
        static constexpr int MOD = 1000000007;
        std::string_view ret = "";
        int prefixHash = 0;
        int prefixFactor = 1;
        int suffixHash = 0;
        for (int count = 1; count < s.size(); ++count) {
            prefixHash = (static_cast<long long>(s[count - 1] - 'a' + 1) * prefixFactor + prefixHash) % MOD;
            prefixFactor = (26ll * prefixFactor) % MOD;
            suffixHash = (s[s.size() - count] - 'a' + 1 + 26ll * suffixHash) % MOD;
            if (prefixHash == suffixHash) {
                ret = s.substr(0, count);
            }
        }
        return std::string(ret);
    }
};
