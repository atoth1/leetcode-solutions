// https://leetcode.com/problems/maximize-score-after-n-operations/

#include <numeric>
#include <queue>
#include <utility>
#include <vector>

namespace {
    
    struct IdPair {
        int id1;
        int id2;
    };
    
    using Partition = std::vector<IdPair>;
    
    using PartitionList = std::vector<Partition>;
    
    static constexpr int MAX_PAIRS = 7;
    
    auto generateIdPartitions() {
        std::vector<PartitionList> partitionLists{ PartitionList{ Partition{ IdPair{ 0, 1 } } } };
        for (int pairId = 1; pairId < MAX_PAIRS; ++pairId) {
            const int id1 = 2 * pairId;
            const int id2 = id1 + 1;
            PartitionList newPartitions{};
            for (const Partition& prevPartition : partitionLists.back()) {
                Partition partition1(prevPartition);
                partition1.push_back({ id1, id2 });
                newPartitions.push_back(std::move(partition1));
                
                for (int prevPairId = 0; prevPairId < pairId; ++prevPairId) {
                    Partition partition2(prevPartition);
                    partition2.push_back({ std::exchange(partition2[prevPairId].id2, id1), id2 });
                    newPartitions.push_back(std::move(partition2));
                    
                    Partition partition3(prevPartition);
                    partition3.push_back({ std::exchange(partition3[prevPairId].id2, id2), id1 });
                    newPartitions.push_back(std::move(partition3));
                }
            }
            partitionLists.push_back(std::move(newPartitions));
        }
        return partitionLists;
    }
    const auto partitionLists = generateIdPartitions();
    
    auto computeGcds(const std::vector<int>& nums) {
        const int n = nums.size();
        std::vector gcds(n, std::vector<int>(n));
        for (int id1 = 0; id1 < n; ++id1) {
            for (int id2 = id1 + 1; id2 < n; ++id2) {
                const int gcd = std::gcd(nums[id1], nums[id2]);
                gcds[id1][id2] = gcd;
                gcds[id2][id1] = gcd;
            }
        }
        return gcds;
    }
}

class Solution {
public:
    static int maxScore(const std::vector<int>& nums) {
        const auto gcds = computeGcds(nums);
        std::priority_queue<int> gcdQueue{};
        
        const int idPairs = nums.size() / 2;
        int max = 0;
        for (const Partition& partition : partitionLists[idPairs - 1]) {
            for (const auto [id1, id2] : partition) {
                gcdQueue.push(gcds[id1][id2]);
            }
            
            int candidate = 0;
            while (!gcdQueue.empty()) {
                candidate += gcdQueue.top() * gcdQueue.size();
                gcdQueue.pop();
            }
            max = std::max(max, candidate);
        }
        return max;
    }
};
