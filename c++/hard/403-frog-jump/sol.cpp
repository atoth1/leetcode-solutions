// https://leetcode.com/problems/frog-jump/

#include <algorithm>
#include <unordered_map>
#include <vector>

class Solution {
public:
    static bool canCross(const std::vector<int>& stones) {
        cache_t cache(0, StateHash{ stones.cbegin() });
        return impl(stones, State{ stones.cbegin(), 0 }, cache);
    }
    
private:
    struct State {
        std::vector<int>::const_iterator pos;
        int prevJump;
    };
    
    struct StateEqual {
        bool operator()(const State l, const State r) const noexcept {
            return l.pos == r.pos && l.prevJump == r.prevJump;
        }
    };
    
    struct StateHash {
        std::vector<int>::const_iterator begin;
        
        std::size_t operator()(const State x) const noexcept {
            static constexpr int MAX_POS = 2000;
            return (x.pos - begin) + MAX_POS * x.prevJump;
        }
    };
    
    using cache_t = std::unordered_map<State, bool, StateHash, StateEqual>;
    
    static bool impl(const std::vector<int>& stones, const State state, cache_t& cache) {
        if (state.pos == stones.cend() - 1) {
            return true;
        } else if (auto it = cache.find(state); it != cache.end()) {
            return it->second;
        } else {
            auto tryJump = [&](const int jump) {
                if (jump <= 0) return false;
                
                const auto pos = std::lower_bound(state.pos, stones.cend(), *(state.pos) + jump);
                if (pos != stones.cend() && *pos == *(state.pos) + jump) {
                    return impl(stones, State{ pos, jump }, cache);
                } else {
                    return false;
                }
            };
            const bool ret1 = tryJump(state.prevJump - 1);
            const bool ret2 = tryJump(state.prevJump);
            const bool ret3 = tryJump(state.prevJump + 1);
            const bool ret = ret1 || ret2 || ret3;
            cache[state] = ret;
            return ret;
        }
    }
};
