// https://leetcode.com/problems/bag-of-tokens/

#include <algorithm>

class Solution {
public:
    int bagOfTokensScore(vector<int>& tokens, int power) {
        std::sort(tokens.begin(), tokens.end());
        
        int score = 0;
        int max = 0;
        int l = 0;
        int r = tokens.size() - 1;
        while (l <= r) {
            if (tokens[l] <= power) {
                power -= tokens[l++];
                ++score;
                if (score > max) max = score;
            } else if (score > 0) {
                --score;
                power += tokens[r--];
            } else {
                break;
            }
        }
        return max;
    }
};
