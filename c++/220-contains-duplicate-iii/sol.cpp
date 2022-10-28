// https://leetcode.com/problems/contains-duplicate-iii/

#include <set>

class Solution {
public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        if (k == 0) return false;
        std::set<int> valsInWindow{};
        auto windowBegin = nums.cbegin();
        auto windowEnd = nums.cbegin();
        for (int i = 0; i < k + 1 && windowEnd != nums.cend(); ++i) {
            auto inserted = valsInWindow.insert(*windowEnd);
            // Success on duplicate insertion, regarless of value of t
            if (!inserted.second) return true;
            ++windowEnd;
        }
        
        auto safeCheck = [&t] (long long greater, long long lesser) {
            return greater - lesser  <= static_cast<long long>(t);
        };
        
        auto curr = valsInWindow.cbegin();
        auto next = curr;
        ++next;
        while (next != valsInWindow.cend()) {
            if (safeCheck(*next, *curr)) return true;
            ++curr;
            ++next;
        }
        
        while (windowEnd != nums.cend()) {
            valsInWindow.erase(*windowBegin);
            ++windowBegin;
            
            auto inserted = valsInWindow.insert(*windowEnd);
            if (!inserted.second) return true;
            if (inserted.first != valsInWindow.begin()) {
                auto prev = inserted.first;
                --prev;
                if (safeCheck(*(inserted.first), *prev)) return true;
            }
            auto next = inserted.first;
            ++next;
            if (next != valsInWindow.end()) {
                if (safeCheck(*next, *(inserted.first))) return true;
            }
            ++windowEnd;
        }
        return false;
    }
};
