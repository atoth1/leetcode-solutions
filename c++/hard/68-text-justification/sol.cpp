// https://leetcode.com/problems/text-justification/

#include <algorithm>
#include <cstdlib>
#include <sstream>

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        std::string spaces(maxWidth, ' ');
        if (words.size() == 1)
        {
            std::copy(words.front().begin(), words.front().end(), spaces.begin());
            return { spaces };
        }
        
        auto lineStart = words.begin();
        std::vector<std::string> ret;
        while(lineStart != words.end())
        {
            auto lineEnd = lineStart + 1;
            int lineSum = (*lineStart).size();
            while (lineEnd != words.end())
            {
                lineSum += (*lineEnd).size() + 1; // +1 for at least one space
                if (lineSum > maxWidth)
                {
                    lineSum -= (*lineEnd).size() + 1;
                    break;
                }
                ++lineEnd;
            }
            
            std::stringstream s;
            if ((lineEnd == words.end()) || (lineEnd - lineStart == 1))
            {
                s << *lineStart++;
                while (lineStart != lineEnd)
                {
                    s << ' ' << *lineStart++;
                }
                s << spaces.substr(0, maxWidth-lineSum);
            }
            else
            {
                auto extraSpaces = std::div(maxWidth - lineSum,
                    static_cast<int>(lineEnd - lineStart) - 1);
                s << *lineStart++;
                while (lineStart != lineEnd)
                {
                    s << spaces.substr(0, 1 + extraSpaces.quot);
                    if (extraSpaces.rem > 0)
                    {
                        s << ' ';
                        --extraSpaces.rem;
                    }
                    s << *lineStart++;
                }
            }
            ret.push_back(s.str());
        }
        return ret;
    }
};
