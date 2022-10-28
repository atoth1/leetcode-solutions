// https://leetcode.com/problems/maximum-length-of-a-concatenated-string-with-unique-characters/

#include <array>

class Solution {
public:
    int maxLength(vector<string>& arr) {
        std::vector<std::array<bool, N>> containsChar{};
        for (const auto& str : arr) {
            std::array<bool, N> curr{};
            bool uniqueChars = true;
            for (const auto c : str) {
                if (!curr[c-'a']) curr[c-'a'] = true;
                else {
                    uniqueChars = false;
                    break;
                }
            }
            if (uniqueChars) {
                containsChar.push_back(std::move(curr));
            }
        }
        
        std::array<bool, N> chars{};
        int ret = 0;
        impl(containsChar, chars, 0, ret);
        return ret;
    }
    
private:
    static constexpr int N = 26;
    
    void impl(
        const std::vector<std::array<bool, N>>& containsChar,
        std::array<bool, 26>& chars,
        const int startId,
        int& max
    ) {
        for (int id = startId; id < containsChar.size(); ++id) {
            if (canAppend(chars, containsChar[id])) {
                int tmp = append(chars, containsChar[id]);
                if (tmp > max) max = tmp;
                impl(containsChar, chars, id+1, max);
                deppend(chars, containsChar[id]);
            }
        }
    }
    
    bool canAppend(const std::array<bool, N>& curr, const std::array<bool, N>& next) {
        for (int id = 0; id < N; ++id) {
            if (curr[id] && next[id]) return false;
        }
        return true;
    }
    
    int append(std::array<bool, N>& curr, const std::array<bool, N>& next) {
        int count = 0;
        for (int id = 0; id < N; ++id) {
            if (curr[id]) ++count;
            if (next[id]) {
                ++count;
                curr[id] = true;
            }
        }
        return count;
    }
    
    void deppend(std::array<bool, N>& curr, const std::array<bool, N>& next) {
        for (int id = 0; id < N; ++id) {
            if (next[id]) curr[id] = false;
        }
    }
    
};