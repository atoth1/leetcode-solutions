// https://leetcode.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/

#include <queue>
#include <vector>

class Solution {
public:
    int minTaps(const int n, const std::vector<int>& ranges) {
        queue_t queue{};
        for (int id = 0; id < ranges.size(); ++id) queue.push(Interval{ id - ranges[id], id + ranges[id] });
        
        auto maxOf = [](const auto& l, const auto& r) { return l > r ? l : r; };
        int begin = 0;
        int count = 0;
        while (!queue.empty()) {
            ++count;
            int end = begin;
            while (!queue.empty() && queue.top().begin <= begin) {
                end = maxOf(end, queue.top().end);
                queue.pop();
                if (end >= n) return count;
            }
            
            if (end == begin) {
                return -1;
            } else {
                begin = end;
            }
        }
        return -1;
    }
    
private:
    struct Interval {
        int begin{};
        int end{};
    };
    
    struct IntervalComp {
        constexpr bool operator()(const Interval l, const Interval r) const noexcept {
            return l.begin > r.begin;
        }
    };
    
    using queue_t = std::priority_queue<Interval, std::vector<Interval>, IntervalComp>;
};
