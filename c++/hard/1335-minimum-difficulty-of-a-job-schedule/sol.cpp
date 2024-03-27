// https://leetcode.com/problems/minimum-difficulty-of-a-job-schedule/

#include <functional>
#include <limits>
#include <span>
#include <unordered_map>

namespace {
    struct State {
        int beginId;
        int groups;
        
        constexpr bool operator<=>(const State&) const noexcept = default;
    };
}

namespace std {
    template <>
    struct hash<State> {
        constexpr std::size_t operator()(const State state) const noexcept {
            return 31 * state.beginId + state.groups;
        }
    };
}

namespace {
    int impl(const std::span<const int> nums, const State state, std::unordered_map<State, int>& cache) {
        static constexpr int INVALID = -1;
        
        const auto [beginId, groups] = state;
        const int elemCount = nums.size() - beginId;
        if (elemCount == 0 && groups == 0) {
            return 0;
        } else if (groups < 1 || elemCount < groups) {
            return INVALID;
        } else if (const auto it = cache.find(state); it != cache.end()) {
            return it->second;
        } else {
            auto maxOf = [](const int x, const int y) { return x > y ? x : y; };
            auto minOf = [](const int x, const int y) { return x < y ? x : y; };
            int ret = std::numeric_limits<int>::max();
            int firstGroupMax = -1;
            for (int firstGroupSize = 1; firstGroupSize <= elemCount; ++firstGroupSize) {
                firstGroupMax = maxOf(firstGroupMax, nums[beginId + firstGroupSize - 1]);
                const int remaining = impl(nums, State{ beginId + firstGroupSize, groups - 1 }, cache);
                if (remaining != INVALID) {
                    ret = minOf(ret, firstGroupMax + remaining);
                }
            }
            cache[state] = ret;
            return ret;
        }
    }
}

class Solution {
public:
    int minDifficulty(const std::span<const int> nums, const int d) {
        std::unordered_map<State, int> cache{};
        return impl(nums, State{ 0, d }, cache);
    }
};