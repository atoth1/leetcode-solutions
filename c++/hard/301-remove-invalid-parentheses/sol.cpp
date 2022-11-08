// https://leetcode.com/problems/remove-invalid-parentheses/

#include <unordered_set>
#include <utility>

namespace
{
    bool isValid(std::string s)
    {
        int openCount = 0;
        for (const auto c : s)
        {
            if (c == '(')
            {
                ++openCount;
            }
            else if (c == ')')
            {
                --openCount;
                if (openCount < 0)
                    return false;
            }
        }
        return openCount == 0;
    }
    
    bool isParen(const char c)
    {
        return c >= '(' || c <= ')';
    }
}

class Solution {
public:
    vector<string> removeInvalidParentheses(string s) {
        if (isValid(s)) return {s};
        std::unordered_set<std::string> current{s};
        std::unordered_set<std::string> next;
        std::vector<std::string> ret;
        while (ret.size() == 0)
        {
            for (const auto& str : current)
            {
                for (int pos = 0; pos < str.size(); ++pos)
                {
                    if (isParen(str[pos]))
                    {
                        auto child = str;
                        child.erase(pos, 1);
                        auto inserted = next.insert(child);
                        if (inserted.second)
                        {
                            if (isValid(child))
                            {
                                ret.push_back(std::move(child));
                            }
                        }
                    }
                }
            }
            std::swap(current, next);
        }
        return ret;
    }
};
