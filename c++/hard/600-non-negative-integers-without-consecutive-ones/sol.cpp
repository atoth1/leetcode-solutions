// https://leetcode.com/problems/non-negative-integers-without-consecutive-ones/

#include <utility>

namespace
{
    // Represnts number of valid ints with greatest set bit I (1-based indexing)
    // I = 0 -> 1 (0...0000)
    // I = 1 -> 1 (0...0001)
    // I = 2 -> 1 (0...0010)
    // I = 3 -> 2 (0...0100, 0...0101)
    // For I >= 2 Fibish<I>::val = sum(K = 0, 1, .., I-2) Fibish<K>::val
    // (can make a valid number with greatest bit I by setting bit I for any valid
    // number with greatest set bit less than I except I-1). Computing this sequence out
    // for a few terms gives 1, 1, 1, 2, 3, 5, 8, 13, 21, ... . Sorta weird Fibonacci...
    template <int I>
    struct Fibish
    {
        enum { val = Fibish<I-1>::val + Fibish<I-2>::val };
    };
    
    template<>
    struct Fibish<2>
    {
        enum { val = 1 };
    };
    
    template<>
    struct Fibish<1>
    {
        enum { val = 1 };
    };
    
    template<>
    struct Fibish<0>
    {
        enum { val = 1 };
    };
    
    template <int... Is>
    constexpr std::array<int, sizeof...(Is)> initVals(std::integer_sequence<int, Is...>)
    {
        return { Fibish<Is>::val... };
    }
    static constexpr auto greatestSetBitToCount = initVals(std::make_integer_sequence<int, 34>());
}

class Solution {
public:
    int findIntegers(int n) {
        if (n == 0) return 1;
        int greatestSetBit = 32;
        unsigned int mask = 1;
        while ((n & (mask << (greatestSetBit-1))) == 0)
        {
            --greatestSetBit;
        }
        
        // Number of valid ints with greatest set bit < greatestSetBit for n
        int count = greatestSetBitToCount[greatestSetBit+1];
        
        // Add number of valid ints <= n with greatest set bit = greatestSetBit
        if (n == 1 || (n & (mask << (greatestSetBit-2))) == 0 )
        {
            n -= (mask << (greatestSetBit-1));
            count += findIntegers(n);
        }
        else
        {
            count += findIntegers((mask << (greatestSetBit-2))-1);
        }
        
        return count;
    }
};
