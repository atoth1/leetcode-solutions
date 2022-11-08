// https://leetcode.com/problems/all-oone-data-structure/

#include <list>
#include <unordered_map>
#include <unordered_set>
#include <utility>

class AllOne {
public:
    void inc(string key)
    {
        // counts.begin() always corresponds to count 0
        auto inserted = strToCount.insert({key, counts.begin()});
        int count = *(inserted.first->second);
        
        if (countToStrs[count+1].empty())
        {
            auto tmp = inserted.first->second;
            counts.insert(++tmp, count+1);
        }
        ++(inserted.first->second);
        
        if (!inserted.second)
        {
            auto& prevCountSet = countToStrs[count];
            prevCountSet.erase(key);
            if (prevCountSet.empty())
            {
                auto tmp = inserted.first->second;
                counts.erase(--tmp);
            }
        }
        countToStrs[count+1].insert(std::move(key));
    }
    
    void dec(string key)
    {
        auto it = strToCount.find(key);
        if (it != strToCount.end())
        {
            int count = *(it->second);
            if (count > 1 && countToStrs[count-1].empty())
            {
                counts.insert(it->second, count-1);
            }
            --(it->second);
            
            auto& prevCountSet = countToStrs[count];
            prevCountSet.erase(key);
            if (prevCountSet.empty())
            {
                auto tmp = it->second;
                counts.erase(++tmp);
            }
            
            if (count == 1)
            {
                strToCount.erase(it);
            }
            else
            {
                countToStrs[count-1].insert(key);
            }
        }
    }
    
    string getMaxKey()
    {
        if (counts.size() > 1)
        {
            return *(countToStrs[counts.back()].begin());
        }
        return "";
    }
    
    string getMinKey()
    {
        if (counts.size() > 1)
        {
            auto tmp = counts.begin();
            return *(countToStrs[*(++tmp)].begin());
        }
        return "";
    }
    
private:
    using Iterator = std::list<int>::iterator;
    std::unordered_map<std::string, Iterator> strToCount;
    std::unordered_map<int, std::unordered_set<std::string>> countToStrs;
    std::list<int> counts = {0};
};

/**
 * Your AllOne object will be instantiated and called as such:
 * AllOne* obj = new AllOne();
 * obj->inc(key);
 * obj->dec(key);
 * string param_3 = obj->getMaxKey();
 * string param_4 = obj->getMinKey();
 */
