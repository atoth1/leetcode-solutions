// https://leetcode.com/problems/find-beautiful-indices-in-the-given-array-ii/

#include <string_view>
#include <vector>

class Solution {
public:
    std::vector<int> beautifulIndices(
        const std::string_view s,
        const std::string_view a,
        const std::string_view b,
        const int k
    ) {
        auto getContainedSubstrStartIds = [&](const std::string_view substr) {
            RollableSubstringHash hash(s, substr.size());
            const int substrHash = substringHash(substr);
            
            std::vector<int> ids{};
            // Should actually check full stubstring equality if equal hashes,
            // but this would give quadratic performance in case of input like
            // s = "aa...a" and substr = "aa..a".
            // I'll take this condition as sufficient proof of eqality
            if (hash.getValue() == substrHash && s[0] == substr[0]) {
                ids.push_back(0);
            }
            
            for (int id = 1; id + substr.size() <= s.size(); ++id) {
                hash.roll();
                // See comment above
                if (hash.getValue() == substrHash && s[id] == substr[0]) {
                    ids.push_back(id);
                }
            }
            return ids;
        };
        const auto aIds = getContainedSubstrStartIds(a);
        const auto bIds = getContainedSubstrStartIds(b);
        
        std::vector<int> ret{};
        auto it = bIds.begin();
        for (const int id : aIds) {
            while (it != bIds.end() && *it < id - k) {
                ++it;
            }
            
            if (it != bIds.end() && *it <= id + k) {
                ret.push_back(id);
            }
        }
        return ret;
    }
    
private:
    // Chosen to be a prime p s.t. 26 * p doesn't overflow int
    static constexpr int mod = 80000023;
    
    static constexpr int shiftFactor = 26;
    
    using size_type = std::string_view::size_type;
    
    static int modPlus(const int x, const int y) {
        return (x + y) % mod;
    }
    
    static int modMinus(const int x, const int y) {
        return x >= y ? x - y : x - y + mod;
    }
    
    static int modTimes(const int x, const int y) {
        return (x * y) % mod;
    }
    
    static int modPow(const int base, const size_type pow) {
        int ret = 1;
        for (int repeat = 0; repeat < pow; ++repeat) {
            ret = modTimes(ret, base);
        }
        return ret;
    }
    
    static int substringHash(
        const std::string_view s,
        const size_type begin = 0,
        const size_type count = std::string_view::npos
    ) {
        int hash = 0;
        int factor = 1;
        const size_type bound = count == std::string_view::npos ? s.size() : begin + count;
        for (size_t id = begin; id < bound; ++id) {
            hash = modPlus(modTimes(hash, shiftFactor), s[id] - 'a');
            factor = modTimes(factor, shiftFactor);
        }
        return hash;
    }
    
    class RollableSubstringHash {
    public:
        RollableSubstringHash(const std::string_view s, const size_type count)
            : value(substringHash(s, 0, count))
            , removalFactor(modPow(shiftFactor, count - 1))
            , currBegin(s.begin())
            , currEnd(s.begin() + count)
            , end(s.end())
        {
                
        }
        
        void roll() {
            // Should probably indicate some way if can't roll
            if (currEnd != end) {
                value = modMinus(value, modTimes(removalFactor, *currBegin++ - 'a'));
                value = modPlus(modTimes(value, shiftFactor), *currEnd++ - 'a');
            }
        }
        
        int getValue() const noexcept {
            return value;
        }
        
    private:
        using iter_t = std::string_view::iterator;
        int value;
        int removalFactor;
        iter_t currBegin;
        iter_t currEnd;
        iter_t end;
    };
};
