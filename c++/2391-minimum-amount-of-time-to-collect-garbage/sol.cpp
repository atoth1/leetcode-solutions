// https://leetcode.com/problems/minimum-amount-of-time-to-collect-garbage/

#include <algorithm>

class Solution {
public:
    int garbageCollection(vector<string>& garbage, vector<int>& travel) {
        int gEnd = 0;
        int gCount = 0;
        int mEnd = 0;
        int mCount = 0;
        int pEnd = 0;
        int pCount = 0;
        for (int id = 0; id < garbage.size(); ++id) {
            int gs = 0;
            int ms = 0;
            int ps = 0;
            for (const auto c : garbage[id]) {
                if (c == 'G') ++gs;
                if (c == 'M') ++ms;
                if (c == 'P') ++ps;
            }
            if (gs) {
                gCount += gs;
                gEnd = id;
            }
            if (ms) {
                mCount += ms;
                mEnd = id;
            }
            if (ps) {
                pCount += ps;
                pEnd = id;
            }
        }
        
        int total = gCount + mCount + pCount;
        total += std::accumulate(travel.cbegin(), travel.cbegin() + gEnd, 0);
        total += std::accumulate(travel.cbegin(), travel.cbegin() + mEnd, 0);
        total += std::accumulate(travel.cbegin(), travel.cbegin() + pEnd, 0);
        return total;
    }
};