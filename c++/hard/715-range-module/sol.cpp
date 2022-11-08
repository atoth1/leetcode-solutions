// https://leetcode.com/problems/range-module/

#include <utility>

class RangeModule {
public:
    using Interval = std::pair<int, int>;
    
    RangeModule() {
        // Initialize with sentinel intervals outside possible range
        static constexpr int invalidLeft = 0;
        static constexpr int invalidRight = 1000000001;
        intervals_.push_back(std::make_pair(invalidLeft, invalidLeft));
        intervals_.push_back(std::make_pair(invalidRight, invalidRight));
    }
    
    void addRange(int left, int right) {
        auto lBounds = find(left);
        auto rBounds = find(right);
        if (lBounds.second)
        {
            // Possibly extend interval containing left to the right
            intervals_[lBounds.first].second = rBounds.second ?
                intervals_[rBounds.first].second : right;
            
            // Erase any swallowed intervals
            intervals_.erase(intervals_.begin() + lBounds.first + 1,
                             intervals_.begin() + rBounds.first + 1);
        }
        else if (!rBounds.second && (lBounds.first == rBounds.first))
        {
            // left and right are in same gap between two intervals, simply
            // insert new interval in appropriate place
            intervals_.insert(intervals_.begin() + lBounds.first + 1,
                              std::make_pair(left, right));
        }
        else
        {
            // Extend first interval greater than left to include left
            intervals_[lBounds.first+1].first = left;
            
            // Possibly extend interval now containing left to the right
            intervals_[lBounds.first+1].second = rBounds.second ?
                intervals_[rBounds.first].second : right;
            
            // Erase any swallowed intervals
             intervals_.erase(intervals_.begin() + lBounds.first + 2,
                              intervals_.begin() + rBounds.first + 1);
        }
    }
    
    bool queryRange(int left, int right) {
        auto lBounds = find(left);
        auto rBounds = find(right);
        return (lBounds.first == rBounds.first) && lBounds.second && rBounds.second;
    }
    
    void removeRange(int left, int right) {
        addRange(left, right);
        auto interval = find(left);
        if (intervals_[interval.first].first == left
            && intervals_[interval.first].second == right)
        {
            intervals_.erase(intervals_.begin() + interval.first,
                             intervals_.begin() + interval.first + 1);
        }
        else if (intervals_[interval.first].first == left)
        {
            intervals_[interval.first].first = right;
        }
        else if (intervals_[interval.first].second == right)
        {
            intervals_[interval.first].second = left;
        }
        else
        {
            int tmp = intervals_[interval.first].first;
            intervals_[interval.first].first = right;
            intervals_.insert(intervals_.begin() + interval.first,
                              std::make_pair(tmp, left));
            
        }
    }
    
private:
    std::pair<int, bool> find(int val)
    {
        // Return value gives index of containing interval and true if val is
        // contained within an interval, and returns index of lower bounding
        // interval and false if val falls between two. Guaranteed to be one
        // or the other due to sentinel intervals created in constructor.
        int l = 0;
        int r = intervals_.size()-1;
        while (l+1 != r)
        {
            int m = l + (r-l)/2;
            if (intervals_[m].first > val)
            {
                r = m;
            }
            else if (intervals_[m].second < val)
            {
                l = m;
            }
            else
            {
                return std::make_pair(m, true);
            }
        }
        return std::make_pair(l, false);
    }
    
    std::vector<Interval> intervals_;
};

/**
 * Your RangeModule object will be instantiated and called as such:
 * RangeModule* obj = new RangeModule();
 * obj->addRange(left,right);
 * bool param_2 = obj->queryRange(left,right);
 * obj->removeRange(left,right);
 */
