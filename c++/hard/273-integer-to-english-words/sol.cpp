// https://leetcode.com/problems/integer-to-english-words/

#include <array>
#include <string>
#include <string_view>
#include <vector>

class Solution {
public:
    static std::string numberToWords(const int num) {
        if (num == 0) return "Zero";
        
        auto toChunks = [](const std::string& str) {
            std::vector<std::string> chunks{};
            for (auto it = str.rbegin(); it != str.rend(); ++it) {
                if (chunks.empty() || chunks.back().size() == 3) {
                    chunks.push_back({ *it });
                } else {
                    chunks.back().push_back(*it);
                }
            }
            return chunks;
        };
        
        auto chunkToWords = [](const std::string& chunk) -> std::string {
            if (chunk == "000") return "";
            
            static constexpr std::array<std::string_view, 9> digits{
                "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine"
            };
            
            static constexpr std::array<std::string_view, 10> teens{
                "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
                "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"
            };
            
            static constexpr std::array<std::string_view, 8> tens{
                "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"
            };
            
            std::string ret{};
            if (chunk.size() == 3 && chunk[2] != '0') {
                ret.append(digits[chunk[2] - '0' - 1]);
                ret.append(" Hundred");
            }
            
            if (chunk.size() >= 2 && chunk[1] == '1') {
                if (!ret.empty()) {
                    ret.push_back(' ');
                }
                ret.append(teens[chunk[0] - '0']);
                return ret;
            }
            
            if (chunk.size() >= 2 && chunk[1] != '0') {
                if (!ret.empty()) {
                    ret.push_back(' ');
                }
                ret.append(tens[chunk[1] - '0' - 2]);
            }
            
            if (chunk[0] != '0')  {
                if (!ret.empty()) {
                    ret.push_back(' ');
                }
                ret.append(digits[chunk[0] - '0' - 1]);
            }
            return ret;
        };
        
        const auto chunks = toChunks(std::to_string(num));
        static constexpr std::array<std::string_view, 3> chunkLabel{ "Thousand", "Million", "Billion" };
        std::string ret{};
        for (int chunkId = chunks.size() - 1; chunkId >= 0; --chunkId) {
            const auto chunkStr = chunkToWords(chunks[chunkId]);
            if (!chunkStr.empty()) {
                if (!ret.empty()) {
                    ret.push_back(' ');
                }
                ret.append(chunkStr);
                if (chunkId > 0) {
                    ret.push_back(' ');
                    ret.append(chunkLabel[chunkId - 1]);
                }
            }
        }
        return ret;
    }
};
