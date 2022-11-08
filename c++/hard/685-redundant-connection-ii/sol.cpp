// https://leetcode.com/problems/redundant-connection-ii/

#include <unordered_map>

namespace
{
struct Node
{
    enum class Status
    {
        Unvisited,
        Tentative,
        Visited
    };
    
    int id_{-1};
    int parentId_{-1};
    std::vector<int> childIds_{};
    Status status_{Status::Unvisited};
};
}

class Solution {
public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>>& edges) {
        std::vector<Node> nodes(edges.size());
        for (int id = 0; id < nodes.size(); ++id) nodes[id].id_ = id;
        
        std::vector<int> firstParentEdge;
        std::vector<int> secondParentEdge;
        for (const auto& edge : edges)
        {
            auto& parent = nodes[edge[0]-1];
            auto& child = nodes[edge[1]-1];
            parent.childIds_.push_back(child.id_);
            if (child.parentId_  == -1)
            {
                child.parentId_ = parent.id_;
            }
            else
            {
                firstParentEdge = {child.parentId_+1, child.id_+1};
                secondParentEdge = {parent.id_+1, child.id_+1};
            }
        }
        // Two nodes are both parent of one node, figure out which edge to remove
        if (!firstParentEdge.empty())
        {
            int pid = firstParentEdge[0]-1;
            int cid = firstParentEdge[1]-1;
            while (pid != -1)
            {
                pid = nodes[pid].parentId_;
                if (pid == cid) return firstParentEdge;
            }
            return secondParentEdge;
        }
        
        auto cycle = findCycle(nodes);
        for (auto eit = edges.crbegin(); eit != edges.crend(); ++eit)
        {
            if (cycle.count((*eit)[0]-1) == 1 && cycle[(*eit)[0]-1] == (*eit)[1]-1) return *eit;
        }
        return {};
    }
    
private:
    std::unordered_map<int, int> findCycle(std::vector<Node>& nodes)
    {
        std::unordered_map<int, int> cycle;
        for (auto& node : nodes)
        {
            if (node.status_ == Node::Status::Unvisited)
            {
                findCycleImpl(nodes, node, cycle);
                if (!cycle.empty()) break;
            }
        }
        return cycle;
    }
    
    void findCycleImpl(std::vector<Node>& nodes,
                       Node& node,
                       std::unordered_map<int, int>& cycle)
    {
        node.status_ = Node::Status::Tentative;
        for (const auto cid : node.childIds_)
        {
            auto& child = nodes[cid];
            if (child.status_ == Node::Status::Unvisited)
            {
                findCycleImpl(nodes, child, cycle);
            }
            else if (child.status_ == Node::Status::Tentative)
            {
                int childId = cid;
                int parentId = node.id_;
                do
                {
                    cycle[parentId] = childId;
                    childId = parentId;
                    parentId = nodes[parentId].parentId_;
                } while (parentId != node.id_);
            }
            if (!cycle.empty()) break;
        }
        node.status_ = Node::Status::Visited;
    }
};
