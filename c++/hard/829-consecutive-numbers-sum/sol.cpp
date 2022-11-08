// https://leetcode.com/problems/consecutive-numbers-sum/

#include <cmath>
#include <cstdlib>

class Solution {
public:
    int consecutiveNumbersSum(int n) {
        int total = 1;
        static const double sqrt2 = std::sqrt(2.);
        int termsBound = sqrt2*std::sqrt(static_cast<double>(n));
        for (int numTerms = 2; numTerms <= termsBound; ++numTerms)
        {
            // Bound on numTerms probably takes care of possibility of
            // consecutive int sequence beginnining at a negative, but
            // best not chance it
            if (numTerms & 1)
            {
                auto divmod = std::div(n, numTerms);
                if (divmod.rem == 0 && (divmod.quot - numTerms/2) > 0)
                {
                    ++total;
                }
            }
            else
            {
                auto divmod = std::div(n + numTerms/2, numTerms);
                if (divmod.rem == 0 && (divmod.quot - numTerms/2) > 0)
                {
                    ++total;
                }
            }
        }
        return total;
    }
};