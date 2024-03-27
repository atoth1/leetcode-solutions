// https://leetcode.com/problems/count-of-integers/

#include <algorithm>
#include <string>
#include <string_view>
#include <unordered_map>

namespace {   

struct State {
    std::string_view num;
    int l;
    int r;
    
    constexpr bool operator==(const State&) const noexcept = default;
};

struct StateHash {
    std::size_t operator()(const State x) const noexcept {
        constexpr int FACTOR = 31;
        std::size_t hash = std::hash<std::string_view>{}(x.num);
        hash = FACTOR * hash + x.l;
        hash = FACTOR * hash + x.r;
        return hash;
    }
};

using cache_t = std::unordered_map<State, int, StateHash>;

constexpr int MOD = 1000000007;

constexpr int modAdd(const int x, const int y) {
    return (x + y) % MOD;
}

constexpr int modSubtract(const int x, const int y) {
    int ret = x - y;
    return ret < 0 ? ret + MOD : ret;
}

// length 22 since largest number considered is 10^22
static constexpr std::string_view NINES = "9999999999999999999999";

int impl(const State state, cache_t& cache) {
    if (const auto it = cache.find(state); it != cache.end()) {
        return it->second;
    }
    
    if (state.num.empty()) {
        return state.l == 0;
    } else {
        const int leadingDigit = state.num[0] - '0';
        std::string_view reducedNum = state.num.substr(1);
        while (!reducedNum.empty() && reducedNum[0] == '0') reducedNum.remove_prefix(1);
        State newState{ reducedNum, std::max({ 0, state.l - leadingDigit }), state.r - leadingDigit };
        int ret = newState.r >= 0 ? impl(newState, cache) : 0;
        
        const std::string_view nines = NINES.substr(0, state.num.size() - 1);
        for (int digit = 0; digit < leadingDigit; ++digit) {
            if (state.r < digit) break;
            newState = { nines, std::max({ 0, state.l - digit }), state.r - digit };
            ret = modAdd(ret, impl(newState, cache));
        }
        
        cache[state] = ret;
        return ret;
    }
}

}

class Solution {
public:
    static int count(const std::string& num1, const std::string& num2, const int minSum, const int maxSum) {
        auto decrNumStr = [](std::string str) {
            if (str.back() > '0') {
                --str.back();
            } else {
                std::reverse(str.begin(), str.end());
                --str[0];
                int pos = 0;
                while (pos < str.size() && str[pos] < '0') {
                    str[pos++] = '9';
                    --str[pos];
                }
                if (str.back() == '0') str.pop_back();
                std::reverse(str.begin(), str.end());
            }
            return str;
        };
        const auto num1Decr = decrNumStr(num1);
        
        State state1{ static_cast<std::string_view>(num1Decr), minSum, maxSum };
        State state2{ static_cast<std::string_view>(num2), minSum, maxSum };
        cache_t cache{};
        return modSubtract(impl(state2, cache), impl(state1, cache));
    }
};
