// https://leetcode.com/problems/orderly-queue/

#include <algorithm>

class Solution {
public:
    string orderlyQueue(string s, int k) {
        if (k >= 2) {
            std::sort(s.begin(), s.end());
            return s;
        }
        
        int n = s.size();
        std::string tmp(s.begin(), s.end() - 1);
        s.append(tmp);
        
        auto comp = [&](const int candidate, const int current) {
            for (int offset = 0; offset < n; ++offset) {
                if (s[candidate + offset] < s[current + offset]) {
                    return true;
                } else if (s[candidate + offset] > s[current + offset]) {
                    return false;
                }
            }
            // If we get here, all characters are the same, could
            // return either true or false, it doesn't matter.
            return false;
        };
        
        auto minStart = 0;
        for (int pos = 1; pos < n; ++pos) {
            if (comp(pos, minStart)) minStart = pos;
        }
        return s.substr(minStart, n);
    }
};
