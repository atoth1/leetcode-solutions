// https://leetcode.com/problems/my-calendar-iii/

#include <iterator>
#include <map>
#include <utility>

class MyCalendarThree {
public:
    MyCalendarThree() {
    }
    
    int book(int start, int end) {
        auto ub = intervalToCount.upper_bound(std::make_pair(start, start));
        auto lb = std::prev(ub);
        
        // Take care of intersection with lower bounding interval
        if (start < lb->first.second) {
            if (start == lb->first.first) {
                if (end < lb->first.second) {
                    int tmp1 = lb->first.second;
                    int tmp2 = lb->second;
                    intervalToCount.erase(lb);
                    intervalToCount[std::make_pair(start, end)] = tmp2+1;
                    intervalToCount[std::make_pair(end, tmp1)] = tmp2;
                    if (tmp2+1 > max) max = tmp2+1;
                    return max;
                } else {
                    ++(lb->second);
                    if (lb->second > max) max = lb->second;
                    if (end == lb->first.second) return max;
                    start = lb->first.second;
                }
            } else {
                if (end < lb->first.second) {
                    int tmp1 = lb->first.first;
                    int tmp2 = lb->first.second;
                    int tmp3 = lb->second;
                    intervalToCount.erase(lb);
                    intervalToCount[std::make_pair(tmp1, start)] = tmp3;
                    intervalToCount[std::make_pair(start, end)] = tmp3+1;
                    intervalToCount[std::make_pair(end, tmp2)] = tmp3;
                    if (tmp3+1 > max) max = tmp3+1;
                    return max;
                } else {
                    int tmp1 = lb->first.first;
                    int tmp2 = lb->first.second;
                    int tmp3 = lb->second;
                    intervalToCount.erase(lb);
                    intervalToCount[std::make_pair(tmp1, start)] = tmp3;
                    intervalToCount[std::make_pair(start, tmp2)] = tmp3+1;
                    if (tmp3+1 > max) max = tmp3+1;
                    if (end == tmp2) return max;
                    start = tmp2;
                }
            }
        }
        
        // Take care of remainder
        if (end <= ub->first.first) {
            intervalToCount[std::make_pair(start, end)] = 1;
            if (max == 0) max = 1;
        } else {
            while (start < end) {
                if (start < ub->first.first) {
                    int smaller = end < ub->first.first ? end : ub->first.first;
                    intervalToCount[std::make_pair(start, smaller)] = 1;
                    if (max == 0) max = 1;
                    if (end <= ub->first.first) return max;
                    start = ub->first.first;
                }
                
                if (end < ub->first.second) {
                    int tmp1 = ub->first.second;
                    int tmp2 = ub->second;
                    intervalToCount.erase(ub);
                    intervalToCount[std::make_pair(start, end)] = tmp2+1;
                    intervalToCount[std::make_pair(end, tmp1)] = tmp2;
                    if (tmp2+1 > max) max = tmp2+1;
                    return max;
                } else {
                    ++(ub->second);
                    if (ub->second > max) max = ub->second;
                    if (end == ub->first.second) return max;
                    start = ub->first.second;
                }
                ++ub;
            }
        }
        return max;
    }

private:
    using Interval = std::pair<int, int>;
    
    struct IntervalComp {
        constexpr bool operator()(const Interval& l, const Interval& r) const {
            return l.first < r.first;
        }
    };
    
    static constexpr int INVALID_LEFT = -1;
    static constexpr int INVALID_RIGHT = 1000000001;
    // Initialize map with unreachable proxy values (all insertion will
    // fall between these with no intersection).
    std::map<Interval, int, IntervalComp> intervalToCount{
        std::make_pair(std::make_pair(INVALID_LEFT, INVALID_LEFT), 0),
        std::make_pair(std::make_pair(INVALID_RIGHT, INVALID_RIGHT), 0)};
    int max{0};
};

/**
 * Your MyCalendarThree object will be instantiated and called as such:
 * MyCalendarThree* obj = new MyCalendarThree();
 * int param_1 = obj->book(start,end);
 */
