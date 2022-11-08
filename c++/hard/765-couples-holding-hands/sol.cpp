// https://leetcode.com/problems/couples-holding-hands/

#include <memory>
#include <unordered_set>

class Solution {
public:
    int minSwapsCouples(vector<int>& row) {
        std::vector<std::shared_ptr<SetNode>> nodes(row.size()/2);
        
        auto setNodeConnection = [&nodes] (int id, int neighborId) {
            if (!nodes[id/2])
            {
                nodes[id/2] = std::make_unique<SetNode>();
                nodes[id/2]->id = id/2;
            }
            if (nodes[id/2]->aConnectId == -1)
            {
                nodes[id/2]->aConnectId = neighborId/2;
            }
            else
            {
                nodes[id/2]->bConnectId = neighborId/2;
            }
        };
        for (int id = 0; id < row.size(); id += 2)
        {
            setNodeConnection(row[id], row[id+1]);
            setNodeConnection(row[id+1], row[id]);
        }
        
        for (const auto& nodePtr : nodes)
        {
            mergeSets(nodePtr, nodes[nodePtr->aConnectId]);
            mergeSets(nodePtr, nodes[nodePtr->bConnectId]);
        }
        
        std::unordered_set<int> rootIds{};
        int count = 0;
        for (const auto& nodePtr : nodes)
        {
            auto rootPtr = rootNode(nodePtr);
            if (rootIds.count(rootPtr->id) == 0)
            {
                count += rootPtr->size - 1;
                rootIds.insert(rootPtr->id);
            }
        }
        return count;
    }
    
private:
    struct SetNode
    {
        int id = -1;
        int aConnectId = -1;
        int bConnectId = -1;
        std::shared_ptr<SetNode> parent = nullptr;
        int size = 1;
    };
    
    static std::shared_ptr<SetNode> rootNode(std::shared_ptr<SetNode> x)
    {
        auto root = x;
        while (root->parent)
        {
            root = root->parent;
        }
        
        while (x != root)
        {
            auto tmp = x->parent;
            x->parent = root;
            x = tmp;
        }
        return root;
    }
    
    static void mergeSets(std::shared_ptr<SetNode> x,
                          std::shared_ptr<SetNode> y)
    {
        x = rootNode(x);
        y = rootNode(y);
        if (x != y)
        {
            if (x->size > y->size)
            {
                x->size += y->size;
                y->parent = x;
            }
            else
            {
                y->size += x->size;
                x->parent = y;
            }
        }
    }
};
