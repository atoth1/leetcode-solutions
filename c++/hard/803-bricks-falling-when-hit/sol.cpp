// https://leetcode.com/problems/bricks-falling-when-hit/

#include <array>
#include <optional>
#include <utility>
#include <vector>

namespace {

struct Position {
  int row;
  int col;

  constexpr bool operator<=>(const Position&) const noexcept = default;
};

struct Direction {
  int rowDelta;
  int colDelta;
};

constexpr std::array dirs{Direction{-1, 0}, Direction{0, -1}, Direction{0, 1}, Direction{1, 0}};

constexpr Position operator+(const Position pos, const Direction dir) {
  return {pos.row + dir.rowDelta, pos.col + dir.colDelta};
}

class DSU {
public:
  DSU(const int rows, const int cols) : nodes(rows, std::vector<Node>(cols)) {
    for (auto& node : nodes[0]) {
      node.isStable = true;
    }
  }

  Position getRootPosition(Position pos) {
    auto rootPos = pos;
    while (nodes[rootPos.row][rootPos.col].parentPos) {
      rootPos = *nodes[rootPos.row][rootPos.col].parentPos;
    }

    while (nodes[pos.row][pos.col].parentPos) {
      pos = std::exchange(*nodes[pos.row][pos.col].parentPos, rootPos);
    }
    return rootPos;
  }

  bool inSameSet(Position pos1, Position pos2) {
    pos1 = getRootPosition(pos1);
    pos2 = getRootPosition(pos2);
    return pos1 == pos2;
  }

  void join(Position pos1, Position pos2) {
    pos1 = getRootPosition(pos1);
    pos2 = getRootPosition(pos2);
    if (pos1 != pos2) {
      if (nodes[pos1.row][pos1.col].size < nodes[pos2.row][pos2.col].size) {
        std::swap(pos1, pos2);
      }
      nodes[pos1.row][pos1.col].size += nodes[pos2.row][pos2.col].size;
      nodes[pos1.row][pos1.col].isStable |= nodes[pos2.row][pos2.col].isStable;
      nodes[pos2.row][pos2.col].parentPos = pos1;
    }
  }

  int getSetSize(Position pos) {
    pos = getRootPosition(pos);
    return nodes[pos.row][pos.col].size;
  }

  bool isStable(Position pos) {
    pos = getRootPosition(pos);
    return nodes[pos.row][pos.col].isStable;
  }

private:
  struct Node {
    std::optional<Position> parentPos{};
    int size = 1;
    bool isStable = false;
  };

  std::vector<std::vector<Node>> nodes;
};
} // namespace

class Solution {
public:
  static std::vector<int> hitBricks(const std::vector<std::vector<int>>& grid,
                                    const std::vector<std::vector<int>>& hits) {
    const int rows = grid.size();
    const int cols = grid[0].size();

    auto inBounds = [&](const Position pos) {
      return pos.row >= 0 && pos.row < rows && pos.col >= 0 && pos.col < cols;
    };

    auto makeFinalState = [&]() {
      std::vector state(rows, std::vector<bool>(cols));
      for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
          if (grid[row][col]) {
            state[row][col] = true;
          }
        }
      }

      for (const auto& pt : hits) {
        state[pt[0]][pt[1]] = false;
      }
      return state;
    };

    auto makeDSU = [&](const std::vector<std::vector<bool>>& state) {
      DSU dsu(rows, cols);
      for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
          if (state[row][col]) {
            if (row < rows - 1 && state[row + 1][col]) {
              dsu.join({row, col}, {row + 1, col});
            }

            if (col < cols - 1 && state[row][col + 1]) {
              dsu.join({row, col}, {row, col + 1});
            }
          }
        }
      }
      return dsu;
    };

    auto state = makeFinalState();
    auto dsu = makeDSU(state);
    std::vector<int> ret(hits.size());
    for (int id = ret.size() - 1; id >= 0; --id) {
      const Position pos{hits[id][0], hits[id][1]};
      if (grid[pos.row][pos.col] && !state[pos.row][pos.col]) {
        state[pos.row][pos.col] = true;
        int unstableNeighborCount = 0;
        for (const auto dir : dirs) {
          const auto neighbor = pos + dir;
          if (inBounds(neighbor) && state[neighbor.row][neighbor.col] && !dsu.inSameSet(pos, neighbor)) {
            if (!dsu.isStable(neighbor)) {
              unstableNeighborCount += dsu.getSetSize(neighbor);
            }
            dsu.join(pos, neighbor);
          }
        }

        if (dsu.isStable(pos)) {
          ret[id] = unstableNeighborCount;
        }
      }
    }
    return ret;
  }
};
