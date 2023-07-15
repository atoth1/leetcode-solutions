// https://leetcode.com/problems/the-number-of-good-subsets/

#include <array>
#include <numeric>
#include <utility>

namespace {
    template<class T, int N>
    struct StaticVector {
        constexpr T& operator[](const int pos) {
            return values_[pos];
        }
        
        constexpr const T& operator[](const int pos) const {
            return values_[pos];
        }
        
        constexpr void push_back(const T& val) {
            values_[size_++] = val;
        }
        
        constexpr int size() const {
            return size_;
        }
        
        T values_[N]{};
        int size_{ 0 };
    };
    
    static constexpr int MOD = 1000000007;
    
    // Count of primes less than 30
    static constexpr int maxSubsetSize = 10;
    using VecType = StaticVector<int, maxSubsetSize>;
    
    // Size known from prior run with vector
    static constexpr int nValidSubsets = 3327;
    using SubsetsType = std::array<VecType, nValidSubsets>;
    
    static constexpr int nCandidates = 18;
    static constexpr std::array<int, nCandidates> candidates{
        2, 3, 5, 6, 7, 10, 11, 13, 14, 15, 17, 19, 21, 22, 23, 26, 29, 30
    };
    
    constexpr SubsetsType initValidSubsets() {
        constexpr int bound = 1 << nCandidates;
        SubsetsType subsets{};
        int pos = 0;
        for (int i = 1; i < bound; ++i) {
            VecType subset{};
            long long prod = 1;
            bool validSubset = true;
            for (int candidateId = 0; candidateId < nCandidates; ++candidateId) {
                if (i & (1 << candidateId)) {
                    if (std::gcd(prod, candidates[candidateId]) != 1) {
                        validSubset = false;
                        break;
                    }
                    subset.push_back(candidates[candidateId]);
                    prod *= candidates[candidateId];
                }
            }
            if (validSubset) {
                subsets[pos++] = subset;
            }
        }
        return subsets;
    }
    
    SubsetsType validSubsets = initValidSubsets();
}

class Solution {
public:
    int numberOfGoodSubsets(vector<int>& nums) {
        auto getCounts = [&]() {
            static constexpr int maxN = 30;
            std::array<int, maxN> counts{};
            for (const int num : nums) {
                ++counts[num - 1];
            }
            return counts;
        };
        const auto counts = getCounts();
        
        auto getValidSubsetCountOmittingOnes = [&]() {
            int count = 0;
            for (const auto& subset : validSubsets) {
                int prod = 1;
                for (int id = 0; id < subset.size(); ++id) {
                    prod = (static_cast<long long>(prod) * counts[subset[id] - 1]) % MOD;
                }
                count = (count + prod) % MOD;
            }
            return count;
        };
        
        auto twoToN = [&](const int n) {
            int ret = 1;
            for (int repeat = 0; repeat < n; ++repeat) {
                ret = (2 * ret) % MOD;
            }
            return ret;
        };
        
        return (static_cast<long long>(twoToN(counts[0])) * getValidSubsetCountOmittingOnes()) % MOD;
    }
};