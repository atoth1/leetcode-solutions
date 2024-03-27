// https://leetcode.com/problems/minimum-operations-to-make-a-subsequence/

#include <map>
#include <iterator>
#include <span>
#include <unordered_map>
#include <vector>

namespace {

std::vector<int> makeSurrogate(const std::span<const int>& target, const std::span<const int>& arr) {
    std::unordered_map<int, int> idLookup{};
    for (int id = 0; id < target.size(); ++id) {
        idLookup[target[id]] = id;
    }

    std::vector<int> ret{};
    for (const int num : arr) {
        if (const auto it = idLookup.find(num); it != idLookup.end()) {
            ret.push_back(it->second);
        }
    }
    return ret;
}

int longestIncreasingSubsequence(const std::span<const int> nums) {
    if (nums.empty()) return 0;

    std::map<int, int> lengthTo{};
    for (const int num : nums) {
        if (lengthTo.empty()) {
            lengthTo[num] = 1;
            continue;
        }
        
        const auto it1 = lengthTo.lower_bound(num);
        if (it1 != lengthTo.end() && it1->first == num) continue;
        
        int length = 0;
        if (it1 == lengthTo.begin()) {
            lengthTo[num] = 1;
            length = 1;
        } else {
            const auto it2 = std::prev(it1);
            length = it2->second + 1;
            lengthTo[num] = length;
        }
        
        if (it1 != lengthTo.end() && it1->second == length) {
            lengthTo.erase(it1);
        }
    }
    return std::prev(lengthTo.end())->second;
}

}

class Solution {
public:
    static int minOperations(const std::span<const int>& target, const std::span<const int>& arr) {
        return target.size() - longestIncreasingSubsequence(makeSurrogate(target, arr));
    }
};
