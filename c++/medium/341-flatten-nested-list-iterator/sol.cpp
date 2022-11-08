// https://leetcode.com/problems/flatten-nested-list-iterator/

/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */

class NestedIterator {
public:
    NestedIterator(vector<NestedInteger> &nestedList)
    {
        if (!nestedList.empty())
        {
            vecStack_.push_back(&nestedList);
            idxStack_.push_back(0);
            pushStack();
            while (!vecStack_.empty() && vecStack_.back()->empty())
            {
                popStack();
                pushStack();
            }
        }
    }
    
    int next()
    {
        //if (!hasNext()) throw exception
        int ret = (*vecStack_.back())[idxStack_.back()++].getInteger();
        popStack();
        pushStack();
        while (!vecStack_.empty() && vecStack_.back()->empty())
        {
            popStack();
            pushStack();
        }
        return ret;
    }
    
    bool hasNext()
    {
        return !vecStack_.empty();
    }
    
private:
    
    void pushStack()
    {
        while (!vecStack_.empty() && !vecStack_.back()->empty()
               && !(*vecStack_.back())[idxStack_.back()].isInteger())
        {
            vecStack_.push_back( &((*vecStack_.back())[idxStack_.back()].getList()) );
            idxStack_.push_back(0);
        }
    }
    
    void popStack()
    {
        while (!vecStack_.empty() && idxStack_.back() == vecStack_.back()->size())
        {
            vecStack_.pop_back();
            idxStack_.pop_back();
            if (!idxStack_.empty())
                ++idxStack_.back();
        }
    }
    
    std::vector<const std::vector<NestedInteger>*> vecStack_;
    std::vector<int> idxStack_;
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */