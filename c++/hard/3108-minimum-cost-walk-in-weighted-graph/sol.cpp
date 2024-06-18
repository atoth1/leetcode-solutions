// https://leetcode.com/problems/minimum-cost-walk-in-weighted-graph/

#include <limits>
#include <optional>
#include <utility>
#include <vector>

namespace {
struct IdPair {
  int id1{};
  int id2{};
};

struct Edge {
  IdPair ids{};
  int weight{};
};

class UnionFind {
public:
  UnionFind(const int n) : nodes(n) {}

  void addEdge(const Edge edge) {
    const int rootId = joinAndGetRootId(edge.ids);
    nodes[rootId].minCost &= edge.weight;
  }

  int query(const IdPair ids) {
    const int rootId1 = getRootId(ids.id1);
    const int rootId2 = getRootId(ids.id2);
    if (rootId1 == rootId2) {
      return nodes[rootId1].minCost;
    } else {
      return -1;
    }
  }

private:
  struct Node {
    std::optional<int> parentId{};
    int rank{};
    int minCost{std::numeric_limits<int>::max()};
  };

  int getRootId(int nodeId) {
    int rootId = nodeId;
    while (nodes[rootId].parentId) {
      rootId = *nodes[rootId].parentId;
    }

    while (nodes[nodeId].parentId) {
      nodeId = std::exchange(*nodes[nodeId].parentId, rootId);
    }
    return rootId;
  }

  int joinAndGetRootId(const IdPair ids) {
    int rootId1 = getRootId(ids.id1);
    int rootId2 = getRootId(ids.id2);
    if (rootId1 != rootId2) {
      if (nodes[rootId1].rank < nodes[rootId2].rank) {
        std::swap(rootId1, rootId2);
      } else if (nodes[rootId1].rank == nodes[rootId2].rank) {
        ++nodes[rootId1].rank;
      }
      nodes[rootId1].minCost &= nodes[rootId2].minCost;
      nodes[rootId2].parentId = rootId1;
    }
    return rootId1;
  }

  std::vector<Node> nodes{};
};

} // namespace

class Solution {
public:
  static std::vector<int> minimumCost(const int n, const std::vector<std::vector<int>>& edges,
                                      const std::vector<std::vector<int>>& queries) {
    UnionFind unionFind(n);
    for (const auto& edge : edges) {
      unionFind.addEdge({{edge[0], edge[1]}, edge[2]});
    }

    std::vector<int> ret{};
    ret.reserve(queries.size());
    for (const auto& query : queries) {
      ret.push_back(unionFind.query({query[0], query[1]}));
    }
    return ret;
  }
};
