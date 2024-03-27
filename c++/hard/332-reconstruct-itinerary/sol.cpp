// https://leetcode.com/problems/reconstruct-itinerary/

#include <map>
#include <memory>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

class Solution {
    struct Node;
    
    using NodePtr = std::shared_ptr<Node>;
    
    struct Connection {
        NodePtr node{};
        int multiplicity{};
    };
    
    struct Node {
        std::map<std::string_view, Connection> connections{};
    };
    
    using GraphType = std::unordered_map<std::string_view, NodePtr>;
    
    static auto makeGraph(
        const std::vector<std::vector<std::string>>& edges
    ) { 
        GraphType graph{};
        auto getOrCreate = [&](const std::string_view label) {
            if (const auto it = graph.find(label); it != graph.end()) {
                return it->second;
            } else {
                auto ptr = std::make_shared<Node>();
                graph[label] = ptr;
                return ptr;
            }
        };
        for (const auto& edge : edges) {
            NodePtr from = getOrCreate(edge[0]);
            NodePtr to = getOrCreate(edge[1]);
            if (const auto it = from->connections.find(edge[1]); it != from->connections.end()){
                ++it->second.multiplicity;
            } else {
                from->connections[edge[1]] = { to, 1 };
            }
        }
        return graph;
    }
    
    static bool impl(
        GraphType& graph,
        const NodePtr curr,
        std::vector<std::string_view>& path,
        const int targetLength
    ) {
        if (path.size() == targetLength) return true;
        
        for (auto& [label, connection] : curr->connections) {
            if (connection.multiplicity > 0) {
                const auto next = connection.node;
                path.emplace_back(label);
                --connection.multiplicity;
                if (impl(graph, next, path, targetLength)) return true;
                path.pop_back();
                ++connection.multiplicity;
            }
        }
        return false;
    }
    
public:
    static std::vector<std::string> findItinerary(
        const std::vector<std::vector<std::string>>& tickets
    ) {
        static constexpr std::string_view startLabel = "JFK";
        auto graph = makeGraph(tickets);
        std::vector<std::string_view> ret{ startLabel };
        impl(graph, graph[startLabel], ret, tickets.size() + 1);
        return std::vector<std::string>(ret.begin(), ret.end());
    }
};