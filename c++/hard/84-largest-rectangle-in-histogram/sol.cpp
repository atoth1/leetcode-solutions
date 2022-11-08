// https://leetcode.com/problems/largest-rectangle-in-histogram/

#include <list>

namespace
{
    struct Rectangle
    {
        int height = 0;
        int width = 0;
    };
}

class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        if (heights.size() == 0) return 0;
        std::list<Rectangle> prevMaxes{ {heights[0], 1} };
        int maxArea = heights[0];
        for (auto hit = heights.begin()+1; hit != heights.end(); ++hit)
        {
            if (*hit == 0)
            {
                prevMaxes.clear();
            }
            else
            {
                if (!prevMaxes.empty())
                {
                    auto prev = prevMaxes.begin();
                    prev->height = *hit < prev->height ? *hit : prev->height;
                    ++(prev->width);
                    int area = prev->height * prev->width;
                    maxArea = area > maxArea ? area : maxArea;
                    auto pit = prev;
                    ++pit;
                    while (pit != prevMaxes.end())
                    {
                        pit->height = *hit < pit->height ? *hit : pit->height;
                        ++(pit->width);
                        if (pit->height > prev->height)
                        {
                            area = pit->height * pit->width;
                            maxArea = area > maxArea ? area : maxArea;
                            ++pit;
                            ++prev;
                        }
                        else
                        {
                            pit = prevMaxes.erase(pit);
                        }
                    }
                }
                if (*hit > *(hit-1))
                {
                    prevMaxes.push_back({*hit, 1});
                    maxArea = *hit > maxArea ? *hit : maxArea;
                }
            }
        }
        return maxArea;
    }
};
