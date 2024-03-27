// https://leetcode.com/problems/design-graph-with-shortest-path-calculator/

#include <limits>
#include <vector>

class Graph {
public:
    Graph(const int n, const std::vector<std::vector<int>>& edges) : distances(n) {
        for (auto& vec : distances) vec = std::vector<int>(n, UNSET);
        for (int node = 0; node < n; ++node) distances[node][node] = 0;
        for (const auto& edge : edges) distances[edge[0]][edge[1]] = edge[2];
        for (int splitId = 0; splitId < n; ++splitId) {
            for (int fromId = 0; fromId < n; ++fromId) {
                for (int toId = 0; toId < n; ++toId) {
                    if (distances[fromId][splitId] + distances[splitId][toId] < distances[fromId][toId]) {
                        distances[fromId][toId] = distances[fromId][splitId] + distances[splitId][toId];
                    }
                }
            }
        }
    }
    
    void addEdge(const std::vector<int> edge) {
        if (edge[2] < distances[edge[0]][edge[1]]) {
            for (int fromId = 0; fromId < distances.size(); ++fromId) {
                for (int toId = 0; toId < distances.size(); ++toId) {
                    if (distances[fromId][edge[0]] + edge[2] + distances[edge[1]][toId] < distances[fromId][toId]) {
                        distances[fromId][toId] = distances[fromId][edge[0]] + edge[2] + distances[edge[1]][toId];
                    }
                }
            }
        }
    }
    
    int shortestPath(const int node1, const int node2) {
        return distances[node1][node2] == UNSET ? -1 : distances[node1][node2];
    }
    
private:
    // Divide by 3 so we can safely add 3 ints
    static constexpr int UNSET = std::numeric_limits<int>::max() / 3;
    
    std::vector<std::vector<int>> distances;
};

/**
 * Your Graph object will be instantiated and called as such:
 * Graph* obj = new Graph(n, edges);
 * obj->addEdge(edge);
 * int param_2 = obj->shortestPath(node1,node2);
 */
