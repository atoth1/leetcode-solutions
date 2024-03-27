// https://leetcode.com/problems/count-vowels-permutation/

#include <array>
#include <numeric>
#include <utility>
#include <vector>

class Solution {
public:
    static int countVowelPermutation(const int n) {
        // Counts of strings ending with each character
        std::array counts{ 1, 1, 1, 1, 1 };
        
        auto modAdd = [](const int x, const int y) {
            static constexpr int MOD = 1000000007;
            return (x + y) % MOD;
        };
        
        const std::array idTransition{
            std::vector{ 1 }, std::vector{ 0, 2 }, std::vector{ 0, 1, 3, 4 }, std::vector{ 2, 4 }, std::vector{ 0 }
        };
        
        for (int i = 2; i <= n; ++i) {
            std::array<int, 5> nextCounts{};
            for (int id = 0; id < counts.size(); ++id) {
                for (const int nextId : idTransition[id]) {
                    nextCounts[nextId] = modAdd(nextCounts[nextId], counts[id]);
                }
            }
            std::swap(counts, nextCounts);
        }
        
        return std::accumulate(counts.cbegin(), counts.cend(), 0, modAdd);
    }
};
