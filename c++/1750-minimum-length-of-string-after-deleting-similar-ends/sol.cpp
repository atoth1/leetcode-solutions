// https://leetcode.com/problems/minimum-length-of-string-after-deleting-similar-ends/

#include <string_view>

class Solution {
public:
    int minimumLength(string s) {
        return impl(s);
    }
    
private:
    int impl(std::string_view s) {
        while (s.size() > 1 && s.front() == s.back()) {
            char c = s.front();
            while (!s.empty() && s.front() == c) s.remove_prefix(1);
            while (!s.empty() && s.back() == c) s.remove_suffix(1);
        }
        return s.size();
    }
};
