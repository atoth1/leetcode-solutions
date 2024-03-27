// https://leetcode.com/problems/meeting-rooms-iii/

#include <algorithm>
#include <functional>
#include <queue>
#include <vector>

class Solution {
public:
    static int mostBooked(const int n, const std::vector<std::vector<int>>& meetings) {
        std::vector<Room> rooms{};
        rooms.reserve(n);
        for (int id = 0; id < n; ++id) {
            rooms.push_back({ id });
        }
        
        std::vector<MeetingRequest> requests{};
        requests.reserve(meetings.size());
        for (const auto& meeting : meetings) {
            requests.push_back({ meeting[0], meeting[1] - meeting[0] });
        }
        std::sort(requests.begin(), requests.end());
        
        std::priority_queue<int, std::vector<int>, std::greater<int>> availableRoomIds{};
        for (int id = 0; id < n; ++id) {
            availableRoomIds.push(id);
        }
        
        std::priority_queue<Meeting> activeMeetings;
        for (const auto request : requests) {
            while (!activeMeetings.empty() && activeMeetings.top().endTime <= request.startTime) {
                availableRoomIds.push(activeMeetings.top().roomId);
                activeMeetings.pop();
            }
            
            if (availableRoomIds.empty()) {
                auto [roomId, startTime] = activeMeetings.top();
                ++rooms[roomId].meetingsHeld;
                activeMeetings.pop();
                activeMeetings.push({ roomId, startTime + request.duration });
                
            } else {
                ++rooms[availableRoomIds.top()].meetingsHeld;
                activeMeetings.push({ availableRoomIds.top(), request.startTime + request.duration });
                availableRoomIds.pop();
            }
        }
        
        int maxId = -1;
        int maxCount = 0;
        for (const auto room : rooms) {
            if (room.meetingsHeld > maxCount) {
                maxId = room.id;
                maxCount = room.meetingsHeld;
            }
        }
        return maxId;
    }
    
private:
    struct Room {
        int id;
        int meetingsHeld = 0;
    };
    
    struct MeetingRequest {
        long long startTime;
        int duration;
        
        constexpr bool operator<(const MeetingRequest other) const noexcept {
            return startTime < other.startTime;
        }
    };
    
    struct Meeting {
        int roomId;
        long long endTime;
        
        constexpr bool operator<(const Meeting other) const noexcept {
            return endTime == other.endTime ? roomId > other.roomId : endTime > other.endTime;
        }
    };
};
