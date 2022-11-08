// https://leetcode.com/problems/student-attendance-record-ii/

#include <tuple>
#include <unordered_map>

class Solution {
public:
    int checkRecord(int n) {
        populateCache(n);
        
        int total = numNoAbsence(n);
        for (int i = 1; i <= n/2; ++i)
        {
            // Absent day i (x2 for symmetry and n/2 bound)
            total += (2 * static_cast<long>(numNoAbsence(i-1)) * numNoAbsence(n-i)) % ansMod;
            total = total % ansMod;
        }
        if (n & 1)
        {
            // Absent midpoint day for odd n
            long tmp = numNoAbsence(n/2);
            total += (tmp * tmp) % ansMod;
            total = total % ansMod;
        }
        return total;
    }
    
private:
    int numNoAbsence(int n)
    {
        if (n == 0)
        {
            return 1;
        }
        else
        {
            const auto& counts = cache[n];
            return (std::get<0>(counts) +
                    (std::get<1>(counts) + std::get<2>(counts)) % ansMod) % ansMod;
        }
    }
    
    void populateCache(int n)
    {
        // Cache values # key-length strings ending with P, exactly one L,
        // and exactly 2 L's respectively
        if (cache.size() < n)
        {
            if (cache.empty())
            {
                cache[1] = std::make_tuple(1, 1, 0);
            }
            for (int k = cache.size() + 1; k <= n; ++k)
            {
                const auto& km1 = cache[k-1];
                int endingP = std::get<0>(km1) + (std::get<1>(km1) + std::get<2>(km1)) % ansMod;
                int endingL = std::get<0>(km1);
                int endingLL = std::get<1>(km1);
                cache[k] = std::make_tuple(endingP % ansMod, endingL, endingLL);
            }
        }
    }
    
    static constexpr int ansMod = 1000000007;
    static std::unordered_map<int, std::tuple<int, int, int>> cache;
};
std::unordered_map<int, std::tuple<int, int, int>> Solution::cache;
