// https://leetcode.com/problems/combination-sum-iii/

class Solution {
public:
    vector<vector<int>> combinationSum3(int k, int n) {
        std::vector<std::vector<int>> ret{};
        std::vector<int> curr{};
        int sum = 0;
        impl(k, n, 1, sum, curr, ret);
        return ret;
    }
    
private:
    void impl(
        const int k,
        const int n,
        const int start,
        int& sum,
        std::vector<int>& curr,
        std::vector<std::vector<int>>& ret
    ) {
        for (int i = start; i < 10; ++i) {
            if (sum + i <= n) {
                sum += i;
                curr.push_back(i);
                if (curr.size() == k && sum == n) {
                    ret.push_back(curr);
                } else if (curr.size() < k && sum < n) { // can improve condition on sum but fuck it
                    impl(k, n, i+1, sum, curr, ret);
                }
                sum -= i;
                curr.pop_back();
            } else {
                break;
            }
        }
    }
};
