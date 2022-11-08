// https://leetcode.com/problems/minimum-window-substring/

#include <array>
#include <string_view>

class Solution {
public:
    string minWindow(string s, string t) {
        if (s.size() < t.size()) return "";
        
        std::array<int, N> tCounts{};
        for (const auto c : t) ++tCounts[charToId(c)];
        
        std::array<int, N> sCounts{};
        std::string_view sView(s);
        std::string_view ret{};
        int start = 0;
        int end = 0;
        while (end < s.size()) {
            while (end < s.size() && !isSubset(tCounts, sCounts)) {
                ++sCounts[charToId(s[end])];
                ++end;
            }
            
            if (isSubset(tCounts, sCounts)) {
                while (sCounts[charToId(s[start])] > tCounts[charToId(s[start])]) {
                    --sCounts[charToId(s[start])];
                    ++start;
                }
                int n = end - start;
                if (ret.empty() || n < ret.size()) ret = sView.substr(start, n);
            }
            --sCounts[charToId(s[start])];
            ++start;
        }
        return std::string(ret);
    }
    
private:
    static constexpr int N = 52;
    
    static int charToId(const char c) {
        return 'a' <= c && c <= 'z' ? c - 'a' : c - 'A' + N/2;
    }
    
    static bool isSubset(const std::array<int, N>& sub, const std::array<int, N> super) {
        for (int id = 0; id < N; ++id) {
            if (sub[id] > super[id]) return false;
        }
        return true;
    }
};
