// https://leetcode.com/problems/first-unique-character-in-a-string/

#include <array>
 
static constexpr std::array<int, 26> initializer = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

class Solution {
public:
    int firstUniqChar(string s) {
        if (s.empty()) return -1;
        std::array<int, 26> first(initializer);
        for (int i = 0; i < s.size(); ++i)
        {
            first[s[i]-'a'] = (first[s[i]-'a'] == -1) ? i : s.size();
        }
        int ret = s.size();
        for (int i = 0; i < 26; ++i)
        {
            int id = first[i];
            if (id >= 0 && id < ret)
            {
                ret = id;
            }
        }
        return ret < s.size() ? ret : -1;
    }
};

