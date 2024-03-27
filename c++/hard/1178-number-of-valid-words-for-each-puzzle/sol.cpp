// https://leetcode.com/problems/number-of-valid-words-for-each-puzzle/

#include <bit>
#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

class Solution {
public:
    static std::vector<int> findNumOfValidWords(
        const std::vector<std::string>& words,
        const std::vector<std::string>& puzzles
    ) {
        auto toMask = [](const std::string& str) {
            std::uint32_t mask{};
            for (const char c : str) {
                const int offset = c - 'a';
                mask |= 1 << offset;
            }
            return mask;
        };
        
        static constexpr int PUZZLE_LENGTH = 7;
        std::unordered_map<std::uint32_t, int> wordMaskCounts{};
        for (const auto& word : words) {
            const std::uint32_t mask = toMask(word);
            if (std::popcount(mask) <= PUZZLE_LENGTH) {
                ++wordMaskCounts[mask];
            }
        }
        
        auto getValidMaskSet = [](const std::string& str) {
            std::unordered_set masks{ static_cast<std::uint32_t>(1 << (str[0] - 'a')) };
            for (int charId = 1; charId < str.size(); ++charId) {
                std::unordered_set<std::uint32_t> next{};
                const int offset = str[charId] - 'a';
                for (const std::uint32_t mask : masks) {
                    next.insert(mask);
                    next.insert(mask | (1 << offset));
                }
                std::swap(masks, next);
            }
            return masks;
        };
        
        std::vector<int> counts{};
        counts.reserve(puzzles.size());
        for (const auto& puzzle : puzzles) {
            int count = 0;
            for (const auto mask : getValidMaskSet(puzzle)) {
                if (const auto it = wordMaskCounts.find(mask); it != wordMaskCounts.end()) {
                    count += it->second;
                }
            }
            counts.push_back(count);
        }
        return counts;
    }
};
