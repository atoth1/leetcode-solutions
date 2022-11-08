// https://leetcode.com/problems/smallest-rotation-with-highest-score/

#include <map>
#include <set>
#include <utility>

class Solution {
public:
    int bestRotation(vector<int>& nums) {
        using Interval = std::pair<int, int>;
        std::map<Interval, int> intervals{};
        int n = nums.size();
        for (int i = 0; i < n; ++i)
        {
            if (nums[i] == 0)
            {
                // Can just skip 0's since they will contribute a
                // point to any rotation of the input vector
                continue;
            }
            else if (nums[i] <= i)
            {
                ++intervals[std::make_pair(0, i-nums[i])];
                if (i < n-1) ++intervals[std::make_pair(i+1, n-1)];
            }
            else
            {
                ++intervals[std::make_pair(i+1, n+i-nums[i])];
            }
        }
        
        using SetKey = std::map<Interval, int>::iterator;
        auto endComp = [] (const SetKey& l, const SetKey& r) {
            return l->first.second == r->first.second ?
                l->first.first < r->first.first :
                l->first.second < r->first.second;
        };
        std::set<SetKey, decltype(endComp)> activeIntervals(endComp);
        
        int active = 0;
        int maxActive = 0;
        int maxActiveStart = 0;
        auto it = intervals.begin();
        while (it != intervals.end())
        {
            int intervalStart = it->first.first;
            while (!activeIntervals.empty() && (*activeIntervals.begin())->first.second < intervalStart)
            {
                active -= (*activeIntervals.begin())->second;
                activeIntervals.erase(activeIntervals.begin());
            }
            while (it != intervals.end() && it->first.first == intervalStart)
            {
                active += it->second;
                activeIntervals.insert(it);
                ++it;
                if (active > maxActive)
                {
                    maxActive = active;
                    maxActiveStart = intervalStart;
                }
            }
        }
        return maxActiveStart;
    }
};
