// https://leetcode.com/problems/numbers-at-most-n-given-digit-set/

class Solution {
public:
    int atMostNGivenDigitSet(const vector<string>& whyNotInts, int n) {
        std::vector<int> digits{};
        for (const auto str : whyNotInts) {
            digits.push_back(str[0] - '0');
        }
        return impl(digits, n, true);
    }
        
    
private:
    int impl(const std::vector<int>& digits, int n, bool includeShorter) {
        if (n == 0) return 0;
        
        int nDigitCount = std::log10(n) + 1;
        int sum = 0;
        if (includeShorter) {
            int prod = 1;
            for (int digit = 1; digit < nDigitCount; ++digit) {
                prod *= digits.size();
                sum += prod;
            }
        }
        
        int factor = std::pow(10, nDigitCount-1);
        int leadingDigit = n/factor;
        int nLessLeadingDigit = 0;
        while (nLessLeadingDigit < digits.size() && digits[nLessLeadingDigit] < leadingDigit) {
            ++nLessLeadingDigit;
        }
        sum += nLessLeadingDigit * std::pow(digits.size(), nDigitCount-1);
        
        if (nLessLeadingDigit < digits.size() && digits[nLessLeadingDigit] == leadingDigit) {
            n -= leadingDigit * factor;
            if (nDigitCount == 1) {
                sum += 1;
            } else if (n != 0 && static_cast<int>(std::log10(n)) == nDigitCount-2) {
                sum += impl(digits, n, false);
            }
        }
        return sum;
    }
};
