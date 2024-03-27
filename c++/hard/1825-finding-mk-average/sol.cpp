// https://leetcode.com/problems/finding-mk-average/

#include <algorithm>
#include <deque>
#include <iterator>
#include <numeric>
#include <set>

class MKAverage {
public:
    MKAverage(const int in_m, const int in_k) : m{ in_m }, k{ in_k } { }
    
    void addElement(const int num) {
        if (nums.size() < m) {
            nums.push_back(num);
            
            if (nums.size() == m) {
                auto sortedNums{ nums };
                std::sort(sortedNums.begin(), sortedNums.end());
                smallest.insert(sortedNums.begin(), sortedNums.begin() + k);
                middle.insert(sortedNums.begin() + k, sortedNums.end() - k);
                largest.insert(sortedNums.end() - k, sortedNums.end());
                middleSum = std::accumulate(middle.begin(), middle.end(), 0);
            }
        } else {
            const int removed = nums.front();
            nums.pop_front();
            nums.push_back(num);
            
            if (const auto it = smallest.find(removed); it != smallest.end()) {
                smallest.erase(it);
            } else if (const auto it = middle.find(removed); it != middle.end()) {
                middle.erase(it);
                middleSum -= removed;
            } else {
                largest.erase(largest.find(removed));
            }
            
            if (const auto it = smallest.lower_bound(num); it != smallest.end()) {
                smallest.insert(num);
            } else if (const auto it = middle.lower_bound(num); it != middle.end()) {
                middle.insert(num);
                middleSum += num;
            } else {
                largest.insert(num);
            }
            
            // Moves smallest element in right to left
            auto leftShift = [](auto& left, auto& right) {
                const int shiftedElem = *right.begin();
                left.insert(shiftedElem);
                right.erase(right.begin());
                return shiftedElem;
            };
            
            // Moves largest element in left to right
            auto rightShift = [](auto& left, auto& right) {
                const auto it = std::prev(left.end());
                const int shiftedElem = *it;
                right.insert(shiftedElem);
                left.erase(it);
                return shiftedElem;
            };
            
            // Important to shift excess to middle first
            if (smallest.size() == k + 1) {
                middleSum += rightShift(smallest, middle);
            }
            if (largest.size() == k + 1) {
                middleSum += leftShift(middle, largest);
            }
            if (smallest.size() == k - 1) {
                middleSum -= leftShift(smallest, middle);
            }
            if (largest.size() == k - 1) {
                middleSum -= rightShift(middle, largest);
            }
        }
    }
    
    int calculateMKAverage() {
        return nums.size() == m ? middleSum / (m - 2 * k) : -1;
    }
    
private:
    int m;
    int k;
    long long middleSum{};
    std::deque<int> nums{};
    std::multiset<int> smallest{};
    std::multiset<int> middle{};
    std::multiset<int> largest{};
};

/**
 * Your MKAverage object will be instantiated and called as such:
 * MKAverage* obj = new MKAverage(m, k);
 * obj->addElement(num);
 * int param_2 = obj->calculateMKAverage();
 */