// https://leetcode.com/problems/online-stock-span/

#include <utility>

class StockSpanner {
public:
    StockSpanner() {
        
    }
    
    int next(int price) {
        int spanStart = valueAndSpans.size();
        while (spanStart > 0 && price >= valueAndSpans[spanStart-1].first) {
            spanStart -= valueAndSpans[spanStart-1].second;
        }
        int span = 1 + valueAndSpans.size() - spanStart;
        valueAndSpans.push_back(std::make_pair(price, span));
        return span;
    }
    
private:
    std::vector<std::pair<int, int>> valueAndSpans{};
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */
