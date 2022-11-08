// https://leetcode.com/problems/similar-string-groups/

#include <memory>
#include <unordered_set>

class Solution {
public:
    int numSimilarGroups(vector<string>& strs) {
        auto equalOrDifferBy2 = [] (const std::string& l, const std::string& r) {
            int diffCount = 0;
            // Problem guarantees equal sized strings
            for (int id = 0; id < l.size(); ++id)
            {
                if (l[id] != r[id]) ++diffCount;
                if (diffCount > 2) return false;
            }
            // Problem guarantees anagrams, so can't differ by a single character
            return true;
        };
        
        std::vector<SetNodePtr> nodes(strs.size(), nullptr);
        for (int id1 = 0; id1 < strs.size(); ++id1)
        {
            nodes[id1] = std::make_shared<SetNode>();
            for (int id2 = 0; id2 < id1; ++id2)
            {
                if (!inSameSet(nodes[id1], nodes[id2]) &&
                    equalOrDifferBy2(strs[id1], strs[id2]))
                {
                    mergeSets(nodes[id1], nodes[id2]);
                }
            }
        }
        
        std::unordered_set<SetNodePtr> roots;
        for (const auto node : nodes) roots.insert(nodeRoot(node));
        return roots.size();
    }
    
private:
    struct SetNode;
    using SetNodePtr = std::shared_ptr<SetNode>;
    struct SetNode
    {
        SetNodePtr parent{nullptr};
        int rank{0};
    };
    
    SetNodePtr nodeRoot(SetNodePtr node)
    {
        auto root = node;
        while (root->parent)
        {
            root = root->parent;
        }
        while (node != root)
        {
            auto tmp = node->parent;
            node->parent = root;
            node = tmp;
        }
        return root;
    }
    
    bool inSameSet(const SetNodePtr x, const SetNodePtr y)
    {
        return nodeRoot(x) == nodeRoot(y);
    }
    
    void mergeSets(SetNodePtr x, SetNodePtr y)
    {
        if (!inSameSet(x, y))
        {
            x = nodeRoot(x);
            y = nodeRoot(y);
            
            if (x->rank < y->rank)
            {
                x->parent = y;
            }
            else
            {
                y->parent = x;
                if (y->rank == x->rank) x->rank += 1;
            }
        }
    }
};
