// https://leetcode.com/problems/top-k-frequent-words/

#include <algorithm>
#include <queue>
#include <unordered_map>
#include <utility>

class Solution {
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        std::unordered_map<std::string, int> counts;
        for (const auto& word : words)
        {
            ++counts[word];
        }
        
        using val_t = std::unordered_map<std::string, int>::const_iterator;
        auto comp = [] (const val_t& l, const val_t& r) {
            return l->second == r-> second ? l->first < r->first : l->second > r->second;
        };
        std::priority_queue<val_t, std::vector<val_t>, decltype(comp)> kFrequent(comp);
        for (auto it = counts.cbegin(); it != counts.cend(); ++it)
        {
            if (kFrequent.size() < k)
            {
                kFrequent.push(it);
            }
            else if (comp(it, kFrequent.top()))
            {
                kFrequent.pop();
                kFrequent.push(it);
            }
        }
        
        std::vector<std::string> ret;
        ret.reserve(k);
        while (!kFrequent.empty())
        {
            ret.push_back(kFrequent.top()->first);
            kFrequent.pop();
        }
        std::reverse(ret.begin(), ret.end());
        return ret;
    }
};
