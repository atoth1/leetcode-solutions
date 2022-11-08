// https://leetcode.com/problems/trapping-rain-water/

#include <list>

class Solution {
public:
    int trap(vector<int>& height) {
        if (height.size() == 1) return 0;
        
        std::list<int> local_max_ids;
        int i = 1;
        while (i < height.size())
        {
            if (height[i-1] > height[i])
            {
                local_max_ids.push_back(i-1);
                // Step past next local minimum
                ++i;
                while (i < height.size() && height[i-1] >= height[i])
                {
                    ++i;
                }
            }
            if (i == height.size()-1)
            {
                // Reached end in non-decreasing section, so this is local max
                local_max_ids.push_back(i);
            }
            ++i;
        }
        
        if (local_max_ids.size() == 1) return 0;
        
        auto lit = local_max_ids.begin();
        auto mit = lit;
        ++mit;
        auto rit = mit;
        ++rit;
        while (rit != local_max_ids.end())
        {
            if (height[*mit] <= height[*lit] && height[*mit] <= height[*rit])
            {
                local_max_ids.erase(mit);
                if (lit == local_max_ids.begin())
                {
                    mit = rit;
                    ++rit;
                }
                else
                {
                    mit = lit;
                    --lit;
                }
            }
            else
            {
                ++rit;
                ++mit;
                ++lit;
            }
        }
        
        int result = 0;
        lit = local_max_ids.begin();
        rit = lit;
        ++rit;
        for (; rit != local_max_ids.end(); ++lit, ++rit)
        {
            int top = height[*lit] < height[*rit] ? height[*lit] : height[*rit];
            for (int j = *lit + 1; j < *rit; ++j)
            {
                if (height[j] <= top)
                    result += top - height[j];
            }
        }
        
        return result;
    }
};
