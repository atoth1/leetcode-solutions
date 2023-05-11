// https://leetcode.com/problems/ipo

#include <queue>

class Solution {
public:
    
    struct Project {
        int profit;
        int capital;
    };
    
    template <class Comp>
    using QueueType = std::priority_queue<Project, std::vector<Project>, Comp>;
    
    int findMaximizedCapital(
        const int maxProjects,
        const int initCapital,
        const std::vector<int>& profits, 
        const std::vector<int>& capitals
    ) {
        const int n = profits.size();
        auto minCapitalComp = [](const Project l, const Project r) {
            return l.capital > r.capital;
        };
        QueueType<decltype(minCapitalComp)> minCapitalQueue(minCapitalComp);
        for (int i = 0; i < n; ++i) {
            minCapitalQueue.push(Project{ profits[i], capitals[i] });
        }
        
        auto maxProfitComp = [](const Project l, const Project r) {
            return l.profit < r.profit;
        };
        QueueType<decltype(maxProfitComp)> maxProfitQueue(maxProfitComp);
        
        int capital = initCapital;
        for (int i = 0; i < maxProjects; ++i) {
            while (!minCapitalQueue.empty() && capital >= minCapitalQueue.top().capital) {
                maxProfitQueue.push(minCapitalQueue.top());
                minCapitalQueue.pop();
            }
            
            if (maxProfitQueue.empty()) break;
            capital += maxProfitQueue.top().profit;
            maxProfitQueue.pop();
        }
        return capital;
    }
};