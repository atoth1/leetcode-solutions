// https://leetcode.com/problems/gas-station/

class Solution {
public:
    int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
        int n = gas.size();
        // What is this length-1 cycle bullshit?
        if (n == 1) {
            if (gas[0] >= cost[0]) return 0;
            else return -1;
        }
        int sum = 0;
        for (int i = 0; i < n; ++i) {
            sum +=  gas[i] - cost[i];
        }
        if (sum < 0) return -1;
        
        static constexpr int UNSET = -1;
        int candidate = UNSET;
        int amount = 0;
        for (int i = 0; i < n; ++i) {
            if (candidate == UNSET) {
                if (gas[i] > cost[i]) {
                    candidate = i;
                    amount = gas[i] - cost[i];
                }
            } else {
                amount += gas[i] - cost[i];
                if (amount < 0) {
                    candidate = -1;
                    amount = 0; // Could probably take this out.
                }
            }
        }
        // Do we need to circle around and try to get back to candidate?
        // Or does non-negative sum above guarantee solution at this point?
        return candidate;
    }
};
