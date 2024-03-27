// https://leetcode.com/problems/find-xor-sum-of-all-pairs-bitwise-and/

#include <array>
#include <span>

class Solution {
public:
    static int getXORSum(const std::span<const int> arr1, const std::span<const int> arr2) {
        static constexpr int INT_SIZE = 32;
        auto getSetBitCounts = [](const std::span<const int> arr) {
            std::array<int, INT_SIZE> counts{};
            for (const int num : arr) {
                for (int bit = 0; bit < INT_SIZE; ++bit) {
                    const bool bitIsSet = num & (1 << bit);
                    if (bitIsSet) {
                        ++counts[bit];
                    }
                }
            }
            return counts;
        };
        
        const auto bits1 = getSetBitCounts(arr1);
        const auto bits2 = getSetBitCounts(arr2);
        int ret = 0;
        for (int bit = 0; bit < INT_SIZE; ++bit) {
            if ((bits1[bit] & 1) && (bits2[bit] & 1)) {
                ret |= 1 << bit;
            }
        }
        return ret;
    }
};
