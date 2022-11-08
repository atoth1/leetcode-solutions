// https://leetcode.com/problems/seat-reservation-manager/

#include <set>

class SeatManager {
public:
    SeatManager(int n) {
        for (int pos = 1; pos <= n; ++pos) {
            free.insert(pos);
        }
    }
    
    int reserve() {
        int ret = *free.begin();
        free.erase(free.begin());
        return ret;
    }
    
    void unreserve(int seatNumber) {
        free.insert(seatNumber);
    }
    
private:
    std::set<int> free{};
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */
