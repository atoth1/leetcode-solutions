// https://leetcode.com/problems/the-number-of-the-smallest-unoccupied-chair/

#include <algorithm>
#include <list>
#include <numeric>
#include <queue>

class Solution {
public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        std::vector<int> ids(times.size());
        std::iota(ids.begin(), ids.end(), 0);
        std::sort(ids.begin(), ids.end(), [&](const int l, const int r) {
            return times[l][0] < times[r][0];
        });
        
        auto comp = [] (const OccupiedSeat l, const OccupiedSeat r) {
            return l.exitTime > r.exitTime;
        };
        std::priority_queue<OccupiedSeat, std::vector<OccupiedSeat>, decltype(comp)> occupied(comp);
        
        std::set<Interval> occupiedIntervals{};
        for (const auto id : ids) {
            auto nextArivee = times[id];
            
            // Clear out people leaving
            while (!occupied.empty() && occupied.top().exitTime <= nextArivee[0]) {
                auto leaving = occupied.top();
                occupied.pop();
                static constexpr int FAKE_END = 1000000;
                auto it = occupiedIntervals.upper_bound(Interval{leaving.pos, FAKE_END});
                --it;
                auto interval = *it;
                occupiedIntervals.erase(it);
                if (interval.start != interval.end) {
                    if (interval.start == leaving.pos) {
                        occupiedIntervals.insert(Interval{leaving.pos + 1, interval.end});
                    } else if (interval.end == leaving.pos) {
                        occupiedIntervals.insert(Interval{interval.start, leaving.pos - 1});
                    } else {
                        occupiedIntervals.insert(Interval{interval.start, leaving.pos - 1});
                        occupiedIntervals.insert(Interval{leaving.pos + 1, interval.end});
                    }
                }
            }
            
            // Seat the next person
            int pos = -1;
            int end = -1;
            if (occupiedIntervals.empty() || occupiedIntervals.begin()->start > 1) {
                pos = 0;
                end = 0;
            } else if (occupiedIntervals.begin()->start == 1) {
                pos = 0;
                end = occupiedIntervals.begin()->end;
                occupiedIntervals.erase(occupiedIntervals.begin());
            } else {
                pos = occupiedIntervals.begin()->end + 1;
                end = pos;
                occupiedIntervals.erase(occupiedIntervals.begin());
                if (!occupiedIntervals.empty() && end == occupiedIntervals.begin()->start - 1) {
                    end = occupiedIntervals.begin()->end;
                    occupiedIntervals.erase(occupiedIntervals.begin());
                }
            }
            if (id == targetFriend) return pos;
            occupiedIntervals.insert(Interval{0, end});
            occupied.push(OccupiedSeat{nextArivee[1], pos});
        }
        return -1;
    }
    
private:
    struct OccupiedSeat {
        int exitTime;
        int pos;
    };
    
    struct Interval {
        int start;
        int end;
        
        bool operator<(const Interval& other) const {
            return start == other.start ? end < other.end : start < other.start;
        }
    };
};
