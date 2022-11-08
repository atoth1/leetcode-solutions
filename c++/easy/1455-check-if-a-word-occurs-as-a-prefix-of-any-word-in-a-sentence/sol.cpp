// https://leetcode.com/problems/check-if-a-word-occurs-as-a-prefix-of-any-word-in-a-sentence/

#include <string_view>

class Solution {
public:
    int isPrefixOfWord(string sentence, string searchWord) {
        auto split = [](const std::string_view str) {
            std::vector<std::string_view> words{};
            auto wordBegin = str.cbegin();
            while (wordBegin != str.cend()) {
                while (wordBegin != str.cend() && *wordBegin == ' ') ++wordBegin;
                if (wordBegin != str.cend()) {
                    auto wordEnd = wordBegin+1;
                    while (wordEnd != str.cend() && *wordEnd != ' ') ++wordEnd;
                    words.push_back(str.substr(wordBegin-str.cbegin(), wordEnd-wordBegin));
                    wordBegin = wordEnd;
                }
            }
            return words;
        };
        
        auto words = split(sentence);
        for (int id = 0; id < words.size(); ++id) {
            const auto word = words[id];
            if (word.size() >= searchWord.size()) {
                if (word.substr(0, searchWord.size()) == searchWord) return id + 1; // Fucking 1-indexed
            }
        }
        return -1;
    }
};
