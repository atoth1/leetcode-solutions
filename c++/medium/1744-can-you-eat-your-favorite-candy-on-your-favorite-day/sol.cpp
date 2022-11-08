// https://leetcode.com/problems/can-you-eat-your-favorite-candy-on-your-favorite-day/

class Solution {
public:
    vector<bool> canEat(vector<int>& candiesCount, vector<vector<int>>& queries) {
        // Total number prior to a given index
        std::vector<long long> cum(candiesCount.size(), 0);
        for (int pos = 1; pos < candiesCount.size(); ++pos) {
            cum[pos] = cum[pos-1] + candiesCount[pos-1];
        }
        
        std::vector<bool> ret{};
        ret.reserve(queries.size());
        for (const auto& query : queries) {
            const int& typePos = query[0];
            const int& targetDay = query[1];
            const int& limit = query[2];
            // limit candies per day
            long long firstPossible = cum[typePos]/limit;
            // One candy per day
            long long lastPossible = cum[typePos] + candiesCount[typePos] - 1;
            ret.push_back(targetDay >= firstPossible &&  targetDay <= lastPossible);
        }
        return ret;
    }
};
