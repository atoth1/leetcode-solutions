// https://leetcode.com/problems/gray-code/

class Solution {
public:
    vector<int> grayCode(int n) {
        if (n == 0)
        {
            return {0};
        }
        else
        {
            auto result = grayCode(n-1);
            result.reserve(2*result.size());
            const auto end = result.rend();
            const int mask = 1 << (n-1);
            for (auto it = result.rbegin(); it != end; ++it)
            {
                result.push_back(*it | mask);
            }
            return result;
        }
    }
};
