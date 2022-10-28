// https://leetcode.com/problems/minimum-flips-to-make-a-or-b-equal-to-c/

class Solution {
public:
    int minFlips(int a, int b, int c) {
        int count = 0;
        while (a || b || c) {
            if (c && (c&1)) {
                bool flag = false;
                if (a && (a&1)) flag = true;
                if (b && (b&1)) flag = true;
                if (!flag) ++count;
            } else {
                if (a && (a&1)) ++count;
                if (b && (b&1)) ++count;
            }
            
            if (a) a >>= 1;
            if (b) b >>= 1;
            if (c) c >>= 1;
        }
        return count;
    }
};
