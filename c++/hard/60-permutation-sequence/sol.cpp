// https://leetcode.com/problems/permutation-sequence/

#include <array>
#include <cstdlib>
#include <utility>

namespace
{
    template <int N>
    struct Factorial
    {
        static_assert(N > 0);
        static constexpr int val = N * Factorial<N-1>::val;
    };

    template <>
    struct Factorial<0>
    {
        static constexpr int val = 1;
    };

    template <std::size_t... Is>
    constexpr std::array<int, sizeof...(Is)> initFactorials(std::index_sequence<Is...> )
    {
        return { Factorial<Is>::val... };
    }
    
    constexpr int maxN = 9;
    constexpr auto globalFactorials = initFactorials(std::make_index_sequence<maxN+1>());
}

class Solution {
public:
    string getPermutation(int n, int k) {
        if (n == 1) return "1";
        
        k = k-1;
        std::string ret(n, ' ');
        std::vector<bool> selected(n, false);
        for (int i = 0; i < n; ++i)
        {
            auto r = std::div(k, globalFactorials[n-1-i]);
            k = r.rem;
            int count = 0;
            int j = 0;
            for (; j < n; ++j)
            {
                count = selected[j] ? count : count+1;
                if (count == r.quot+1)
                    break;
            }
            selected[j] = true;
            ret[i] = j + '1';
        }
        
        return ret;
    }
};
