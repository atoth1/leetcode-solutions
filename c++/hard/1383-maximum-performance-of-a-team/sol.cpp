// https://leetcode.com/problems/maximum-performance-of-a-team/

#include <algorithm>
#include <queue>
#include <vector>

class Solution {
public:
    int maxPerformance(
        const int, // Absolutely unnecessary input
        const std::vector<int>& speed,
        const std::vector<int>& efficiency,
        const int k
    ) {
        auto makeSortedWorkers = [&]() {
            const int n = speed.size();
            std::vector<Worker> workers{};
            workers.reserve(n);
            for (int id = 0; id < n; ++id) {
                workers.push_back({ speed[id], efficiency[id] });
            }
            std::sort(workers.begin(), workers.end(), [](const Worker x, const Worker y) {
                return x.efficiency > y.efficiency;
            });
            return workers;
        };
        const auto workers = makeSortedWorkers();
        
        auto maxOf = [](long long x, long long y) { return x > y ? x : y; };
        
        auto comp = [](const Worker x, const Worker y) {
            return x.speed > y.speed;
        };
        using queue_t = std::priority_queue<Worker, std::vector<Worker>, decltype(comp)>;
        queue_t workerQueue{};
            
        long long sum = 0;
        long long max = 0;
        for (const Worker worker : workers) {
            if (workerQueue.size() < k) {
                sum += worker.speed;
                workerQueue.push(worker);
            } else if (comp(worker, workerQueue.top())) {
                sum += worker.speed - workerQueue.top().speed;
                workerQueue.pop();
                workerQueue.push(worker);
            }
            max = maxOf(max, sum * worker.efficiency);
        }
        return max % 1000000007;;
    }
    
private:
    struct Worker {
        int speed;
        int efficiency;
    };
};
