// https://leetcode.com/problems/count-unique-characters-of-all-substrings-of-a-given-string/

#include <array>
#include <utility>

class Solution {
public:
    int uniqueLetterString(string s) {
        using prev_type = std::pair<std::string::const_iterator, std::string::const_iterator>;
        std::array<prev_type, 26> previousOccurances{};
        for (auto& prev : previousOccurances) prev = std::make_pair(s.cend(), s.cend());
        
        int cum = 0;
        int prev = 0;
        for (auto it = s.cbegin(); it != s.cend(); ++it)
        {
            int currId = it - s.cbegin();
            int prevId = previousOccurances[*it-'A'].first - s.cbegin();
            int beforePrevId = previousOccurances[*it-'A'].second - s.cbegin();
            int prevAdjustment = 0;
            if (prevId == s.size())
            {
                // First occurance of this character.
                // Appending to all substrs up to previous character
                // increase the score of each by 1
                prevAdjustment = currId;
            }
            else if (prevId != s.size() && beforePrevId == s.size())
            {
                // Previous occurance was the first occurance of this character.
                // When appended, this character no longer contributes in substrs
                // starting from the beginning up to prevId, and does contribute in
                // substrs starting after prevId
                prevAdjustment = currId - 2*prevId - 2;
            }
            else
            {
                // Multiple previous occurances of this character.
                // Adjust score down for contribution of this character from
                // substrs starting after beforePrevId up to prevId, and add
                // contribution from those starting after prevId
                prevAdjustment = currId - 2*prevId + beforePrevId - 1;
            }
            int curr = 1 + prev + prevAdjustment;
            cum += curr;
            prev = curr;
            previousOccurances[*it-'A'] = std::make_pair(it, previousOccurances[*it-'A'].first);
        }
        return cum;
    }
};
