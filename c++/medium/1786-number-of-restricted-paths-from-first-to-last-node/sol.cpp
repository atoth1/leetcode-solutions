// https://leetcode.com/problems/number-of-restricted-paths-from-first-to-last-node/

#include <queue>
#include <tuple>
#include <utility>

class Solution {
public:
    int countRestrictedPaths(int n, vector<vector<int>>& edges) {
        auto distances = computeDistances(undirectedGraph(n, edges));
        
        std::vector<int> cache(n, UNSET);
        cache.back() = 1;
        return computePaths(0, directedGraph(edges, distances), cache);
    }
    
private:
    using key_type = std::pair<int, int>;
    static constexpr int UNSET = -1;
    static constexpr int MODULUS = 1000000007;
    
    std::vector<std::vector<key_type>> undirectedGraph(
        const int n,
        const std::vector<std::vector<int>>& edges
    ) {
        std::vector<std::vector<key_type>> ret(n);
        for (const auto& edge : edges) {
            ret[edge[0]-1].push_back(std::make_pair(edge[1]-1, edge[2]));
            ret[edge[1]-1].push_back(std::make_pair(edge[0]-1, edge[2]));
        }
        return ret;
    }
    
    std::vector<int> computeDistances(
        const std::vector<std::vector<key_type>>& graph
    ) {
        auto comp = [] (const key_type& l, const key_type& r) {
            return l.second > r.second;
        };
        
        using queue_type = std::priority_queue<key_type, std::vector<key_type>, decltype(comp)>;
        queue_type queue(comp);
        queue.push(std::make_pair(graph.size()-1, 0));
        std::vector<int> ret(graph.size(), UNSET);
        while (!queue.empty()) {
            auto path = queue.top();
            queue.pop();
            if (ret[path.first] == UNSET) {
                ret[path.first] = path.second;
                for (const auto neighbor : graph[path.first]) {
                    if (ret[neighbor.first] == UNSET) {
                        queue.push(std::make_pair(neighbor.first, path.second + neighbor.second));
                    }
                }
            }
        }
        return ret;
    }
    
    std::vector<vector<int>> directedGraph(
        const std::vector<std::vector<int>>& edges,
        const std::vector<int>& distances
    ) {
        std::vector<vector<int>> ret(distances.size());
        for (const auto& edge : edges) {
            if(distances[edge[0]-1] > distances[edge[1]-1]) {
                ret[edge[0]-1].push_back(edge[1]-1);
            } else if (distances[edge[1]-1] > distances[edge[0]-1]) {
                ret[edge[1]-1].push_back(edge[0]-1);
            }
        }
        return ret;
    }
    
    int computePaths(
        const int id,
        const std::vector<std::vector<int>>& graph,
        std::vector<int>& cache
    ) {
        if (cache[id] == UNSET) {
            int total = 0;
            for (const auto child : graph[id]) {
                total += computePaths(child, graph, cache);
                total %= MODULUS;
            }
            cache[id] = total;
        }
        return cache[id];
    }
};
