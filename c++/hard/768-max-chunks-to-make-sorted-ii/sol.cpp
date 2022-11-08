// https://leetcode.com/problems/max-chunks-to-make-sorted-ii/

#include <map>
#include <unordered_map>

class Solution {
public:
    int maxChunksToSorted(vector<int>& arr) {
        std::unordered_map<int, int> valSortedPos;
        {
            std::map<int, int> valCounts;
            for (const auto val : arr)
            {
                ++valCounts[val];
            }
            
            int start = 0;
            for (const auto& p : valCounts)
            {
                valSortedPos[p.first] = start;
                start += p.second;
            }
        }
        
        int count = 0;
        int endId = -1;
        for (int id = 0; id < arr.size(); ++id)
        {
            if (id > endId || valSortedPos[arr[id]] > endId)
            {
                endId = valSortedPos[arr[id]];
            }
            ++valSortedPos[arr[id]];
            
            if (id == endId) ++count;
        }
        return count;
    }
};