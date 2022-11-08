// https://leetcode.com/problems/stickers-to-spell-word/

#include <algorithm>
#include <array>
#include <map>

class Solution {
public:
    int minStickers(vector<string>& stickers, string target) {
        auto charCounts = [] (const std::string& str, const std::array<int, 26>* bound = nullptr) {
            std::array<int, 26> count{};
            for (const auto c : str)
            {
                if (!bound || count[c - 'a'] < (*bound)[c - 'a'])
                {
                    ++count[c - 'a'];
                }
            }
            return count;
        };
        auto targetCount = charCounts(target);
        std::vector<std::array<int, 26>> counts(stickers.size());
        for (int i = 0; i < counts.size(); ++i)
        {
            counts[i] = charCounts(stickers[i], &targetCount);
        }
        
        auto checkFeasible = [&] () {
            for (int i = 0; i < 26; ++i)
            {
                if (targetCount[i] > 0)
                {
                    bool foundChar = false;
                    for (const auto& count : counts)
                    {
                        if (count[i] > 0)
                        {
                            foundChar = true;
                            break;
                        }
                    }
                    if (!foundChar) return false;
                }
            }
            return true;
        };
        if (!checkFeasible()) return -1;
        
        std::map<std::array<int, 26>, int> contribCounts;
        for (const auto& count : counts)
        {
            contribCounts[count] = std::accumulate(count.cbegin(), count.cend(), 0);
        }
        std::sort(counts.begin(), counts.end(), [&contribCounts] (const auto& l, const auto& r) {
            return contribCounts[l] > contribCounts[r];
        });
        auto begin = counts.begin();
        auto end = counts.end();
        while (begin != end)
        {
            end = std::remove_if(begin+1, end, [&begin] (const auto& count) {
                for (int i = 0; i < 26; ++i)
                {
                    if (count[i] > (*begin)[i]) return false;
                }
                return true;
            });
            ++begin;
        }
        counts.erase(end, counts.end());
            
        int minCount = 15; // max length of target
        searchMin(counts, targetCount, 0, 0, minCount);
        return minCount;
    }
    
private:
    void searchMin(const std::vector<std::array<int, 26>>& counts,
                   std::array<int, 26>& remainingTarget,
                   int idx,
                   int count,
                   int& minCount)
    {
        auto targetFound = [] (const auto& target) {
            for (int i = 0; i < 26; ++i)
            {
                if (target[i] > 0) return false;
            }
            return true;
        };
        auto hasContrib = [] (const auto& candidate, const auto& target) {
            for (int i = 0; i < 26; ++i)
            {
                if (target[i] > 0 && candidate[i] > 0) return true;
            }
            return false;
        };
        
        if (idx < counts.size())
        {
            if (targetFound(remainingTarget))
            {
                if (count < minCount) minCount = count;
            }
            else
            {
                if (hasContrib(counts[idx], remainingTarget))
                {
                    for (int i = 0; i < 26; ++i) remainingTarget[i] -= counts[idx][i];
                    searchMin(counts, remainingTarget, idx, count+1, minCount);
                    for (int i = 0; i < 26; ++i) remainingTarget[i] += counts[idx][i];
                }
                searchMin(counts, remainingTarget, idx+1, count, minCount);
            }
        }
    }
};
