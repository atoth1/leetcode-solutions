// https://leetcode.com/problems/24-game/

#include <cmath>

class Solution {
public:
    bool judgePoint24(vector<int>& cards) {
        double a = cards[0];
        double b = cards[1];
        double c = cards[2];
        double d = cards[3];
        
        // Adding 2 numbers
        if (try3Numbers(a+b, c, d))
        {
            return true;
        }
        else if (try3Numbers(a+c, b, d))
        {
            return true;
        }
        else if (try3Numbers(a+d, b, c))
        {
            return true;
        }
        else if (try3Numbers(b+c, a, d))
        {
            return true;
        }
        else if (try3Numbers(b+d, a, c))
        {
            return true;
        }
        else if (try3Numbers(c+d, a, b))
        {
            return true;
        }
        // Multiplying 2 numbers
        else if (try3Numbers(a*b, c, d))
        {
            return true;
        }
        else if (try3Numbers(a*c, b, d))
        {
            return true;
        }
        else if (try3Numbers(a*d, b, c))
        {
            return true;
        }
        else if (try3Numbers(b*c, a, d))
        {
            return true;
        }
        else if (try3Numbers(b*d, a, c))
        {
            return true;
        }
        else if (try3Numbers(c*d, a, b))
        {
            return true;
        }
        // Subtracting 2 numbers
        else if (try3Numbers(a-b, c, d))
        {
            return true;
        }
        else if (try3Numbers(a-c, b, d))
        {
            return true;
        }
        else if (try3Numbers(a-d, b, c))
        {
            return true;
        }
        else if (try3Numbers(b-a, c, d))
        {
            return true;
        }
        else if (try3Numbers(b-c, a, d))
        {
            return true;
        }
        else if (try3Numbers(b-d, a, c))
        {
            return true;
        }
        else if (try3Numbers(c-a, b, d))
        {
            return true;
        }
        else if (try3Numbers(c-b, a, d))
        {
            return true;
        }
        else if (try3Numbers(c-d, a, b))
        {
            return true;
        }
        else if (try3Numbers(d-a, b, c))
        {
            return true;
        }
        else if (try3Numbers(d-b, a, c))
        {
            return true;
        }
        else if (try3Numbers(d-c, a, b))
        {
            return true;
        }
        // Dividing 2 numbers
        else if (try3Numbers(a/b, c, d))
        {
            return true;
        }
        else if (try3Numbers(a/c, b, d))
        {
            return true;
        }
        else if (try3Numbers(a/d, b, c))
        {
            return true;
        }
        else if (try3Numbers(b/a, c, d))
        {
            return true;
        }
        else if (try3Numbers(b/c, a, d))
        {
            return true;
        }
        else if (try3Numbers(b/d, a, c))
        {
            return true;
        }
        else if (try3Numbers(c/a, b, d))
        {
            return true;
        }
        else if (try3Numbers(c/b, a, d))
        {
            return true;
        }
        else if (try3Numbers(c/d, a, b))
        {
            return true;
        }
        else if (try3Numbers(d/a, b, c))
        {
            return true;
        }
        else if (try3Numbers(d/b, a, c))
        {
            return true;
        }
        else if (try3Numbers(d/c, a, b))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
private:
    bool try3Numbers(double a, double b, double c)
    {
        // Add
        if (try2Numbers(a+b, c))
        {
            return true;
        }
        else if (try2Numbers(a+c, b))
        {
            return true;
        }
        else if (try2Numbers(b+c, a))
        {
            return true;
        }
        // Multiply
        else if (try2Numbers(a*b, c))
        {
            return true;
        }
        else if (try2Numbers(a*c, b))
        {
            return true;
        }
        else if (try2Numbers(b*c, a))
        {
            return true;
        }
        // Subtract
        else if (try2Numbers(a-b, c))
        {
            return true;
        }
        else if (try2Numbers(a-c, b))
        {
            return true;
        }
        else if (try2Numbers(b-a, c))
        {
            return true;
        }
        else if (try2Numbers(b-c, a))
        {
            return true;
        }
        else if (try2Numbers(c-a, b))
        {
            return true;
        }
        else if (try2Numbers(c-b, a))
        {
            return true;
        }
        // Divide
        else if (try2Numbers(a/b, c))
        {
            return true;
        }
        else if (try2Numbers(a/c, b))
        {
            return true;
        }
        else if (try2Numbers(b/a, c))
        {
            return true;
        }
        else if (try2Numbers(b/c, a))
        {
            return true;
        }
        else if (try2Numbers(c/a, b))
        {
            return true;
        }
        else if (try2Numbers(c/b, a))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    bool try2Numbers(double a, double b)
    {
        constexpr double eps = 1.0e-10;
        constexpr double target = 24.;
        return std::abs(a + b - target) < eps || std::abs(a * b - target) < eps ||
            std::abs(a - b - target) < eps || std::abs(b - a - target) < eps ||
            std::abs(a/b - target) < eps || std::abs(b/a - target) < eps;
    }
};
