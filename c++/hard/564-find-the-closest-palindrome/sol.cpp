// https://leetcode.com/problems/find-the-closest-palindrome/

#include <utility>

class Solution {
public:
    string nearestPalindromic(string n) {
        int nDigits = n.size();
        if (nDigits == 1)
        {
            --n.front();
            return n;
        }
        
        auto isPow10 = [] (const std::string& s)
        {
            return s.front() == '1' && s.find_first_not_of('0', 1) == std::string::npos;
        };
        // 9...99 -> 10...01
        if (n.find_first_not_of('9') == std::string::npos)
        {
            std::string ret(nDigits+1, '0');
            ret.front() = '1';
            ret.back() = '1';
            return ret;
        }
        // 10...0 -> 9...9
        if (isPow10(n)) return std::string(nDigits-1, '9');
        // 10...01 -> 9...99
        n.back() -= 1;
        if (isPow10(n)) return std::string(nDigits-1, '9');
        n.back() += 1;
        
        long nLong = std::stol(n);
        std::string lower(nDigits, '0');
        lower.front() = '1';
        lower.back() = '1';
        long lowerLong = std::stol(lower);
        std::string upper(nDigits, '9');
        long upperLong = std::stol(upper);
        for (int i = 0; i < (nDigits+1)/2; ++i)
        {
            std::string delta(nDigits, '0');
            delta[i] = '1';
            delta[nDigits-1-i] = '1';
            long deltaLong = std::stol(delta);
            int k = 0;
            while (lowerLong + deltaLong <= nLong)
            {
                lowerLong += deltaLong;
                ++k;
                if (lowerLong == nLong)
                {
                    lower = std::to_string(lowerLong);
                    if (nDigits & 1)
                    {
                        lowerLong = std::stol(lower.substr(0, (nDigits+1)/2));
                    }
                    else
                    {
                        lowerLong = std::stol(lower.substr(0, nDigits/2));
                    }
                    upperLong = lowerLong+1;
                    std::string upperTmp = std::to_string(upperLong);
                    --lowerLong;
                    std::string lowerTmp = std::to_string(lowerLong);
                    for (int j = 0; j < lowerTmp.size(); ++j)
                    {
                        lower[j] = lowerTmp[j];
                        lower[lower.size()-1-j] = lowerTmp[j];
                        upper[j] = upperTmp[j];
                        upper[upper.size()-1-j] = upperTmp[j];
                    }
                    return nLong - std::stol(lower) <= std::stol(upper) - nLong ?
                        lower : upper;
                }
            }
            if (k < 9)
            {
                upperLong = lowerLong + deltaLong;
            }
        }
        return nLong - lowerLong <= upperLong - nLong ?
            std::to_string(lowerLong) : std::to_string(upperLong);
    }
};
