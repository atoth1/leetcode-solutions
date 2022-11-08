// https://leetcode.com/problems/find-the-kth-smallest-sum-of-a-matrix-with-sorted-rows/

#include <algorithm>
#include <unordered_set>

class Solution {
public:
    int kthSmallest(vector<vector<int>>& mat, int k) {
        std::vector<Iter> initIters{};
        int initSum = 0;
        for (const auto& row : mat) {
            initIters.push_back(row.cbegin());
            initSum += row[0];
        }
        State initState{ initIters, initSum };
        std::unordered_set<State, HashState, EqualStates> encountered({ initState }, 10000, HashState{ initIters });
        std::vector<State> curr{ initState };
        
        auto comp = [](const State& l, const State& r) {
            return l.sum > r.sum;
        };
        
        int count = 0;
        while (count < k-1) {
            ++count;
            State prevState = curr[0];
            std::pop_heap(curr.begin(), curr.end(), comp);
            curr.pop_back();
            for (int row = 0; row < mat.size(); ++row) {
                if (prevState.iters[row] != mat[row].cend() - 1) {
                    State newState = prevState;
                    newState.sum -= *newState.iters[row];
                    ++newState.iters[row];
                    newState.sum += *newState.iters[row];
                    if (encountered.count(newState) == 0) {
                        curr.push_back(newState);
                        std::push_heap(curr.begin(), curr.end(), comp);
                        encountered.insert(newState);
                    }
                }
            }
        }
        return curr[0].sum;
    }
    
private:
    using Iter = std::vector<int>::const_iterator;
    
    struct State {
        std::vector<Iter> iters{};
        int sum{};
    };
    
    struct HashState {
        std::vector<Iter> beginIters{};
        
        // Adapted from some StackOverflow answer
        std::size_t operator()(const State& x) const {
            std::size_t seed = x.iters.size();
            for(int row = 0; row < x.iters.size(); ++row) {
                std::size_t i = x.iters[row] - beginIters[row];
                seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
            }
            return seed;
        }
    };
    
    struct EqualStates {
        bool operator()(const State& l, const State& r) const {
            return l.sum == r.sum ? l.iters == r.iters : false;
        }
    };
};
