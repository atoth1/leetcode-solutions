// https://leetcode.com/problems/find-median-from-data-stream/

#include <map>

class MedianFinder {
public:
    MedianFinder() {
        
    }
    
    void addNum(int num) {
        const bool first = counts.empty();
        
        auto it = counts.find(num);
        if (it != counts.end()) {
            ++it->second;
        } else {
            counts[num] = 1;
        }
        
        if (first) {
            lower = std::make_pair(counts.cbegin(), 1);
            upper = lower;
        } else if (lower == upper) {
            if (num < lower.first->first) {
                if (lower.second == 1) {
                    --lower.first;
                    lower.second = lower.first->second;
                } else {
                    --lower.second;
                }
            } else if (num > upper.first->first) {
                if (upper.second == upper.first->second) {
                    ++upper.first;
                    upper.second = 1;
                } else {
                    ++upper.second;
                }
            } else {
                ++upper.second;
            }
        } else {
            if (num < upper.first->first) {
                if (num == lower.first->first) {
                    ++lower.second;
                } else if (num > lower.first->first) {
                    ++lower.first;
                }
                upper = lower;
            } else {
                lower = upper;
            }
        }
    }
    
    double findMedian() {
        return 0.5 * (lower.first->first + upper.first->first);
    }
    
private:
    using Iterator = std::map<int, int>::const_iterator;
    std::map<int, int> counts{};
    std::pair<Iterator, int> lower;
    std::pair<Iterator, int> upper;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */