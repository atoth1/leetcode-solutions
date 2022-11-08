// https://leetcode.com/problems/sum-of-distances-in-tree/

#include <map>
#include <memory>
#include <utility>

class Solution {
public:
    vector<int> sumOfDistancesInTree(int n, vector<vector<int>>& edges) {
        if (n == 1) return {0};
        
        std::vector<std::shared_ptr<GraphNode>> nodes(n);
        for (const auto edge : edges)
        {
            if (!nodes[edge[0]])
            {
                nodes[edge[0]] = std::make_shared<GraphNode>();
                nodes[edge[0]]->id = edge[0];
            }
            if (!nodes[edge[1]])
            {
                nodes[edge[1]] = std::make_shared<GraphNode>();
                nodes[edge[1]]->id = edge[1];
            }
            nodes[edge[0]]->neighbors.push_back(nodes[edge[1]]);
            nodes[edge[1]]->neighbors.push_back(nodes[edge[0]]);
        }
        
        std::vector<int> ret(n, 0);
        CacheType cache;
        for (const auto node : nodes)
        {
            int sum = 0;
            for (const auto neighbor : node->neighbors)
            {
                auto res = sumOfDistancesImpl(cache, neighbor, node);
                sum += res.first;
            }
            ret[node->id] = sum;
        }
        //std::cout << cache.size() << '\n';
        return ret;
    }
    
private:
    struct GraphNode
    {
        int id{-1};
        std::vector<std::shared_ptr<GraphNode>> neighbors{};
    };
    
    using CacheKey = std::pair<std::shared_ptr<GraphNode>, std::shared_ptr<GraphNode>>;
    using CacheVal = std::pair<int, int>;
    struct CacheKeyHash
    {
        std::size_t operator()(const CacheKey& key) const noexcept
        {
            static constexpr std::size_t maxNodes = 30000;
            if (key.first == nullptr)
            {
                return maxNodes*maxNodes;
            }
            return maxNodes*key.first->id + key.second->id;
        }
    };
    using CacheType = std::map<CacheKey, CacheVal>;
    //using CacheType = std::unordered_map<CacheKey, CacheVal, CacheKeyHash>;
    CacheVal sumOfDistancesImpl(CacheType& cache,
                                const std::shared_ptr<GraphNode> node,
                                const std::shared_ptr<GraphNode> parent)
    {
        auto it = cache.find(std::make_pair(parent, node));
        if (it != cache.end())
        {
            return it->second;
        }
        else
        {
            int sum = 1;
            int numPaths = 1;
            for (const auto neighbor : node->neighbors)
            {
                if (neighbor != parent)
                {
                    auto res = sumOfDistancesImpl(cache, neighbor, node);
                    sum += res.first + res.second;
                    numPaths += res.second;
                }
            }
            auto ret = std::make_pair(sum, numPaths);
            cache[std::make_pair(parent, node)] = ret;
            return ret;
        }
    }
};
