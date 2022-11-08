// https://leetcode.com/problems/falling-squares/

#include <tuple>
#include <utility>

class Solution {
public:
    using IntervalAndHeight = std::tuple<int, int, int>;
    
    vector<int> fallingSquares(vector<vector<int>>& positions) {
        static constexpr int invalidLeft = 0;
        static constexpr int invalidRight = 1000000000;
        static constexpr int invalidHeight = -1;
        std::vector<IntervalAndHeight> intervals{
            {invalidLeft, invalidLeft, invalidHeight},
            {invalidRight, invalidRight, invalidHeight}};
        
        std::vector<int> ret;
        int maxHeight = 0;
        for (const auto square : positions)
        {
            int ledge = square[0];
            int redge = square[0] + square[1];
            auto lbounds = find(intervals, ledge, Side::LEFT);
            auto rbounds = find(intervals, redge, Side::RIGHT);
            if (lbounds.first == rbounds.first && !lbounds.second && !rbounds.second)
            {
                intervals.insert(intervals.begin() + lbounds.first + 1,
                    {ledge, redge, square[1]});
                ++lbounds.first;
            }
            else
            {
                if (!lbounds.second)
                {
                    ++lbounds.first;
                    std::get<0>(intervals[lbounds.first]) = ledge;
                }
                else if (std::get<0>(intervals[lbounds.first]) < ledge)
                {
                    intervals.insert(intervals.begin() + lbounds.first,
                        {std::get<0>(intervals[lbounds.first]),
                         ledge,
                         std::get<2>(intervals[lbounds.first])});
                    ++lbounds.first;
                    ++rbounds.first;
                    std::get<0>(intervals[lbounds.first]) = ledge;
                }
                
                if (!rbounds.second)
                {
                    std::get<1>(intervals[lbounds.first]) = redge; // lbounds on purpose here
                }    
                else if (std::get<1>(intervals[rbounds.first]) > redge)
                {
                    intervals.insert(intervals.begin() + rbounds.first + 1,
                        {redge,
                         std::get<1>(intervals[rbounds.first]),
                         std::get<2>(intervals[rbounds.first])});
                    std::get<1>(intervals[lbounds.first]) = redge; // lbounds on purpose here
                }
                
                int tmpMax = 0;
                for (int id = lbounds.first; id < rbounds.first + 1; ++id)
                {
                    tmpMax = std::get<2>(intervals[id]) > tmpMax ?
                        std::get<2>(intervals[id]) : tmpMax;
                }
                std::get<2>(intervals[lbounds.first]) = square[1] + tmpMax;
                
                intervals.erase(intervals.begin() + lbounds.first + 1,
                                intervals.begin() + rbounds.first + 1);
            }
            
            ret.push_back((ret.empty() || std::get<2>(intervals[lbounds.first]) > ret.back())
                ? std::get<2>(intervals[lbounds.first]) : ret.back());
            
            if (std::get<1>(intervals[lbounds.first]) == std::get<0>(intervals[lbounds.first + 1])
               && std::get<2>(intervals[lbounds.first]) == std::get<2>(intervals[lbounds.first + 1]))
            {
                std::get<1>(intervals[lbounds.first]) = std::get<1>(intervals[lbounds.first + 1]);
                intervals.erase(intervals.begin() + lbounds.first + 1);
            }
            if (std::get<1>(intervals[lbounds.first - 1]) == std::get<0>(intervals[lbounds.first])
               && std::get<2>(intervals[lbounds.first - 1]) == std::get<2>(intervals[lbounds.first]))
            {
                std::get<0>(intervals[lbounds.first]) = std::get<0>(intervals[lbounds.first - 1]);
                intervals.erase(intervals.begin() + lbounds.first - 1);
            }
        }
        
        return ret;
    }
    
private:
    enum class Side {LEFT, RIGHT};
    
    std::pair<int, bool>
    find(const std::vector<IntervalAndHeight>& intervals, int pos, Side side)
    {
        int l = 0;
        int r = intervals.size()-1;
        while (l+1 != r)
        {
            int m = l + (r-l)/2;
            if ((side == Side::LEFT && pos < std::get<0>(intervals[m]))
                || (side == Side::RIGHT && pos <= std::get<0>(intervals[m])))
            {
                r = m;
            }
            else if ((side == Side::LEFT && pos >= std::get<1>(intervals[m]))
                || (side == Side::RIGHT && pos > std::get<1>(intervals[m])))
            {
                l = m;
            }
            else
            {
                return std::make_pair(m, true);
            }
        }
        return std::make_pair(l, false);
    }
};
