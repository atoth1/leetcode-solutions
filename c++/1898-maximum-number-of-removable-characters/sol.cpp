// https://leetcode.com/problems/maximum-number-of-removable-characters/

#include <array>
#include <unordered_set>
#include <utility>

class Solution {
public:
    int maximumRemovals(string s, string p, vector<int>& removable) {
        if (s.size() == p.size()) return 0;
        
        std::array<std::vector<int>, 26> charIds{};
        for (int id = 0; id < s.size(); ++id) {
            charIds[s[id] - 'a'].push_back(id);
        }
        
        auto subsequenceExists = [&] (const std::unordered_set<int>& removed) {
            using it_type = std::vector<int>::const_iterator;
            std::array<std::pair<it_type, it_type>, 26> pos;
            for (int offset = 0; offset < 26; ++offset) {
                const auto& ids = charIds[offset];
                pos[offset] = std::make_pair(ids.cbegin(), ids.cend());
            }
            
            int id = -1;
            for (const char c : p) {
                auto& its = pos[c - 'a'];
                while (its.first != its.second &&
                      (*its.first < id || removed.count(*its.first) == 1)) {
                    ++its.first;
                }
                if (its.first == its.second) return false;
                id = *its.first;
                ++its.first;
            }
            return true;
        };
        
        int l = 0;
        int r = removable.size() + 1;
        while (l+1 != r) {
            int m = (l + r)/2;
            std::unordered_set<int> removed{removable.cbegin(), removable.cbegin() + m};
            if (subsequenceExists(removed)) l = m;
            else r = m;
        }
        return l;
    }
};
