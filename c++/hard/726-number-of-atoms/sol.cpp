// https://leetcode.com/problems/number-of-atoms/

#include <map>
#include <sstream>
#include <utility>

class Solution {
public:
    string countOfAtoms(string formula) {
        auto result = countOfAtomsImpl(formula, formula.cbegin());
        std::stringstream ret;
        for (const auto& elem : result.first)
        {
            ret << elem.first;
            if (elem.second != 1) ret << elem.second;
        }
        return ret.str();
    }
    
private:
    std::pair<std::map<std::string, int>, std::string::const_iterator>
    countOfAtomsImpl(const std::string& formula, std::string::const_iterator pos)
    {
        auto parseElement = [] (const std::string& formula, std::string::const_iterator& it) {
            // Would normally check that the first char is capital
            auto start = it++;
            while (*it >='a' && *it <= 'z')
            {
                ++it;
            }
            return std::string(start, it);
        };
        
        auto parseCount = [] (const std::string& formula, std::string::const_iterator& it) {
            // Assuming no leading 0's for count strings
            if (it == formula.cend() || *it < '1' || *it > '9')
            {
                return 1;
            }
            else
            {
                int count = 0;
                while (it != formula.cend() && *it >= '0' && *it <= '9')
                {
                    count = 10*count + *it - '0';
                    ++it;
                }
                return count;
            }
        };
        
        std::map<std::string, int> counts;
        while (pos != formula.cend() && *pos != ')')
        {
            if (*pos == '(')
            {
                auto nested = countOfAtomsImpl(formula, pos+1);
                pos = nested.second;
                auto count = parseCount(formula, pos);
                for (const auto& elem : nested.first)
                {
                    counts[elem.first] += count * elem.second;
                }
            }
            else
            {
                auto elem = parseElement(formula, pos);
                auto count = parseCount(formula, pos);
                counts[elem] += count;
            }
        }
        if (pos != formula.cend()) ++pos;
        return std::make_pair(counts, pos);
    }
};
