// https://leetcode.com/problems/subsequence-with-the-minimum-score/

#include <iterator>
#include <string_view>
#include <vector>

class Solution {
public:
    static int minimumScore(const std::string_view s, const std::string_view t) {
        auto hasSubsequence = [](
            const std::string_view str1,
            const std::string_view str2
        ) {
            auto it = str2.begin();
            for (const char c : str1) {
                if (it != str2.end() && c == *it) ++it;
            }
            return it == str2.end();
        };
        if (hasSubsequence(s, t)) return 0;
        
        auto isValidWindowLength = [](
            const std::string_view str1,
            const std::string_view str2,
            const int len
        ) {
            const int target = str2.size() - len;
            std::vector<int> backIds{};
            auto it1 = str2.rbegin();
            for (int id = str1.size() - 1; id >= 0; --id) {
                if (it1 != str2.rend() && *it1 == str1[id]) {
                    backIds.push_back(id);
                    ++it1;
                }
            }
            if (backIds.size() >= target) return true;
            
            auto it2 = str1.begin();
            for (int frontCount = 1; frontCount + len <= str2.size(); ++frontCount) {
                while (it2 != str1.end() && *it2 != str2[frontCount - 1]) ++it2;
                if (it2 == str1.end()) return false;
                while (!backIds.empty() && backIds.back() <= std::distance(str1.begin(), it2)) backIds.pop_back();
                ++it2;
                if (frontCount + backIds.size() >= target) return true;
            }
            return false;
        };
        
        int l = 0;
        int r = t.size();
        while (l + 1 != r) {
            const int m = l + (r - l) / 2;
            if (isValidWindowLength(s, t, m)) {
                r = m;
            } else {
                l = m;
            }
        }
        return r;
    }
};
