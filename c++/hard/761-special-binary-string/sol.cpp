// https://leetcode.com/problems/special-binary-string/

#include <algorithm>
#include <functional>
#include <sstream>
#include <string>
#include <vector>

class Solution {
public:
  static std::string makeLargestSpecial(const std::string& s) { return impl(s, 0, s.size()); }

private:
  static std::string impl(const std::string& s, const int beginId, const int endId) {
    if (beginId == endId)
      return "";

    std::vector<std::string> substrs{};
    int substrBegin = beginId;
    int count = 0;
    for (int substrEnd = substrBegin + 1; substrEnd <= endId; ++substrEnd) {
      if (s[substrEnd - 1] == '1') {
        ++count;
      } else {
        --count;
        if (count == 0) {
          std::stringstream substr;
          substr << '1' << impl(s, substrBegin + 1, substrEnd - 1) << '0';
          substrs.push_back(substr.str());
          substrBegin = substrEnd;
        }
      }
    }

    std::sort(substrs.begin(), substrs.end(), std::greater<std::string>{});

    std::stringstream ret;
    for (const auto& substr : substrs) {
      ret << substr;
    }
    return ret.str();
  }
};
