// https://leetcode.com/problems/minimum-impossible-or/

#include <array>
#include <optional>
#include <vector>

class Solution {
public:
    int minImpossibleOR(const std::vector<int>& nums) {
        static constexpr int N_EXPONENTS = 31;
        std::array<bool, N_EXPONENTS> powerOfTwoExists{};
        for (const int n : nums) {
            if (auto bitId = getSingleSetBitId(n); bitId) {
                powerOfTwoExists[*bitId] = true;
            }
        }
        
        for (int exponent = 0; exponent < N_EXPONENTS; ++exponent) {
            if (!powerOfTwoExists[exponent]) {
                return 1 << exponent;
            }
        }
        return -1;
    }
    
private:
    static std::optional<int> getSingleSetBitId(int n) {
        std::optional<int> setId{};
        int bitId = -1;
        while (n) {
            ++bitId;
            if (n & 1)  {
                if (setId) {
                    return {};
                } else {
                    setId = bitId;
                }
            }
            n >>= 1;
        }
        return setId;
    }
};