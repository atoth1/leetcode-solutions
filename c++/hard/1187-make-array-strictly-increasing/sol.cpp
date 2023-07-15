// https://leetcode.com/problems/make-array-strictly-increasing/

#include <algorithm>
#include <vector>
#include <unordered_map>
#include <utility>

class Solution {
public:
    int makeArrayIncreasing(const std::vector<int>& arr1, std::vector<int>& arr2) {
        auto isStrictlyIncreasing = [](const std::vector<int> arr) {
            for (int id = 1; id < arr.size(); ++id) {
                if (arr[id -1] >= arr[id]) return false;
            }
            return true;
        };
        if (isStrictlyIncreasing(arr1)) return 0;
        
        std::sort(arr2.begin(), arr2.end());
        arr2.erase(std::unique(arr2.begin(), arr2.end()), arr2.end());
        
        auto minOf = [](const int x, const int y) { return x < y ? x : y; };
        
        auto updateOrInitializeState = [&](
            std::unordered_map<int, int>& states,
            const int key,
            const int candidateValue
        ) {
            if (auto it = states.find(key); it != states.end()) {
                states[key] = minOf(candidateValue, it->second);
            } else {
                states[key] = candidateValue;
            }
        };
        
        std::unordered_map<int, int> states{ { arr1[0], 0 } };
        if (arr2[0] < arr1[0]) states[arr2[0]] = 1;
        for (int id = 1; id < arr1.size(); ++id) {
            std::unordered_map<int, int> nextStates{};
            for (const auto [last, count] : states) {
                if (arr1[id] > last) {
                    updateOrInitializeState(nextStates, arr1[id], count);
                }
                
                auto ub = std::upper_bound(arr2.cbegin(), arr2.cend(), last);
                if (ub != arr2.cend()) {
                    updateOrInitializeState(nextStates, *ub, count + 1);
                }
            }
            
            if (nextStates.empty()) return -1;
            std::swap(states, nextStates);
        }
        
        int min = arr2.size();
        for (const auto [_, count] : states) {
            min = minOf(min, count);
        }
        return min;
    }
};