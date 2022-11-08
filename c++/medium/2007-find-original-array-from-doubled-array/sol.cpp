// https://leetcode.com/problems/find-original-array-from-doubled-array/

#include <map>

class Solution {
public:
    vector<int> findOriginalArray(vector<int>& changed) {
        if (changed.size() % 2 == 1) return {};
        
        std::map<int, int> counts;
        for (const auto num : changed) ++counts[num];
        
        std::vector<int> ret;
        if (counts.begin()->first == 0) {
            int quot = counts.begin()->second/2;
            int rem = counts.begin()->second - 2*quot;
            if (rem) {
                return {};
            } else {
                for (int repeat = 0; repeat < quot; ++repeat) ret.push_back(0);
                counts.erase(counts.begin());
            }
        }
        
        while (!counts.empty()) {
            auto smaller = counts.begin();
            auto greater = counts.find(2 * smaller->first);
            
            if (greater == counts.end() || smaller->second > greater->second) {
              return {};
            } else {
                for (int repeat = 0; repeat < smaller->second; ++repeat) ret.push_back(smaller->first);
                if (greater->second > smaller->second) {
                    greater->second -= smaller->second;
                } else {
                    counts.erase(greater);
                }
                counts.erase(smaller);
            }
        }
        return ret;
    }
};
