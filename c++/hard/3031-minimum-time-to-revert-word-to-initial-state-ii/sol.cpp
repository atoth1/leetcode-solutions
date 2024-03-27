// #include <algorithm>
#include <cstdlib>
#include <string_view>

namespace {

constexpr std::size_t MOD = 10000019;

constexpr std::size_t COEF = 31;

// Unique number x s.t. (COEF * x) % MOD == 1 (computed offline)
constexpr std::size_t COEF_MULT_INV = 8709694;

std::size_t modPlus(const std::size_t x, const std::size_t y) { return (x + y) % MOD; }

std::size_t modMinus(const std::size_t x, const std::size_t y) { return x >= y ? x - y : x - y + MOD; }

std::size_t modTimes(const std::size_t x, const std::size_t y) { return (x * y) % MOD; }

std::size_t toHash(const char c) { return c - 'a' + 1; }

class ShrinkableHash {
public:
  ShrinkableHash(std::string_view inStr) : str(inStr) {
    for (const char c : str) {
      hash = modPlus(modTimes(COEF, hash), toHash(c));
      leadingTermCoef = modTimes(COEF, leadingTermCoef);
    }
  }

  void shrinkFront(const int terms) {
    const int bound = std::min(terms, static_cast<int>(str.size()));
    for (int repeat = 0; repeat < bound; ++repeat) {
      hash = modMinus(hash, modTimes(toHash(str.front()), leadingTermCoef));
      leadingTermCoef = modTimes(leadingTermCoef, COEF_MULT_INV);
      str.remove_prefix(1);
    }
  }

  void shrinkBack(const int terms) {
    const int bound = std::min(terms, static_cast<int>(str.size()));
    for (int repeat = 0; repeat < bound; ++repeat) {
      hash = modTimes(modMinus(hash, toHash(str.back())), COEF_MULT_INV);
      leadingTermCoef = modTimes(leadingTermCoef, COEF_MULT_INV);
      str.remove_suffix(1);
    }
  }

  std::string_view getStr() const noexcept { return str; }

  bool isEmpty() const noexcept { return str.empty(); }

  std::size_t getHash() const noexcept { return hash; }

private:
  std::string_view str{};
  std::size_t hash{};
  std::size_t leadingTermCoef{COEF_MULT_INV};
};
} // namespace

class Solution {
public:
  static int minimumTimeToInitialState(std::string_view word, const int k) {
    ShrinkableHash frontHash(word);
    ShrinkableHash backHash(word);
    int ret = 0;
    while (!frontHash.isEmpty()) {
      ++ret;
      frontHash.shrinkBack(k);
      backHash.shrinkFront(k);
      if (frontHash.getHash() == backHash.getHash() && frontHash.getStr() == backHash.getStr()) {
        return ret;
      }
    }
    return 0;
  }
};
