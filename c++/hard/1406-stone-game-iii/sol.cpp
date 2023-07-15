// https://leetcode.com/problems/stone-game-iii/

#include <array>
#include <limits>

class Solution {
public:
    string stoneGameIII(vector<int>& values) {
        const int n = values.size();
        int postfix = values[n - 1];
        std::array<int, 3> dp{ values[n - 1], 0, 0 };
        for (int id = n - 2; id >= 0; --id) {
            postfix += values[id];
            int value = std::numeric_limits<int>::min();
            for (int offset = 0; offset < 3; ++offset) {
                const int candidate = postfix - dp[offset];
                if (candidate > value) value = candidate;
            }
            dp[2] = dp[1];
            dp[1] = dp[0];
            dp[0] = value;
        }
        
        const int alicePoints = dp[0];
        const int bobPoints = postfix - alicePoints;
        return alicePoints > bobPoints ? "Alice" : alicePoints < bobPoints ? "Bob" : "Tie";
    }
};
