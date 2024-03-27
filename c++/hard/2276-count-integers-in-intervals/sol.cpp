// https://leetcode.com/problems/count-integers-in-intervals/

#include <iterator>
#include <set>

class CountIntervals {
public:
    CountIntervals() {
        
    }
    
    void add(const int left, const int right) {
        auto minOf = [](const int x, const int y) { return x < y ? x : y; };
        auto maxOf = [](const int x, const int y) { return x > y ? x : y; };
        
        Interval interval{ left, right + 1 };
        auto it = intervals_.upper_bound(interval);
        if (it != intervals_.begin() && std::prev(it)->end >= interval.begin) {
            const auto prev = std::prev(it);
            count_ -= prev->size();
            interval.begin = minOf(interval.begin, prev->begin);
            interval.end = maxOf(interval.end, prev->end);
            intervals_.erase(prev);
        }
        
        while (it != intervals_.end() && it->end <= interval.end) {
            const auto next = std::next(it);
            count_ -= it->size();
            intervals_.erase(it);
            it = next;
        }
        
        if (it != intervals_.end() && it->begin <= interval.end) {
            count_ -= it->size();
            interval.end = maxOf(interval.end, it->end);
            intervals_.erase(it);
        }
        
        count_ += interval.size();
        intervals_.insert(interval);
    }
    
    int count() const noexcept {
        return count_;
    }
    
private:
    struct Interval {
        int begin;
        int end;
        
        constexpr int size() const noexcept {
            return end - begin;
        }
        
        constexpr bool operator<(const Interval other) const noexcept {
            return begin < other.begin;
        }
    };
    
    std::set<Interval> intervals_{};
    
    int count_{};
};

/**
 * Your CountIntervals object will be instantiated and called as such:
 * CountIntervals* obj = new CountIntervals();
 * obj->add(left,right);
 * int param_2 = obj->count();
 */
