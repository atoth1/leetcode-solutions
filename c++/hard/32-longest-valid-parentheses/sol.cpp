// https://leetcode.com/problems/longest-valid-parentheses/

class Solution {
public:
    int longestValidParentheses(string s) {
        bool  passChangedString = true;
        while (passChangedString)
        {
            // I'm assuming we could do something to reduce search boundries
            // but who cares.
            passChangedString = false;
            for (auto it = s.begin(); it != s.end(); ++it)
            {
                // Change () characters surrounding a valid (possibly empty)
                // substring to X's
                if (*it == '(')
                {
                    auto tmp = it;
                    ++tmp;
                    while (tmp != s.end() && *tmp == 'X')
                    {
                        ++tmp;
                    }
                    if (tmp != s.end() && *tmp == ')')
                    {
                        passChangedString = true;
                        *it = 'X';
                        *tmp = 'X';
                    }
                    it = tmp-1;
                }
            }
        }
        
        // Subsequences of X's now represent valid substrings, find longest
        int maxCount = 0;
        for (auto it = s.cbegin(); it != s.cend(); ++it)
        {
            if (*it == 'X')
            {
                ++it;
                int count = 1;
                while(it != s.cend() && *it == 'X')
                {
                    ++it;
                    ++count;
                }
                if (count > maxCount) maxCount = count;
                if (it == s.cend()) break;
            }
        }
        return maxCount;
    }
};
