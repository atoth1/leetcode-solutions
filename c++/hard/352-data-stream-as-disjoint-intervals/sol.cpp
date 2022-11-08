// https://leetcode.com/problems/data-stream-as-disjoint-intervals/

#include <set>
#include <utility>

class SummaryRanges
{
public:
    SummaryRanges() = default;
    
    void addNum(int val)
    {
        if (intervals_.empty())
        {
            cachedIntervals_ = { {val, val} };
            intervals_.insert(std::make_pair(val, val));
            return;
        }
        
        auto begin = intervals_.begin();
        auto end = intervals_.end();
        --end;
        if (val < begin->first)
        {
            cachedIntervalsValid_ = false;
            if (val == begin->first - 1)
            {
                auto update = std::make_pair(val, begin->second);
                intervals_.erase(begin);
                intervals_.insert(update);
            }
            else
            {
                intervals_.insert(std::make_pair(val, val));
            }
        }
        else if (val > end->second)
        {
            cachedIntervalsValid_ = false;
            if (val == end->second+1)
            {
                auto update = std::make_pair(end->first, val);
                intervals_.erase(end);
                intervals_.insert(update);
            }
            else
            {
                intervals_.insert(std::make_pair(val, val));
            }
        }
        else
        {
            auto update = std::make_pair(val, val);
            auto rit = intervals_.upper_bound(update);
            auto lit = rit;
            --lit;
            if (val == lit->second+1 && val == rit->first-1)
            {
                cachedIntervalsValid_ = false;
                auto actualUpdate = std::make_pair(lit->first, rit->second);
                intervals_.erase(lit);
                intervals_.erase(rit);
                intervals_.insert(actualUpdate);
            }
            else if (val == lit->second+1)
            {
                cachedIntervalsValid_ = false;
                auto actualUpdate = std::make_pair(lit->first, val);
                intervals_.erase(lit);
                intervals_.insert(actualUpdate);
            }
            else if (val == rit->first-1)
            {
                cachedIntervalsValid_ = false;
                auto actualUpdate = std::make_pair(val, rit->second);
                intervals_.erase(rit);
                intervals_.insert(actualUpdate);
            }
            else if (val > lit->second+1 && val < rit->first-1)
            {
                cachedIntervalsValid_ = false;
                intervals_.insert(update);
            }
        }
    }
    
    vector<vector<int>> getIntervals()
    {
        if (!cachedIntervalsValid_)
        {
            cachedIntervals_.clear();
            for (const auto& interval : intervals_)
            {
                cachedIntervals_.push_back( {interval.first, interval.second} );
            }
        }
        return cachedIntervals_;
    }
private:
    std::set<std::pair<int, int>> intervals_;
    std::vector<std::vector<int>> cachedIntervals_ = {};
    bool cachedIntervalsValid_ = true;
};

/**
 * Your SummaryRanges object will be instantiated and called as such:
 * SummaryRanges* obj = new SummaryRanges();
 * obj->addNum(val);
 * vector<vector<int>> param_2 = obj->getIntervals();
 */
