// https://leetcode.com/problems/closest-divisors/

#include <algorithm>
#include <cmath>

class Solution {
public:
    vector<int> closestDivisors(int num) {
        auto closestDivisorsFor = [] (const int n) {
            int bound = std::sqrt(n);
            auto curr = std::make_pair(1, n);
            for (int smaller = 2; smaller <= bound; ++smaller) {
                int larger = n/smaller;
                if (n - smaller * larger == 0) {
                    curr = std::make_pair(smaller, larger);
                }
            }
            return curr;
        };
        
        // Do we know for sure np1 and np2 can't have equidistant closest factors?
        auto np1 = closestDivisorsFor(num+1);
        auto np2 = closestDivisorsFor(num+2);
        return np1.second - np1.first < np2.second - np2.first ?
            std::vector<int>{ np1.first, np1.second } : std::vector<int>{ np2.first, np2.second };
    }
};
