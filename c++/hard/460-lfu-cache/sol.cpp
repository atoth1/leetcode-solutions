// https://leetcode.com/problems/lfu-cache/

#include <list>
#include <unordered_map>

class LFUCache {
public:
    LFUCache(int capacity)
        : capacity_(capacity)
    { }
    
    int get(int key) {
        auto it = keyToData_.find(key);
        if (it != keyToData_.end())
        {
            incrementCountData(it->second, key);
            return std::get<0>(it->second);
        }
        else
        {
            return -1;
        }
    }
    
    void put(int key, int value) {
        auto it = keyToData_.find(key);
        if (it != keyToData_.end())
        {
            incrementCountData(it->second, key);
            std::get<0>(it->second) = value;
        }
        else if (capacity_ > 0)
        {
            insertNewPair(key, value);
        }
    }
    
private:
    using OuterIterator = std::list<std::list<int>>::iterator;
    using InnerIterator = std::list<int>::iterator;
    using Data = std::tuple<int, int, OuterIterator, InnerIterator>;
    
    void incrementCountData(Data& data, int key)
    {
        auto& keyCount = std::get<1>(data);
        auto& outerIt = std::get<2>(data);
        auto& innerIt = std::get<3>(data);
        
        auto outerItNext = outerIt;
        ++outerItNext;
        if (outerItNext == keyCountGroupList_.end() ||
            std::get<1>(keyToData_[*(outerItNext->begin())]) != keyCount+1)
        {
            if (outerIt->size() > 1)
            {
                outerIt->erase(innerIt);
                outerIt = keyCountGroupList_.insert(outerItNext, {key});
                innerIt = outerIt->begin();
            }
        }
        else
        {
            outerIt->erase(innerIt);
            if (outerIt->empty())
            {
                keyCountGroupList_.erase(outerIt);
            }
            outerIt = outerItNext;
            innerIt = outerIt->insert(outerIt->end(), key);
        }
        ++keyCount;
    }
    
    void insertNewPair(int key, int val)
    {
        if (keyToData_.size() == capacity_)
        {
            keyToData_.erase(*(keyCountGroupList_.begin()->begin()));
            keyCountGroupList_.begin()->erase(keyCountGroupList_.begin()->begin());
            if (keyCountGroupList_.begin()->empty())
            {
                keyCountGroupList_.erase(keyCountGroupList_.begin());
            }
        }
        
        OuterIterator outerIt;
        InnerIterator innerIt;
        if (keyCountGroupList_.empty() || 
            std::get<1>(keyToData_[*(keyCountGroupList_.begin()->begin())]) != 1)
        {
            outerIt = keyCountGroupList_.insert(keyCountGroupList_.begin(), {key});
            innerIt = outerIt->begin();
        }
        else
        {
            outerIt = keyCountGroupList_.begin();
            innerIt = outerIt->insert(outerIt->end(), key);
        }
        keyToData_[key] = std::make_tuple(val, 1, outerIt, innerIt);
    }
    
    std::unordered_map<int, Data> keyToData_;
    std::list<std::list<int>> keyCountGroupList_;
    int capacity_;
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
