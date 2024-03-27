// https://leetcode.com/problems/maximum-score-of-a-good-subarray/

#include <iterator>
#include <span>

class Solution {
public:
    static int maximumScore(const std::span<const int> nums, const int k) {
        auto maxOf = [](const int x, const int y) { return x > y ? x : y; };
        auto minOf = [](const int x, const int y) { return x < y ? x : y; };
        auto left = std::next(nums.begin(), k);
        auto right = left;
        int max = *left;
        int minValue = *left;
        while (left != nums.begin() || right != std::prev(nums.end())) {
            if (left == nums.begin()) {
                ++right;
                minValue = minOf(minValue, *right);
            } else if (right == std::prev(nums.end())) {
                --left;
                minValue = minOf(minValue, *left);
            } else if (*std::prev(left) >= minValue) {
                --left;
            } else if (*std::next(right) >= minValue) {
                ++right;
            } else if (*std::prev(left) > *std::next(right)) {
                --left;
                minValue = *left;
            } else {
                ++right;
                minValue = *right;
            }
            max = maxOf(max, minValue * (std::distance(left, right) + 1));
        }
        return max;
    }
};
