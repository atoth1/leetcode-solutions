// https://leetcode.com/problems/compare-strings-by-frequency-of-the-smallest-character/

#include <map>
#include <utility>

class Solution {
public:
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words) {
        auto objective = [] (const std::string& s) {
            auto smallestWithCount = std::make_pair('z', 0);
            for (const auto c : s) {
                if (c < smallestWithCount.first) {
                    smallestWithCount = std::make_pair(c, 1);
                } else if (c == smallestWithCount.first) {
                    ++smallestWithCount.second;
                }
            }
            return smallestWithCount.second;
        };
        
        std::map<int, int> counts{};
        for (const auto& word : words) {
            ++counts[objective(word)];
        }
        
        auto inclusive_scan = [] (std::map<int, int>& counts) {
            int prev = 0;
            for (auto& p : counts) {
                prev += p.second;
                p.second = prev;
            }
        };
        inclusive_scan(counts);
        
        std::vector<int> ret{};
        for (const auto& query : queries) {
            auto it = counts.upper_bound(objective(query));
            if (it == counts.cbegin()) {
                ret.push_back(words.size());
            } else {
                --it;
                ret.push_back(words.size() - it->second);
            }
        }
        return ret;
    }
};
