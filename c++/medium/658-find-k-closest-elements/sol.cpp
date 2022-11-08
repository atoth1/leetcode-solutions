// https://leetcode.com/problems/find-k-closest-elements/

#include <algorithm>

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        if (k == arr.size()) return arr;
        
        auto rit = std::lower_bound(arr.cbegin(), arr.cend(), x);
        if (rit == arr.cbegin())
        {
            return std::vector<int>(arr.cbegin(), arr.cbegin()+k);
        }
        else if (rit == arr.cend())
        {
            return std::vector<int>(arr.cend()-k, arr.cend());
        }
        else
        {
            auto lit = rit-1;
            while (rit - lit < k+1)
            {
                if(*rit - x < x - *lit)
                {
                    ++rit;
                    if (rit == arr.cend())
                    {
                        return std::vector<int>(arr.cend()-k, arr.cend());
                    }
                }
                else
                {
                    if (lit == arr.cbegin())
                    {
                        return std::vector<int>(arr.cbegin(), arr.cbegin()+k);
                    }
                    --lit;
                }
            }
            return std::vector<int>(lit+1, rit);
        }
    }
};
