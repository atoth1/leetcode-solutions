// https://leetcode.com/problems/closest-room/description/

#include <algorithm>

class Solution {
public:
    vector<int> closestRoom(vector<vector<int>>& rooms, vector<vector<int>>& queries) {
        auto makeInfo = [&](const std::vector<std::vector<int>>& input) {
            std::vector<Info> info{};
            for (int id = 0; id < input.size(); ++id) {
                const auto& entry = input[id];
                info.push_back({ entry[0], entry[1], id });
            }
            std::sort(info.begin(), info.end(), [](const Info l, const Info r) {
                return l.id < r.id;
            });
            return info;
        };
        const auto roomInfo = makeInfo(rooms);
        const auto queryInfo = makeInfo(queries);

        auto solve = [&]() {
            std::vector<Info> closest(queryInfo.size(), Info{});

            // Get min distances to room on left
            auto lit = roomInfo.begin();
            std::vector<Info> roomStack{};
            for (const auto query : queryInfo) {
                auto updateStack = [&]() {
                    while (lit != roomInfo.end() && lit->id <= query.id) {
                        // Maintain monotonicity
                        while (!roomStack.empty() && roomStack.back().capacity <= lit->capacity) {
                            roomStack.pop_back();
                        }
                        roomStack.push_back(*lit++);
                    }
                };
                updateStack();

                auto binarySearch = [&]() {
                    if (query.capacity <= roomStack.back().capacity) {
                        closest[query.inputId] = roomStack.back();
                    } else if (query.capacity <= roomStack[0].capacity) {
                        int l = 0;
                        int r = roomStack.size() - 1;
                        while (l+1 != r) {
                            int m = (l+r)/2;
                            if (query.capacity <= roomStack[m].capacity) {
                                l = m;
                            } else {
                                r = m;
                            }
                        }
                        closest[query.inputId] = roomStack[l];
                    }
                };
                if (!roomStack.empty()) binarySearch();
            }

            // Get min distances to room on right
            auto rit = roomInfo.rbegin();
            roomStack.clear();
            for (auto qit = queryInfo.rbegin(); qit != queryInfo.rend(); ++qit) {
                const auto query = *qit;
                auto updateStack = [&]() {
                    while (rit != roomInfo.rend() && rit->id >= query.id) {
                        // Maintain monotonicity
                        while (!roomStack.empty() && roomStack.back().capacity <= rit->capacity) {
                            roomStack.pop_back();
                        }
                        roomStack.push_back(*rit++);
                    }
                };
                updateStack();

                auto updateIfCloser = [&](const Info leftRoom, const Info rightRoom, const Info query) {
                    if (leftRoom.id == -1 ||
                        rightRoom.id - query.id < query.id - leftRoom.id
                    ) {
                        closest[query.inputId] = rightRoom;
                    }
                };

                auto binarySearch = [&]() {
                    // Different from previous binary search since this needs
                    // to compare agains a possible candidate room from the left.
                    if (query.capacity <= roomStack.back().capacity) {
                        updateIfCloser(closest[query.inputId], roomStack.back(), query);
                    } else if (query.capacity <= roomStack[0].capacity) {
                        int l = 0;
                        int r = roomStack.size() - 1;
                        while (l+1 != r) {
                            int m = (l+r)/2;
                            if (query.capacity <= roomStack[m].capacity) {
                                l = m;
                            } else {
                                r = m;
                            }
                        }
                        updateIfCloser(closest[query.inputId], roomStack[l], query);
                    }
                };
                if (!roomStack.empty()) binarySearch();
            }

            std::vector<int> ret{};
            ret.reserve(closest.size());
            for (const auto room : closest) {
                ret.push_back(room.id);
            }
            return ret;
        };
        return solve();
    }

private:
    struct Info {
        int id{ -1 }; // roomId/preferred
        int capacity{ -1 }; // size/minSize
        int inputId{ -1 }; // position in input array
    };
};
