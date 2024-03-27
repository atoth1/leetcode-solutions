// https://leetcode.com/problems/constrained-subsequence-sum/

#include <limits>
#include <queue>
#include <span>

class Solution {
public:
    static int constrainedSubsetSum(const std::span<const int> nums, const int k) {
        auto maxOf = [](const int x, const int y) { return x > y ? x : y; };
        std::priority_queue<Data> prev{};
        int max = std::numeric_limits<int>::min();
        for (int id = 0; id < nums.size(); ++id) {
            while (!prev.empty() && id - prev.top().id > k) prev.pop();
            const int thisMax = nums[id] + (prev.empty() ? 0 : prev.top().sum);
            max = maxOf(max, thisMax);
            if (thisMax > 0) prev.push({ id, thisMax });
        }
        return max;
    }
    
private:
    struct Data {
        int id;
        int sum;
        
        constexpr bool operator<(const Data other) const noexcept {
            return sum < other.sum;
        }
    };
};
