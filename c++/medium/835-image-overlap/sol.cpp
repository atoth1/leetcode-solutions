// https://leetcode.com/problems/image-overlap/

#include <unordered_map>

class Solution {
public:
    int largestOverlap(vector<vector<int>>& img1, vector<vector<int>>& img2) {
        const int n = img1.size();
        // Could save some storage by only tallying ids in one image and doing
        // later loop over other matrix entries 
        std::vector<std::pair<int, int>> img1Ids;
        std::vector<std::pair<int, int>> img2Ids;
        for (int row = 0; row < n; ++row)
        {
            for (int col = 0; col < n; ++col)
            {
                if (img1[row][col] == 1) img1Ids.push_back(std::make_pair(row, col));
                if (img2[row][col] == 1) img2Ids.push_back(std::make_pair(row, col));
            }
        }
        
        std::unordered_map<std::pair<int, int>,
                           int,
                           PairHash> translationToSum;
        int max = 0;
        for (const auto pos1 : img1Ids)
        {
            for (const auto pos2 : img2Ids)
            {
                auto translation = std::make_pair(pos2.first - pos1.first,
                                                  pos2.second - pos1.second);
                ++translationToSum[translation];
                if (translationToSum[translation] > max) max = translationToSum[translation];
            }
        }
        return max;
    }
    
private:
    struct PairHash
    {
        std::size_t operator()(const std::pair<int, int> val) const noexcept
        {
            // Each component of val is in the range [-maxShift, maxShift]
            static constexpr int maxShift = 29;
            static constexpr int stride = 2*maxShift + 1;
            return stride*(val.first+maxShift) + val.second+maxShift;
        }
    };
};

