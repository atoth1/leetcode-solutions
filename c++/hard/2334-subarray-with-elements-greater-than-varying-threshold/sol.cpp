// https://leetcode.com/problems/subarray-with-elements-greater-than-varying-threshold/description/

#include <algorithm>
#include <iterator>
#include <set>

class Solution {
public:
    int validSubarraySize(vector<int>& nums, int threshold) {
        auto idAndValComp = [](const IndexAndValue l, const IndexAndValue r) {
            return l.val_ == r.val_ ? l.id_ > r.id_ : l.val_ < r.val_;
        };

        std::vector<IndexAndValue> heap;
        heap.reserve(nums.size());
        for (int id = 0; id < nums.size(); ++id) {
            heap.push_back(IndexAndValue{ id, nums[id] });
        }
        std::make_heap(heap.begin(), heap.end(), idAndValComp);

        auto intervalComp = [](const Interval l, const Interval r) {
            return l.end_ < r.end_;
        };

        std::set<Interval, decltype(intervalComp)> intervals(intervalComp);

        auto insertIndex = [&intervals](const int id) {
            Interval newInterval{ id, id+1 };
            auto greater = intervals.upper_bound(newInterval);
            if (!intervals.empty() && greater != intervals.begin() &&
                id == std::prev(greater)->end_
            ) {
                auto prev = std::prev(greater);
                newInterval.begin_ = prev->begin_;
                intervals.erase(prev);
            }
            if (greater != intervals.end() && id+1 == greater->begin_) {
                newInterval.end_ = greater->end_;
                intervals.erase(greater);
            }
            intervals.insert(newInterval);
            return newInterval.end_ - newInterval.begin_;
        };

        for (int len = 1; len <= nums.size(); ++len) {
            const auto thresh = static_cast<double>(threshold)/len;
            while (!heap.empty() && heap[0].val_ > thresh) {
                // insertIndex returns length of interval containing the index
                if (insertIndex(heap[0].id_) >= len) {
                    return len;
                }
                std::pop_heap(heap.begin(), heap.end(), idAndValComp);
                heap.pop_back();
            }
        }
        return -1;
    }

private:
    struct IndexAndValue {
        int id_;
        int val_;
    };

    struct Interval {
        int begin_;
        int end_; // Non-inclusive
    };
};
