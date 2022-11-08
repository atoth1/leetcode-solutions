// https://leetcode.com/problems/minimum-garden-perimeter-to-collect-enough-apples/

#include <cmath>

class Solution {
public:
    long long minimumPerimeter(long long neededApples) {
        auto objective = [&] (const double k) {
            return 2*k*(k+1)*(2*k+1) - neededApples;
        };
        
        auto deriv = [] (const double k) {
            return 4*k*(k+1) + 2*k*(2*k+1) + 2*(k+1)*(2*k+1);
        };
        
        double k = std::pow(neededApples/4.0, 1/3.0);
        for (int repeat = 0; repeat < 5; ++repeat) {
            k -= objective(k)/deriv(k);
        }
        
        int tmp = static_cast<int>(k) - 1;
        while (objective(tmp) <  0) ++tmp;
        return 8*tmp;
    }
};
