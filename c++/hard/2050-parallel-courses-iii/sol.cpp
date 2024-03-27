// https://leetcode.com/problems/parallel-courses-iii/

#include <unordered_set>
#include <utility>
#include <vector>

class Solution {
public:
    static int minimumTime(int, const std::vector<std::vector<int>>& relations, const std::vector<int>& time) {
        auto maxOf = [](const int x, const int y) { return x > y ? x : y; };
        const int n = time.size();
        const std::vector<Data> data = topoSort(n, relations);
        std::vector<int> minToFinish(n);
        int ret = 0;
        for (const Data& entry : data) {
            int startTime = 0;
            for (const int reqId : entry.requiresIds) {
                startTime = maxOf(startTime, minToFinish[reqId]);
            }
            const int finishTime = startTime + time[entry.courseId];
            minToFinish[entry.courseId] = finishTime;
            ret = maxOf(ret, finishTime);
        }
        return ret;
    }
    
private:
    struct Data {
        int courseId;
        std::unordered_set<int> requiresIds{};
    };
    
    static std::vector<Data> topoSort(const int n, const std::vector<std::vector<int>>& relations) {
        std::vector<Data> data{};
        data.reserve(n);
        for (int id = 0; id < n; ++id) {
            data.push_back(Data{ id });
        }

        std::vector<std::vector<int>> preceedsIds(n);
        for (const auto& relation : relations) {
            // Silly 1-indexing
            const int fromId = relation[0] - 1;
            const int toId = relation[1] - 1;
            preceedsIds[fromId].push_back(toId);
            data[toId].requiresIds.insert(fromId);
        }

        std::vector<int> requirementsSatisfied{};
        for (const Data& entry : data) {
           if (entry.requiresIds.empty()) requirementsSatisfied.push_back(entry.courseId);
        }

        std::vector<std::unordered_set<int>> requirements(n);
        for (int id = 0; id < n; ++id) {
            requirements[id] = data[id].requiresIds;
        }

        std::vector<Data> ret{};
        ret.reserve(n);
        while (!requirementsSatisfied.empty()) {
            const Data& entry = data[requirementsSatisfied.back()];
            requirementsSatisfied.pop_back();

            for (const int id : preceedsIds[entry.courseId]) {
                requirements[id].erase(entry.courseId);
                if (requirements[id].empty()) requirementsSatisfied.push_back(id);
            }

            ret.push_back(std::move(entry));
        }
        return ret;
    }
};