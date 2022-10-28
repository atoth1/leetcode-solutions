// https://leetcode.com/problems/maximize-number-of-subsequences-in-a-string/

#include <algorithm>

class Solution {
public:
    long long maximumSubsequenceCount(string text, string pattern) {
        if (pattern[0] == pattern[1]) {
            int count = 0;
            for (const auto c : text) {
                if (c == pattern[0]) ++count;
            }
            return static_cast<long long>(count)*(count+1)/2;
        } else {
            long long numFirstBefore = 0;
            long long numSecondAfter = std::count(text.cbegin(), text.cend(), pattern[1]);
            long long total = 0;
            
            // If adding pattern[0] at front
            long long maxAdded = numSecondAfter;
            for (const auto c : text) {
                if (c == pattern[0]) {
                    total += numSecondAfter;
                    ++numFirstBefore;
                }
                if (c == pattern[1]) --numSecondAfter;
            }
            // Would ading pattern[1] at end create more?
            maxAdded = std::max(maxAdded, numFirstBefore);
            return total + maxAdded;
        }
    }
};
