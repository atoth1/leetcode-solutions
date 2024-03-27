// https://leetcode.com/problems/minimum-changes-to-make-k-semi-palindromes/

#include <array>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace {
    static constexpr int MAX_N = 200;
    
    auto makeDivisors() {
        std::array<std::vector<int>, MAX_N> divisors{};
        for (int n = 1; n <= MAX_N; ++n) {
            std::vector<int> nDivisors{};
            for (int candidate = 1; candidate < n; ++candidate) {
                if ((n % candidate) == 0) {
                    nDivisors.push_back(candidate);
                }
            }
            divisors[n - 1] = nDivisors;
        }
        return divisors;
    }
    
    const auto divisors = makeDivisors();
    
    struct State {
        int charCount;
        int groups;
        
        constexpr bool operator==(const State&) const noexcept = default;
    };
    
    struct StateHash {
        constexpr std::size_t operator()(const State state) const noexcept {
            return state.charCount + (MAX_N + 1) * state.groups;
        }
    };
    
    using cache_t = std::unordered_map<State, int, StateHash>;
    
    static constexpr int INVALID = 1000000;
    
    int impl(const State state, const std::vector<std::vector<int>>& costs, cache_t& cache) {
        const auto [charCount, groups] = state;
        if (charCount == 0 && groups == 0) {
            return 0;
        } else if (charCount <= 0 || groups <= 0) {
            return INVALID;
        } else if (auto it = cache.find(state); it != cache.end()) {
            return it->second;
        } else {
            int ret = INVALID;
            const int bound = charCount - 2 * (groups - 1);
            for (int lastGroupLen = 2; lastGroupLen <= bound; ++lastGroupLen) {
                const int candidate = costs[charCount - lastGroupLen][charCount - 1]
                    + impl(State{ charCount - lastGroupLen, groups - 1 }, costs, cache);
                ret = std::min(ret, candidate);
            }
            cache[state] = ret;
            return ret;
        }
    }
}

class Solution {
public:
    static int minimumChanges(const std::string_view s, const int k) {
        auto computeSemiPalindromeCosts = [&]() {
            std::vector costs(s.size(), std::vector(s.size(), INVALID));
            for (int firstId = 0; firstId < s.size(); ++firstId) {
                for (int secondId = firstId + 1; secondId < s.size(); ++secondId) {
                    const int len = secondId - firstId + 1;
                    int cost = INVALID;
                    for (const int stride : divisors[len - 1]) {
                        const int groups = len / stride;
                        int candidateCost = 0;
                        for (int offset = 0; offset < stride; ++offset) {
                            int lid = firstId + offset;
                            int rid = lid + (groups - 1) * stride;
                            while (lid < rid) {
                                if (s[lid] != s[rid]) {
                                    ++candidateCost;
                                }
                                lid += stride;
                                rid -= stride;
                            }
                        }
                        cost = std::min(cost, candidateCost);
                    }
                    costs[firstId][secondId] = cost;
                }
            }
            return costs;
        };
        
        const auto costs = computeSemiPalindromeCosts();
        cache_t cache{};
        return impl(State{ static_cast<int>(s.size()), k }, costs, cache);
    }
};
