// https://leetcode.com/problems/minimum-interval-to-include-each-query/

#include <algorithm>

namespace {
    struct IntervalRepr {
        int length{};
        int end{};
    };
    
    // Want min heap by interval length
    constexpr bool operator<(const IntervalRepr l, const IntervalRepr r) {
        return l.length > r.length;
    }
}

class Solution {
public:
    vector<int> minInterval(vector<vector<int>>& intervals, vector<int>& queries) {
        std::sort(intervals.begin(), intervals.end());
        
        std::vector<int> ids(queries.size());
        std::iota(ids.begin(), ids.end(), 0);
        std::sort(ids.begin(), ids.end(), [&](const int l, const int r) {
            return queries[l] < queries[r];
        });
        
        std::vector<int> ret(queries.size(), -1);
        std::vector<IntervalRepr> active{};
        auto pos = intervals.cbegin();
        for (const int id : ids) {
            const int query = queries[id];
            while (pos != intervals.cend() && (*pos)[0] <= query) {
                const auto& interval = *pos++;
                active.push_back(IntervalRepr{ interval[1] - interval[0] + 1, interval[1] });
                std::push_heap(active.begin(), active.end());
            }
            
            while (!active.empty() && active[0].end < query) {
                std::pop_heap(active.begin(), active.end());
                active.pop_back();
            }
            
            if (!active.empty()) {
                ret[id] = active[0].length;
            }
        }
        return ret;
    }
};