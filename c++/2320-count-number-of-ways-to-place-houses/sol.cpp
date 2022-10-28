// https://leetcode.com/problems/count-number-of-ways-to-place-houses/

class Solution {
public:
    int countHousePlacements(int n) {
        static constexpr int MODULUS = 1000000007;
        static constexpr int MAXN = 10000;
        static std::vector<int> numToHereWithHouse(MAXN);
        static std::vector<int> numToHereWithoutHouse(MAXN);
        static bool initialized = false;
        if (!initialized) {
            initialized = true;
            numToHereWithHouse[0] = 1;
            numToHereWithoutHouse[0] = 1;
            for (int pos = 1; pos < MAXN; ++pos) {
                numToHereWithHouse[pos] = numToHereWithoutHouse[pos-1];
                numToHereWithoutHouse[pos] = (numToHereWithHouse[pos-1]
                    + numToHereWithoutHouse[pos-1]) % MODULUS;
            }
        }
        long long total = static_cast<long long>(numToHereWithHouse[n-1]) * numToHereWithHouse[n-1];
        total %= MODULUS;
        total += static_cast<long long>(numToHereWithoutHouse[n-1]) * numToHereWithoutHouse[n-1];
        total %= MODULUS;
        total += static_cast<long long>(numToHereWithHouse[n-1]) * numToHereWithoutHouse[n-1];
        total %= MODULUS;
        total += static_cast<long long>(numToHereWithHouse[n-1]) * numToHereWithoutHouse[n-1];
        total %= MODULUS;
        return static_cast<int>(total);
    }
};
