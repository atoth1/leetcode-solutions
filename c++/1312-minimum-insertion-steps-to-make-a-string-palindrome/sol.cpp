// https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/

#include <string_view>
#include <unordered_set>

class Solution {
public:
    int minInsertions(string s) {
        std::unordered_map<std::string_view, int> cache;
        return impl(s, cache);
    }
    
private:
    int impl(const std::string_view s, std::unordered_map<std::string_view, int>& cache) {
        auto it = cache.find(s);
        if (it != cache.end()) return it->second;
        
        if (s.size() == 0 || s.size() == 1) {
            return 0;
        }
        else if (s.front() == s.back()) {
            int ret = impl(s.substr(1, s.size() - 2), cache);
            cache[s] = ret;
            return ret;
        } else {
            int tmp1 = impl(s.substr(0, s.size() - 1), cache);
            int tmp2 = impl(s.substr(1, s.size() - 1), cache);
            int ret = tmp1 < tmp2 ? tmp1 : tmp2;
            cache[s] = ret + 1;
            return ret + 1;
        }
    }
};
