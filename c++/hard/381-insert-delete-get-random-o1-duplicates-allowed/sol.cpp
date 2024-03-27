// https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/

#include <iterator>
#include <list>
#include <random>
#include <unordered_map>
#include <utility>
#include <vector>

class RandomizedCollection {
public:
    RandomizedCollection() : generator(std::random_device()()) {
        
    }
    
    bool insert(const int val) {
        const Entry newEntry{ val, static_cast<int>(iters.size()) };
        if (auto it = valToList.find(val); it != valToList.end()) {
            list_t& list = it->second;
            list.push_back(newEntry);
            iters.push_back(std::prev(list.end()));
            return false;
        } else {
            list_t& list = valToList[val];
            list.push_back(newEntry);
            iters.push_back(list.begin());
            return true;
        }
    }
    
    bool remove(const int val) {
        if (auto it = valToList.find(val); it != valToList.end()) {
            list_t& list = it->second;
            iter_t& removed = iters[list.back().id];
            iter_t& swapped = iters.back();
            std::swap(removed, swapped);
            std::swap(removed->id, swapped->id);
            list.pop_back();
            iters.pop_back();
            if (list.empty()) valToList.erase(val);
            return true;
        } else {
            return false;
        }
    }
    
    int getRandom() {
        std::uniform_int_distribution<int>  dist(0, iters.size() - 1);
        const int id = dist(generator);
        return iters[id]->val;
    }
    
private:
    struct Entry {
        int val;
        int id;
    };
    
    // list is important because of iterator invalidation on resize (for vector)
    using list_t = std::list<Entry>;
    
    using iter_t = list_t::iterator;
    
    std::vector<iter_t> iters{};
    
    std::unordered_map<int, list_t> valToList{};
    
    std::mt19937 generator;
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */
