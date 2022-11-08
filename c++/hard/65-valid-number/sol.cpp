// https://leetcode.com/problems/valid-number/

#include <string_view>

namespace
{
    bool onlyDigits(std::string_view s)
    {
        for (const auto c : s)
        {
            if (c < '0' || c > '9') return false;
        }
        return true;
    }
    
    bool isDecimal(std::string_view s)
    {
        if (s.empty()) return false;
        if (s.front() == '+' || s.front() == '-')
        {
            s.remove_prefix(1);
            if (s.empty()) return false;
        }
        
        auto it = s.begin();
        while (it != s.end() && *it != '.')
        {
            ++it;
        }
        if (it == s.end()) return false;
        
        int nPrefix = it - s.begin();
        int startPostfix = it+1-s.begin();
        int nPostfix = s.end()-it-1;
        if (nPrefix == 0 && nPostfix == 0) return false;
        return onlyDigits(s.substr(0, nPrefix)) &&
               onlyDigits(s.substr(startPostfix, nPostfix));
    }
    
    bool isInteger(std::string_view s)
    {
        if (s.empty()) return false;
        if (s.front() == '+' || s.front() == '-')
        {
            s.remove_prefix(1);
            if (s.empty()) return false;
        }
        return onlyDigits(s);
    }
}

class Solution {
public:
    bool isNumber(string s) {
        std::string_view s_view = s;
        auto it = s_view.begin();
        while (it != s_view.end() && *it != 'e' && *it != 'E')
        {
            ++it;
        }
        
        if (!isDecimal(s_view.substr(0, it - s_view.begin())) &&
            !isInteger(s_view.substr(0, it - s_view.begin())))
        {
            return false;
        }
        
        if (it != s_view.end())
        {
            return isInteger(s_view.substr(it+1-s_view.begin(), s_view.end()-it-1));
        }
        return true;
    }
};
