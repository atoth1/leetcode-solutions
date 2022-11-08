// https://leetcode.com/problems/decode-ways/

class Solution {
public:
    int numDecodings(string s) {
        if (s[0] == '0') return 0;
        
        int n = s.size();
        std::vector<int> cache(n, -1);
        auto impl = [&] (auto recursive, int id) {
            if (cache[id] != -1) return cache[id];
            else
            {
                if (id >= n)
                {
                    return 0;
                }
                else if (id == n - 1)
                {
                    if (s[id] == '0')
                        return cache[id] = 0;
                    else
                        return cache[id]= 1;
                    return cache[id];
                }
                else
                {
                    if (s[id] == '0')
                    {
                        cache[id] = 0;
                    }
                    else
                    {
                        int result = recursive(recursive, id+1);
                        if (s[id] == '1' || (s[id] == '2' && s[id+1] < '7'))
                        {
                            if (id < n-2)
                            {
                                result += recursive(recursive, id+2);
                            }
                            else
                            {
                                result += 1;
                            }
                        }
                        cache[id] =  result;
                    }
                    return cache[id];
                }
            }
        };
        
        return impl(impl, 0);
    }
};
