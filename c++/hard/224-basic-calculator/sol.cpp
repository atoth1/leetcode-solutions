// https://leetcode.com/problems/basic-calculator/

#include <algorithm>
#include <cctype>
#include <memory>
#include <string>
#include <utility>

class Solution {
public:
    int calculate(std::string s) {
        s.erase(std::remove_if(s.begin(), s.end(), [](const char c) {
            return c == ' ';
        }), s.end());
        return parse(s, s.cbegin()).first->eval();
    }
    
private:
    
    class Expr {
    public:
        virtual int eval() const = 0;
    };
    
    class LiteralExpr : public Expr {
    public:
        LiteralExpr(const int value) : value_(value) {
        }
        
        int eval() const override {
            return value_;
        }
        
    private:
        int value_;
    };
    
    class UnaryMinusExpr : public Expr {
    public:
        UnaryMinusExpr(std::unique_ptr<Expr>&& expr) : expr_(std::move(expr)) {
        }
        
        int eval() const override {
            return -expr_->eval();
        }
        
    private:
        std::unique_ptr<Expr> expr_;
    };
    
    class BinaryPlusExpr : public Expr {
    public:
        BinaryPlusExpr(std::unique_ptr<Expr>&& expr1, std::unique_ptr<Expr>&& expr2)
            : expr1_(std::move(expr1))
            , expr2_(std::move(expr2)) {
        }
        
        int eval() const override {
            return expr1_->eval() + expr2_->eval();
        }
        
    private:
        std::unique_ptr<Expr> expr1_;
        std::unique_ptr<Expr> expr2_;
    };
    
    class BinaryMinusExpr : public Expr {
    public:
        BinaryMinusExpr(std::unique_ptr<Expr>&& expr1, std::unique_ptr<Expr>&& expr2)
            : expr1_(std::move(expr1))
            , expr2_(std::move(expr2)) {
        }
        
        int eval() const override {
            return expr1_->eval() - expr2_->eval();
        }
        
    private:
        std::unique_ptr<Expr> expr1_;
        std::unique_ptr<Expr> expr2_;
    };
    
    using Iter = std::string::const_iterator;
    
    enum class Op { PLUS, MINUS };
    
    std::pair<std::unique_ptr<Expr>, Iter> parse(const std::string& s, Iter pos) {
        std::unique_ptr<Expr> prevExpr = nullptr;
        Op prevOp = Op::PLUS;
        while (pos != s.cend() && *pos != ')') {
            std::unique_ptr<Expr> expr = nullptr;
            if (*pos == '(') {
                auto tmp = parse(s, pos+1);
                pos = tmp.second;
                if (prevExpr) expr = std::move(tmp.first);
                else prevExpr = std::move(tmp.first);
            } else if (*pos == '-') {
                // Should only be doing this for the leading term of a subexpression.
                // All other '-'s are part of a BinaryMinusExpr
                if (std::isdigit(*(pos+1))) {
                    auto end = pos+2;
                    while (end != s.cend() && std::isdigit(*end)) ++end;
                    prevExpr = std::make_unique<LiteralExpr>(std::stoi(std::string(pos, end)));
                    pos = end;
                } else {
                    // Skip open paren so parse returns at appropriate close paren
                    auto tmp = parse(s, pos+2);
                    prevExpr = std::make_unique<UnaryMinusExpr>(std::move(tmp.first));
                    pos = tmp.second;
                }
            } else {
                auto end = pos+1;
                while (end != s.cend() && std::isdigit(*end)) ++end;
                int val = std::stoi(std::string(pos, end));
                if (prevExpr) expr = std::make_unique<LiteralExpr>(val);
                else prevExpr = std::make_unique<LiteralExpr>(val);
                pos = end;
            }
            
            if (expr) {
                if (prevOp == Op::PLUS) prevExpr
                    = std::make_unique<BinaryPlusExpr>(std::move(prevExpr), std::move(expr));
                else prevExpr = std::make_unique<BinaryMinusExpr>(std::move(prevExpr), std::move(expr));
            }
            
            // Iterator should be advanced to the next operator in this case
            if (pos != s.cend() && *pos != ')') {
                if (*pos == '+') prevOp = Op::PLUS;
                else prevOp = Op::MINUS;
                ++pos;
            }
        }
        
        // Want returned iterator to point one past closing paren
        if (pos != s.cend()) {
            ++pos;
        }
        
        return std::make_pair(std::move(prevExpr), pos);
    }
};
