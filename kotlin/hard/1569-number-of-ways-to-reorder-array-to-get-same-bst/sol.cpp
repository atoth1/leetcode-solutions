// https://leetcode.com/problems/number-of-ways-to-reorder-array-to-get-same-bst/

#include <map>
#include <utility>
#include <vector>

class Solution {
public:
    int numOfWays(const std::vector<int>& nums) {
        const int n = nums.size();
        if (n <= 2) return 0;
        
        const auto partitioning = partition(nums);
        const auto& less = partitioning.first;
        const auto& greater = partitioning.second;
        int lessOrderings = 1 + numOfWays(less);
        int greaterOrderings = 1 + numOfWays(greater);
        int permutations = nChooseK(n - 1, minOf(less.size(), greater.size()));
        int ret = (static_cast<long long>(lessOrderings) * greaterOrderings) % MOD;
        ret = (static_cast<long long>(ret) * permutations) % MOD;
        return ret == 0 ? MOD - 1 : ret - 1;
    }
    
private:
    static constexpr int MOD = 1000000007;
                                    
    static std::map<std::pair<int, int>, int> permutationCache;
    
    static int minOf(const int x, const int y) {
        return x < y ? x : y;
    }
    
    static std::pair<std::vector<int>, std::vector<int>> partition(const std::vector<int>& vec) {
        std::vector<int> less{};
        std::vector<int> greater{};
        for (const int val : vec) {
            if (val < vec[0]) {
                less.push_back(val);
            } else if (val > vec[0]) {
                greater.push_back(val);
            }
        }
        return { less, greater };
    }
    
    static int nChooseK(const int n, const int k) {
        if (k == 0 || k == n) {
            return 1;
        }
        
        if (auto it = permutationCache.find({ n, k }); it != permutationCache.end()) {
            return it->second;
        }
        
        int ret = (nChooseK(n - 1, k - 1) + nChooseK(n - 1, k)) % MOD;
        permutationCache[{ n, k }] = ret;
        return ret;
    }
};
                                    
std::map<std::pair<int, int>, int> Solution::permutationCache{};