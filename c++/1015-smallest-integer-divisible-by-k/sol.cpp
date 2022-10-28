// https://leetcode.com/problems/smallest-integer-divisible-by-k/

class Solution {
public:
    int smallestRepunitDivByK(int k) {
        std::vector<bool> seen(k, false);
        int a = 1 % k;
        seen[a] = true;
        int n = 1;
        while (a != 0) {
            ++n;
            a = (10 * a + 1) % k;
            if (seen[a]) return -1;
            seen[a] = true;
        }
        return n;
    }
};
