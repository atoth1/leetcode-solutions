// https://leetcode.com/problems/number-of-flowers-in-full-bloom/

#include <algorithm>
#include <limits>
#include <memory>
#include <vector>

namespace {
struct Interval {
    int begin;
    int end;
    
    int length() const noexcept {
        return end - begin;
    }
    
    int mid() const noexcept {
        return begin + length() / 2;
    }
};

class Node {
public:
    Node(const Interval inBounds) : bounds(inBounds) { }
    
    void insert(const Interval interval) {
        if (interval.end <= bounds.mid()) {
            if (!left) left = std::make_unique<Node>(Interval{ bounds.begin, bounds.mid() });
            left->insert(interval);
        } else if (interval.begin > bounds.mid()) {
            if (!right) right = std::make_unique<Node>(Interval{ bounds.mid() + 1, bounds.end });
            right->insert(interval);
        } else {
            beginPts.push_back(interval.begin);
            endPts.push_back(interval.end);
        }
    }
    
    void completeInsertions() {
        std::sort(beginPts.begin(), beginPts.end());
        std::sort(endPts.begin(), endPts.end());
        if (left) left->completeInsertions();
        if (right) right->completeInsertions();
    }
    
    int query(const int pt) const noexcept {
        if (pt < bounds.mid()) {
            const int count = std::upper_bound(beginPts.begin(), beginPts.end(), pt) - beginPts.begin();
            return count + (left ? left->query(pt) : 0);
        } else if (pt > bounds.mid()) {
            const int count = std::upper_bound(endPts.begin(), endPts.end(), pt) - endPts.begin();
            return endPts.size() - count + (right ? right->query(pt) : 0);
        } else {
            return beginPts.size();
        }
    }
    
private:
    Interval bounds;
    std::unique_ptr<Node> left{};
    std::unique_ptr<Node> right{};
    std::vector<int> beginPts{};
    std::vector<int> endPts{};
};

class IntervalTree {
public:
    IntervalTree(const std::vector<std::vector<int>>& intervals) {
        int begin = std::numeric_limits<int>::max();
        int end = std::numeric_limits<int>::min();
        for (const auto& interval : intervals) {
            begin = std::min(begin, interval[0]);
            end = std::max(end, interval[1]);
        }
        bounds = Interval{ begin, end + 1 };
        root = std::make_unique<Node>(bounds);
        
        for (const auto& interval : intervals) {
            root->insert(Interval{ interval[0], interval[1] + 1 });
        }
        root->completeInsertions();
    }
    
    int query(const int value) const noexcept {
        return value < bounds.begin || value >= bounds.end ? 0 : root->query(value);
    }
    
private:
    Interval bounds;
    std::unique_ptr<Node> root;
};
    
}

class Solution {
public:
    static std::vector<int> fullBloomFlowers(
        const std::vector<std::vector<int>>& flowers,
        const std::vector<int>& persons
    ) {
        const auto tree = IntervalTree(flowers);
        std::vector<int> ret{};
        ret.reserve(persons.size());
        for (const int value : persons) ret.push_back(tree.query(value));
        return ret;
    }
};
