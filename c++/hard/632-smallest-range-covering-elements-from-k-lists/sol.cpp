// https://leetcode.com/problems/smallest-range-covering-elements-from-k-lists/

#include <iterator>
#include <set>
#include <vector>

class Solution {
public:
    std::vector<int> smallestRange(const std::vector<std::vector<int>>& nums) {
        set_t vals{};
        for (const auto& vec : nums) vals.insert({ vec.begin(), vec.end() });
        
        InclusiveInterval ret = getCandidate(vals);
        while (std::next(vals.begin()->first) != vals.begin()->second) {
            const auto next = std::make_pair(std::next(vals.begin()->first), vals.begin()->second);
            vals.erase(vals.begin());
            vals.insert(next);
            
            const InclusiveInterval candidate = getCandidate(vals);
            if (candidate.len() < ret.len()) {
                ret = candidate;
            }
        }
        return { ret.first, ret.last };
    }
    
private:
    using iter_t = std::vector<int>::const_iterator;
    using value_t = std::pair<iter_t, iter_t>;
    struct Comp {
        bool operator()(const value_t l, const value_t r) const noexcept {
            return *l.first < *r.first;
        }
    };
    using set_t = std::multiset<value_t, Comp>;
    
    struct InclusiveInterval {
        int first;
        int last;
        
        constexpr int len() const noexcept { return last - first + 1; }
    };
    
    InclusiveInterval getCandidate(const set_t& vals) {
        return { *vals.begin()->first, *std::prev(vals.end())->first };
    }
};
