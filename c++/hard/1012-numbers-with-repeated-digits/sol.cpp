// https://leetcode.com/problems/numbers-with-repeated-digits/

#include <algorithm>
#include <array>
#include <numeric>
#include <set>
#include <vector>

namespace {

constexpr int factorialish(const int n, const int terms) {
  if (terms == 0) {
    return 1;
  } else {
    return n * factorialish(n - 1, terms - 1);
  }
}

// i-1 entry is the count of numbers with exactly i unique digits
constexpr std::array countWithUniqueDigits{9,
                                           9 * factorialish(9, 1),
                                           9 * factorialish(9, 2),
                                           9 * factorialish(9, 3),
                                           9 * factorialish(9, 4),
                                           9 * factorialish(9, 5),
                                           9 * factorialish(9, 6),
                                           9 * factorialish(9, 7),
                                           9 * factorialish(9, 8)};
} // namespace

class Solution {
public:
  static int numDupDigitsAtMostN(const int n) {
    auto getDigits = [](int num) {
      std::vector<int> digits{};
      while (num) {
        const int quot = num / 10;
        const int rem = num - 10 * quot;
        digits.push_back(rem);
        num = quot;
      }
      std::reverse(digits.begin(), digits.end());
      return digits;
    };
    const auto digits = getDigits(n);

    int countWithSameNumberDigits = (digits[0] - 1) * factorialish(9, digits.size() - 1);
    std::set includedDigits{digits[0]};
    for (auto digitIt = digits.begin() + 1; digitIt < digits.end(); ++digitIt) {
      const int remainingDigitCandidateCount = 10 - includedDigits.size() - 1;
      const int remainingDigitCount = digits.end() - digitIt - 1;
      const int contrib = factorialish(remainingDigitCandidateCount, remainingDigitCount);
      for (int candidateDigit = 0; candidateDigit < *digitIt; ++candidateDigit) {
        if (!includedDigits.contains(candidateDigit)) {
          countWithSameNumberDigits += contrib;
        }
      }

      if (!includedDigits.insert(*digitIt).second) {
        break;
      }
    }
    if (includedDigits.size() == digits.size()) {
      ++countWithSameNumberDigits;
    }

    const int countWithFewerDigits =
        std::accumulate(countWithUniqueDigits.begin(), countWithUniqueDigits.begin() + digits.size() - 1, 0);
    return n - countWithSameNumberDigits - countWithFewerDigits;
  }
};
