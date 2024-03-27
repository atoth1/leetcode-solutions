// https://leetcode.com/problems/find-a-value-of-a-mysterious-function-closest-to-target/

#include <limits>
#include <memory>
#include <utility>
#include <vector>

namespace {
    class Node;
    
    using NodePtr = std::unique_ptr<Node>;
    
    struct Interval {
        int begin_{};
        int end_{};
        
        constexpr bool operator==(const Interval other) const noexcept {
            return begin_ == other.begin_ && end_ == other.end_;
        }
    };
    
    class Node {
    public:
        Node(const std::vector<int>& arr, const Interval interval)
            : interval_{ interval }
            , mid_{ interval_.begin_ + (interval.end_ - interval.begin_) / 2 }
        {
            if (interval_.end_ - interval_.begin_ == 1) {
                val_ = arr[interval_.begin_];
            } else {
                left_ = std::make_unique<Node>(arr, Interval{ interval_.begin_, mid_ });
                right_ = std::make_unique<Node>(arr, Interval{ mid_, interval_.end_ });
                val_ = left_->val() & right_->val();
            }
        }
        
        int val() const {
            return val_;
        }
        
        int query(const Interval interval) const {
            if (interval == interval_) {
                return val_;
            } else if (interval.end_ <= mid_) {
                return left_->query(interval);
            } else if (interval.begin_ >= mid_) {
                return right_->query(interval);
            } else {
                return left_->query({ interval.begin_, mid_ }) & right_->query({ mid_, interval.end_ });
            }
        }
        
    private:
        NodePtr left_{ nullptr };
        NodePtr right_{ nullptr };
        int val_;
        Interval interval_;
        int mid_;
    };
    
    class SegmentTree {
    public:
        SegmentTree(const std::vector<int>& arr)
            : size_{ static_cast<int>(arr.size()) }
            , root_{ std::make_unique<Node>(arr, Interval{ 0, size_ }) }
        { }
        
        int query(const Interval interval) const {
            // Probably check that query interval is contained within root_'s interval
            return root_->query(interval);
        }
        
        int size() const {
            return size_;
        }
        
    private:
        int size_;
        NodePtr root_;
    };
    
    std::pair<int, int> binarySearch(const SegmentTree& lookup, const int begin, const int target) {
        int l = begin + 1;
        int lValue = lookup.query({ begin, l });
        int r = lookup.size();
        int rValue = lookup.query({ begin, r });
        if (rValue >= target) {
            return { rValue, -1000000000 };
        }
        
        while (l + 1 != r) {
            const int m = l + (r - l) / 2;
            const int mValue = lookup.query({ begin, m });
            if (mValue >= target) {
                l = m;
                lValue = mValue;
            } else {
                r = m;
                rValue = mValue;
            }
        }
        return { lValue, rValue };
    }
}

class Solution {
public:
    int closestToTarget(const std::vector<int>& arr, int target) {
        SegmentTree lookup(arr);
        auto minOf = [](const int x, const int y) { return x < y ? x : y; };
        int min = std::numeric_limits<int>::max();
        for (int begin = 0; begin < arr.size(); ++begin) {
            if (arr[begin] < target) {
                min = minOf(min, target - arr[begin]);
            } else {
                const auto [greater, smaller] = binarySearch(lookup, begin, target);
                min = minOf(min, greater - target);
                min = minOf(min, target - smaller);
            }
        }
        return min;
    }
};