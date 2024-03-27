// https://leetcode.com/problems/count-different-palindromic-subsequences/

#include <string_view>
#include <unordered_map>

namespace {
    struct Bounds {
        int begin;
        int end;
        
        constexpr bool operator==(const Bounds& other) const noexcept = default;
    };
    
    struct BoundsHash {
        constexpr std::size_t operator()(const Bounds bounds) const noexcept {
            constexpr int COEF = 1009;
            return bounds.begin + COEF * bounds.end;
        } 
    };
    
    using cache_t = std::unordered_map<Bounds, int, BoundsHash>;
    
    constexpr int modPlus(const int x, const int y) {
        constexpr int MOD = 1000000007;
        return (x + y) % MOD;
    }
    
    static constexpr std::string_view charSet{ "abcd" };
    
    int impl(const std::string_view s, const Bounds bounds, cache_t& cache) {
        if (bounds.begin > bounds.end) {
            return 0;
        } else if (bounds.begin == bounds.end) {
            return 1;
        } else if (auto it = cache.find(bounds); it != cache.end()) {
            return it->second;
        } else {
            int count = 1;
            for (const char c : charSet) {
                int first = bounds.begin;
                while (first < bounds.end && s[first] != c) ++first;
                if (first == bounds.end) continue;
                count = modPlus(count, 1);
                
                int last = bounds.end - 1;
                while (s[last] != c) --last;
                count = modPlus(count, impl(s, Bounds{ first + 1, last }, cache));
                
            }
            cache[bounds] = count;
            return count;
        }
    }
}

class Solution {
public:
    static int countPalindromicSubsequences(const std::string_view s) {
        cache_t cache{};
        return impl(s, Bounds{ 0, static_cast<int>(s.size()) }, cache) - 1;
    }
};
