// https://leetcode.com/problems/check-if-array-pairs-are-divisible-by-k/

class Solution {
public:
    bool canArrange(vector<int>& arr, int k) {
        std::vector<int> counts(k, 0);
        for (const int num : arr) {
            int quot = num/k;
            int rem = num - k*quot;
            if (rem < 0) rem += k;
            ++counts[rem];
        }
        
        if (counts[0] & 1) return false;
        for (int pos = 1; pos <= (k-1)/2; ++pos) {
           if (counts[pos] != counts[k-pos]) return false;
        }
        return true;
    }
};
