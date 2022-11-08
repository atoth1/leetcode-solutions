// https://leetcode.com/problems/random-pick-with-blacklist/

#include <memory>
#include <random>
#include <unordered_set>
#include <utility>

class SolutionImpl {
public:
    virtual ~SolutionImpl() {};
    virtual int pick() = 0;
};

class DirectSolutionImpl : public SolutionImpl {
public:
    DirectSolutionImpl(int n, std::unordered_set<int> blacklist)
      : gen_(std::random_device()())
      , distrib_(0, n-blacklist.size()-1)
    {
        sampleNums_.reserve(n-blacklist.size());
        for (int i = 0; i < n; ++i)
        {
            if (blacklist.count(i) == 0) sampleNums_.push_back(i);
        }
    }
    
    int pick() override {
        return sampleNums_[distrib_(gen_)];
    }
    
private:
    std::vector<int> sampleNums_;
    std::mt19937 gen_;
    std::uniform_int_distribution<int> distrib_;
};

class RejectionSolutionImpl : public SolutionImpl {
public:
    RejectionSolutionImpl(int n, std::unordered_set<int> blacklist)
      : blacklist_(std::move(blacklist))
      , gen_(std::random_device()())
      , distrib_(0, n-1)
    {
        
    }
    
    int pick() override {
        int ret = -1;
        while (ret == -1)
        {
            int candidate = distrib_(gen_);
            if (blacklist_.count(candidate) == 0) ret = candidate;
        }
        return ret;
    }
    
private:
    std::unordered_set<int> blacklist_;
    std::mt19937 gen_;
    std::uniform_int_distribution<int> distrib_;
};

class Solution {
public:
    Solution(int n, vector<int>& blacklist) {
        std::unordered_set<int> blacklist_set;
        for (const int i : blacklist) blacklist_set.insert(i);
        
        // Directly sample if n not too large or blacklist size
        // is large relative to n.
        // Could probably tune these based on problem specs.
        static constexpr int threshhold_n = 1000;
        static constexpr double threshhold_frac = 0.9;
        if (n < threshhold_n || threshhold_frac * n < blacklist_set.size())
        {
            impl_ = std::make_unique<DirectSolutionImpl>(n, std::move(blacklist_set));
        }
        else
        {
            impl_ = std::make_unique<RejectionSolutionImpl>(n, std::move(blacklist_set));
        }
    }
    
    int pick() {
        return impl_->pick();
    }
    
private:
    std::unique_ptr<SolutionImpl> impl_;
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(n, blacklist);
 * int param_1 = obj->pick();
 */
