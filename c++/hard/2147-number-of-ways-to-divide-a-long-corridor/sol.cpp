// https://leetcode.com/problems/number-of-ways-to-divide-a-long-corridor/

#include <algorithm>
#include <numeric>
#include <string_view>

class Solution {
public:
    static int numberOfWays(const std::string_view str) {
        const int sCount = std::count(str.begin(), str.end(), 'S');
        if (sCount == 0 || (sCount & 1)) {
            return 0;
        } else {
            auto advancePastTwoS = [](const auto start) {
                auto it = start;
                int sCount = 0;
                while (sCount < 2) {
                    if (*it == 'S') ++sCount;
                    ++it;
                }
                return it;
            };
            
            auto advanceToNextS = [](const auto start) {
                auto it = start;
                while (*it != 'S') ++it;
                return it;
            };
            
            auto modTimes = [](const long long x, const int y) {
                return static_cast<int>((x * y) % 1000000007);
            };
            
            int prod = 1;
            auto it = str.begin();
            for (int repeat = 0; repeat < (sCount / 2) - 1; ++repeat) {
                auto gapBegin = advancePastTwoS(it);
                auto gapEnd = advanceToNextS(gapBegin);
                prod = modTimes(prod, 1 + gapEnd - gapBegin);
                it = gapEnd;
            }
            
            return prod;
        }
    }
};
