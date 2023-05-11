// https://leetcode.com/problems/sequentially-ordinal-rank-tracker/

#include <set>

class SORTracker {
public:
    SORTracker() {
        curr = locations.cbegin();
    }
    
    void add(string name, int score) {
        auto inserted = locations.insert(Location{ name, score }).first;
        if (curr == locations.cend() || LocationComp{}(*inserted, *curr)) {
            --curr;
        }
    }
    
    string get() {
        auto ret = curr->name;
        ++curr;
        return ret;
    }
    
private:
    
    struct Location {
        std::string name{};
        int score{};
    };
    
    struct LocationComp {
        constexpr bool operator()(const Location& l, const Location& r) const {
            return l.score == r.score ? l.name < r.name : l.score > r.score;
        }
    };
    
    using iterator_t = std::set<Location, LocationComp>::const_iterator;
    std::set<Location, LocationComp> locations{};
    iterator_t curr;
};

/**
 * Your SORTracker object will be instantiated and called as such:
 * SORTracker* obj = new SORTracker();
 * obj->add(name,score);
 * string param_2 = obj->get();
 */