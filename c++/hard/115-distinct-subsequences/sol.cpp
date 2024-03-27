// https://leetcode.com/problems/distinct-subsequences/

#include <algorithm>
#include <string_view>
#include <utility>
#include <vector>

class Solution {
public:
    int numDistinct(std::string_view s, const std::string_view t) {
        auto trimExtraneous = [](std::string_view& str1, const std::string_view str2) {
            while (!str1.empty() && str1.front() != str2.front()) str1.remove_prefix(1);
            while (!str1.empty() && str1.back() != str2.back()) str1.remove_suffix(1);
        };
        trimExtraneous(s, t);
        
        
        if (s.size() == t.size()) return s == t;
        
        auto hasAsSubset = [](std::string_view str1, const std::string_view str2) {
            auto it = str1.begin();
            for (const char c: str2) {
                while (it != str1.end() && *it != c) ++it;
                if (it == str1.end()) return false;
                ++it;
            }
            return true;
        };
        if (!hasAsSubset(s, t)) return 0;
        
        // Ugh, intermediate states can overflow int even though:
        // "The test cases are generated so that the answer fits on a 32-bit signed integer"
        std::vector<long long> curr(s.size() + 1, 1);
        std::vector<long long> next(s.size() + 1);
        for (int tCount = 1; tCount <= t.size(); ++tCount) {
            for (int sCount = tCount; sCount <= s.size(); ++sCount) {
                next[sCount] = next[sCount - 1];
                if (t[tCount - 1] == s[sCount - 1]) next[sCount] += curr[sCount - 1];
            }
            std::swap(curr, next);
            std::fill(next.begin(), next.end(), 0);
        }
        return static_cast<int>(curr[s.size()]);
    }
};
