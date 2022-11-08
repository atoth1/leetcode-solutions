// https://leetcode.com/problems/bus-routes/

#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <utility>

class Solution {
public:
    int numBusesToDestination(vector<vector<int>>& routes, int source, int target) {
        if (source == target) return 0;
        auto stops = makeStops(routes);
        if (!stops[source] || !stops[target]) return -1;
        
        std::unordered_set<std::shared_ptr<Stop>> curr{ stops[source] };
        std::unordered_set<std::shared_ptr<Stop>> next;
        int numRoutes = 0;
        while (!curr.empty())
        {
            ++numRoutes;
            for (const auto stop : curr)
            {
                stop->visited = true;
                for (const auto route : stop->routes)
                {
                    for (const auto routeStop : route->stops)
                    {
                        if (routeStop->id == target) return numRoutes;
                        if (!routeStop->visited && curr.count(routeStop) == 0) next.insert(routeStop);
                    }
                }
            }
            std::swap(curr, next);
            next.clear();
        }
        return -1;
    }
    
private:
    // Should probably just eliminate Route struct and have a set of the
    // other Stops which can be reached in one ride from this stop
    struct Route;
    struct Stop
    {
        int id{-1};
        std::vector<std::shared_ptr<Route>> routes{};
        bool visited{false};
    };
    
    struct Route
    {
        std::vector<std::shared_ptr<Stop>> stops{};
        //std::vector<Stop*> stops{};
    };
    
    std::unordered_map<int, std::shared_ptr<Stop>> makeStops(
        const std::vector<std::vector<int>>& routes)
    {
        std::unordered_map<int, std::shared_ptr<Stop>> stops;
        for (const auto& route : routes)
        {
            auto routePtr = std::make_shared<Route>();
            for (const auto stop : route)
            {
                if (!stops[stop])
                {
                    stops[stop] = std::make_shared<Stop>();
                    stops[stop]->id = stop;
                }
                routePtr->stops.push_back(stops[stop]);
                stops[stop]->routes.push_back(routePtr);
            }
        }
        return stops;
    }
};
