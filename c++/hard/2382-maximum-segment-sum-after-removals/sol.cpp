// https://leetcode.com/problems/maximum-segment-sum-after-removals/


#include <functional>
#include <map>
#include <set>
#include <vector>

class Solution {
public:
    std::vector<long long> maximumSegmentSum(
        const std::vector<int>& nums,
        const std::vector<int>& removeQueries
    ) {
        std::vector<long long> prefixSums(nums.size() + 1);
        for (int id = 1; id < prefixSums.size(); ++id) prefixSums[id] = prefixSums[id - 1] + nums[id - 1];
        std::map<long long, int, std::greater<long long>> sumCounts{ { prefixSums.back(), 1 } };
        std::set<Interval> intervals{ { 0, static_cast<int>(nums.size()) } };
        
        auto removeIndex = [&](const int id) {
            const auto it = intervals.lower_bound({ id, id });
            const Interval containingInterval = *it;
            const long long intervalSum =
                prefixSums[containingInterval.end] - prefixSums[containingInterval.begin];
            intervals.erase(it);
            --sumCounts[intervalSum];
            if (sumCounts[intervalSum] == 0) sumCounts.erase(intervalSum);
            if (containingInterval.size() > 1) {
                if (id != containingInterval.begin) {
                    intervals.insert({ containingInterval.begin, id });
                    ++sumCounts[prefixSums[id] - prefixSums[containingInterval.begin]];
                }
                if (id + 1 != containingInterval.end) {
                    intervals.insert({ id + 1, containingInterval.end });
                    ++sumCounts[prefixSums[containingInterval.end] - prefixSums[id + 1]];
                }
            }
        };
        
        std::vector<long long> ret{};
        for (const int queryId : removeQueries) {
            removeIndex(queryId);
            ret.push_back(sumCounts.begin()->first);
        }
        return ret;
    }
    
private:
    struct Interval {
        int begin{};
        int end{};
        
        constexpr int size() const noexcept { return end - begin; }
        
        constexpr bool operator<(const Interval other) const noexcept {
            return end < other.end;
        }
    };
};