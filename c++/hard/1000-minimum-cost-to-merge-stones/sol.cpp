// https://leetcode.com/problems/minimum-cost-to-merge-stones/

#include <algorithm>
#include <limits>
#include <numeric>
#include <optional>
#include <unordered_map>
#include <vector>

namespace {

class RangeSum {
public:
  RangeSum(const std::vector<int>& nums) {
    prefix.resize(nums.size() + 1);
    std::inclusive_scan(nums.begin(), nums.end(), prefix.begin() + 1);
  }

  int sumBetween(const int beginId, const int endId) const {
    // Throw if invalid bounds
    return prefix[endId] - prefix[beginId];
  }

private:
  std::vector<int> prefix;
};

struct State {
  int beginId;
  int endId;
  int piles;

  constexpr bool operator==(const State&) const noexcept = default;
};

struct StateHash {
  constexpr std::size_t operator()(const State x) const noexcept {
    constexpr int COEF = 31;
    std::size_t hash = x.beginId;
    hash = COEF * hash + x.endId;
    hash = COEF * hash + x.piles;
    return hash;
  }
};

using cache_t = std::unordered_map<State, std::optional<int>, StateHash>;

std::optional<int> impl(const RangeSum& rs, const int window, const State state, cache_t& cache) {
  const auto [begin, end, piles] = state;
  const int count = end - begin;
  if (count == piles) {
    return 0;
  } else if (count < piles || ((count - piles) % (window - 1)) != 0) {
    return std::nullopt;
  } else if (auto it = cache.find(state); it != cache.end()) {
    return it->second;
  } else {
    auto ret = std::numeric_limits<int>::max();
    if (piles == 1) {
      ret = rs.sumBetween(begin, end) + *impl(rs, window, State(begin, end, window), cache);
    } else {
      for (int lCount = 1; lCount < count; ++lCount) {
        const auto lScore = impl(rs, window, State(begin, begin + lCount, 1), cache);
        const auto rScore = impl(rs, window, State(begin + lCount, end, piles - 1), cache);
        if (lScore && rScore) {
          ret = std::min(ret, *lScore + *rScore);
        }
      }
    }
    cache[state] = ret;
    return ret;
  }
}
} // namespace

class Solution {
public:
  static int mergeStones(const std::vector<int>& stones, const int k) {
    RangeSum sums(stones);
    cache_t cache{};
    const auto ret = impl(sums, k, State(0, stones.size(), 1), cache);
    if (ret) {
      return *ret;
    } else {
      return -1;
    }
  }
};
