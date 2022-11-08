// https://leetcode.com/problems/min-stack/

class MinStack {
public:
    MinStack() {
        
    }
    
    void push(int val) {
        vals_.push_back(val);
        if (mins_.empty() || val <= mins_.back())
            mins_.push_back(val);
    }
    
    void pop() {
        if (vals_.back() == mins_.back())
            mins_.pop_back();
        vals_.pop_back();
    }
    
    int top() {
        return vals_.back();
    }
    
    int getMin() {
        return mins_.back();
    }
    
private:
    std::vector<int> vals_;
    std::vector<int> mins_;
};

/**
 * Your MinStack object will be instantiated and called as such:
 * MinStack* obj = new MinStack();
 * obj->push(val);
 * obj->pop();
 * int param_3 = obj->top();
 * int param_4 = obj->getMin();
 */
