// https://leetcode.com/problems/earliest-possible-day-of-full-bloom/

#include <algorithm>

class Solution {
public:
    int earliestFullBloom(vector<int>& plantTime, vector<int>& growTime) {
        std::vector<int> ids(plantTime.size());
        std::iota(ids.begin(), ids.end(), 0);
        std::sort(ids.begin(), ids.end(), [&](const int l, const int r) {
            return growTime[l] > growTime[r];
        });
        
        int earliest = 0;
        int plantingTime = 0;
        for (const auto id : ids) {
            plantingTime += plantTime[id];
            int candidate = plantingTime + growTime[id];
            if (candidate > earliest) earliest = candidate;
        }
        return earliest;
    }
};
