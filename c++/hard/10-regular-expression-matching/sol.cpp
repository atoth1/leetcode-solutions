// https://leetcode.com/problems/regular-expression-matching/

#include <optional>
#include <string_view>
#include <vector>

class Solution {
public:
    static bool isMatch(const std::string_view s, const std::string_view p) {
        const int m = s.size();
        const int n = p.size();
        auto makeCache = [&]() {
            cache_t cache(m + 1, std::vector<std::optional<bool>>(n + 1));
            cache[0][0] = true;

            // No non-empty string can match an empty pattern
            for (int sCount = 1; sCount <= m; ++sCount) {
                cache[sCount][0] = false;
            }

            // Empty string may match a pattern of the form .* repeated however many times
            for (int pCount = 1; pCount <= n; ++pCount) {
                if ((pCount % 2) == 0 && p[pCount - 1] == '*' && *cache[0][pCount - 2]) {
                    cache[0][pCount] = true;
                } else {
                    cache[0][pCount] = false;
                }
            }
            return cache;
        };
        cache_t cache = makeCache();
        return impl(s, m, p, n, cache);
    }
    
private:
    using cache_t = std::vector<std::vector<std::optional<bool>>>;
    
    static bool impl(
        const std::string_view s,
        const int sCount,
        const std::string_view p,
        const int pCount,
        cache_t& cache
    ) {
        if (cache[sCount][pCount]) {
            return *cache[sCount][pCount];
        } else {
            auto singleCharMatch = [](const char sc, const char pc) {
                return sc == pc || pc == '.';
            };
            
            bool matches = false;
            if (singleCharMatch(s[sCount - 1], p[pCount - 1])) {
                matches = impl(s, sCount - 1, p, pCount - 1, cache);
            } else if (p[pCount - 1] == '*') {
                matches = impl(s, sCount, p, pCount - 2, cache);
                int sPos = sCount - 1;
                while (!matches && sPos >= 0 && singleCharMatch(s[sPos], p[pCount - 2])) {
                    if (impl(s, sPos, p, pCount - 2, cache)) {
                        matches = true;
                    }
                    --sPos;
                }
            }
            cache[sCount][pCount] = matches;
            return matches;
        }
    }
};
