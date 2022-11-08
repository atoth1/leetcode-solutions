// https://leetcode.com/problems/making-a-large-island/

#include <map>
#include <memory>
#include <utility>

class Solution {
public:
    int largestIsland(vector<vector<int>>& grid) {
        // Problem says n x n, but not reason not to generalize to m x n
        int m = grid.size();
        int n = grid[0].size();
        std::vector<std::vector<SetNodePtr>> nodes(
            m, std::vector<SetNodePtr>(n, nullptr));
        std::vector<std::pair<int, int>> candidateCoords;
        for (int row = 0; row < m; ++row)
        {
            for (int col = 0; col < n; ++col)
            {
                if (grid[row][col] == 1)
                {
                    if (!nodes[row][col])
                        nodes[row][col] = std::make_shared<SetNode>();
                    // Don't worry about row-1 or col-1, those are already merged
                    if (row < m-1 && grid[row+1][col] == 1)
                    {
                        if (!nodes[row+1][col])
                            nodes[row+1][col] = std::make_shared<SetNode>();
                        mergeSets(nodes[row][col], nodes[row+1][col]);
                    }
                    if (col < n-1 && grid[row][col+1] == 1)
                    {
                        if (!nodes[row][col+1])
                            nodes[row][col+1] = std::make_shared<SetNode>();
                        mergeSets(nodes[row][col], nodes[row][col+1]);
                    }
                }
                else
                {
                    // Check for neighboring islands
                    if ((row > 0 && grid[row-1][col] == 1) ||
                        (row < m-1 && grid[row+1][col] == 1) ||
                        (col > 0 && grid[row][col-1] == 1) ||
                        (col < n-1 && grid[row][col+1] == 1))
                    {
                        candidateCoords.push_back(std::make_pair(row, col));
                    }
                }
            }
        }
        
        if (candidateCoords.empty())
        {
            // grid is either all 0's or all 1's
            return grid[0][0] == 1 ? m*n : 1;
        }
        
        int max = 0;
        for (const auto coords : candidateCoords)
        {
            int row = coords.first;
            int col = coords.second;
            int candidateSize = 1;
            
            SetNodePtr upRoot = nullptr;
            if (row > 0 && nodes[row-1][col])
            {
                upRoot = nodeRoot(nodes[row-1][col]);
                candidateSize += upRoot->size;
            }
            
            SetNodePtr downRoot = nullptr;
            if (row < m-1 && nodes[row+1][col])
            {
                downRoot = nodeRoot(nodes[row+1][col]);
                if (downRoot != upRoot)
                    candidateSize += downRoot->size;
            }
            
            SetNodePtr leftRoot = nullptr;
            if (col > 0 && nodes[row][col-1])
            {
                leftRoot = nodeRoot(nodes[row][col-1]);
                if (leftRoot != upRoot && leftRoot != downRoot)
                    candidateSize += leftRoot->size;
            }
            
            SetNodePtr rightRoot = nullptr;
            if (col < n-1 && nodes[row][col+1])
            {
                rightRoot = nodeRoot(nodes[row][col+1]);
                if (rightRoot != upRoot && rightRoot != downRoot && rightRoot != leftRoot)
                    candidateSize += rightRoot->size;
            }
            if (candidateSize > max) max = candidateSize;
        }
        return max;
    }
    
private:
    struct SetNode
    {
        std::shared_ptr<SetNode> parent{nullptr};
        int size{1};
    };
    using SetNodePtr = std::shared_ptr<SetNode>;
    
    SetNodePtr nodeRoot(SetNodePtr node)
    {
        SetNodePtr root = node;
        while (root->parent) root = root->parent;
        while (node != root)
        {
            auto tmp = node->parent;
            node->parent = root;
            node = tmp;
        }
        return root;
    }
    
    void mergeSets(SetNodePtr x, SetNodePtr y)
    {
        x = nodeRoot(x);
        y = nodeRoot(y);
        if (x == y) return;
        if (x->size < y->size)
        {
            x->parent = y;
            y->size += x->size;
        }
        else
        {
            y->parent = x;
            x->size += y->size;
        }
    }
};
