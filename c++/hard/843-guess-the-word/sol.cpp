// https://leetcode.com/problems/guess-the-word/

#include <array>
#include <limits>
#include <map>
#include <utility>

/**
 * // This is the Master's API interface.
 * // You should not implement it, or speculate about its implementation
 * class Master {
 *   public:
 *     int guess(string word);
 * };
 */
class Solution {
public:
    void findSecretWord(vector<string>& wordlist, Master& master) {
        static constexpr int maxGuesses = 10;
        if (wordlist.size() <= maxGuesses)
        {
            for (const auto& word : wordlist)
            {
                master.guess(word);
            }
            return;
        }
        
        auto computeObjective = [] (const std::string& l, const std::string& r) {
            int objective = 0;
            for (int pos = 0; pos < l.size(); ++pos)
            {
                if (l[pos] == r[pos]) ++objective;
            }
            return objective;
        };
        
        std::map<std::pair<std::string, std::string>, int> objectiveValues;
        for (const auto& word1 : wordlist)
        {
            for (const auto& word2 : wordlist)
            {
                objectiveValues[std::make_pair(word1, word2)] = computeObjective(word1, word2);
            }
        }
        
        auto selectCandidate = [&objectiveValues] (const std::vector<std::string>& candidates) {
            const double target = (candidates.size()-1)/6.;
            double min = std::numeric_limits<double>::max();
            auto ret = candidates.cbegin();
            for (auto candidate = candidates.cbegin(); candidate != candidates.cend(); ++candidate)
            {
                std::array<int, 6> tally{};
                for (const auto& other : candidates)
                {
                    if (other == *candidate) continue;
                    ++tally[objectiveValues[std::make_pair(other, *candidate)]];
                    
                }
                double sum = 0.;
                for (const auto val : tally) sum += (val-target)*(val-target);
                if (sum < min)
                {
                    ret = candidate;
                    min = sum;
                }
            }
            return ret;
        };
        
        std::vector<std::string> curr(wordlist);
        std::vector<std::string> next{};
        for (int guess = 1; guess <= maxGuesses; ++guess)
        {
            const auto candidate = selectCandidate(curr);
            int objective = master.guess(*candidate);
            if (objective == candidate->size()) break;
            
            // Only need to continue to consider words in curr that give the
            // same objective value as the secret word
            for (auto it = curr.cbegin(); it != curr.cend(); ++it)
            {
                if (it == candidate) continue;
                if (objectiveValues[std::make_pair(*it, *candidate)] == objective)
                {
                    // Don't care about move, short-string optimization in play
                    next.push_back(*it);
                }
            }
            // Oh no, too bad if found it but numGuesses == maxGuesses
            if (guess < maxGuesses && next.size() == 1) master.guess(next[0]);
            std::swap(curr, next);
            next.clear();
        }
    }
};
