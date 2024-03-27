// https://leetcode.com/problems/find-all-people-with-secret/

#include <algorithm>
#include <utility>
#include <vector>

namespace
{
  class DSU
  {
  public:
    DSU(const int n) : nodes(n) {}

    int getRootId(int id)
    {
      int rootId = id;
      while (nodes[rootId].parentId != Node::NONE)
      {
        rootId = nodes[rootId].parentId;
      }

      while (nodes[id].parentId != Node::NONE)
      {
        id = std::exchange(nodes[id].parentId, rootId);
      }
      return rootId;
    }

    void join(int id1, int id2)
    {
      id1 = getRootId(id1);
      id2 = getRootId(id2);
      if (id1 != id2)
      {
        if (nodes[id1].rank < nodes[id2].rank)
        {
          std::swap(id1, id2);
        }
        else if (nodes[id1].rank < nodes[id2].rank)
        {
          ++nodes[id1].rank;
        }
        nodes[id2].parentId = id1;
      }
    }

    void reset(const int id)
    {
      nodes[id].parentId = Node::NONE;
      nodes[id].rank = 0;
    }

    bool inSameSet(const int id1, const int id2)
    {
      return getRootId(id1) == getRootId(id2);
    }

  private:
    struct Node
    {
      static constexpr int NONE = -1;
      int parentId = NONE;
      int rank = 0;
    };

    std::vector<Node> nodes;
  };
}

class Solution
{
public:
  static std::vector<int> findAllPeople(
      const int n,
      const std::vector<std::vector<int>> &meetings,
      const int firstPerson)
  {
    auto sortedMeetings(meetings);
    std::sort(sortedMeetings.begin(), sortedMeetings.end(), [](const auto &x, const auto &y)
              { return x[2] < y[2]; });

    DSU dsu(n);
    dsu.join(0, firstPerson);

    auto begin = sortedMeetings.begin();
    while (begin != sortedMeetings.end())
    {
      auto end = begin;
      while (end != sortedMeetings.end() && (*end)[2] == (*begin)[2])
      {
        dsu.join((*end)[0], (*end)[1]);
        ++end;
      }

      while (begin != end)
      {
        if (!dsu.inSameSet(0, (*begin)[0]))
        {
          dsu.reset((*begin)[0]);
          dsu.reset((*begin)[1]);
        }
        ++begin;
      }
    }

    std::vector<int> ret{};
    for (int id = 0; id < n; ++id)
    {
      if (dsu.inSameSet(0, id))
      {
        ret.push_back(id);
      }
    }
    return ret;
  }
};
