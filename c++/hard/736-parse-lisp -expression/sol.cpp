// https://leetcode.com/problems/parse-lisp-expression/

#include <any>
#include <cctype>
#include <exception>
#include <memory>
#include <string_view>
#include <unordered_map>
#include <utility>

namespace
{
class LetExpr;
std::vector<LetExpr*> globalScopes;

bool validVariableName(const std::string_view token)
{
    auto it = token.cbegin();
    if (!std::islower(*it)) return false;
    ++it;
    while (it != token.cend())
    {
        if (!std::islower(*it) && !std::isdigit(*it)) return false;
        ++it;
    }
    return true;
}

bool validLiteralValue(const std::string_view token)
{
    auto it = token.cbegin();
    if (*it == '+' || *it == '-') ++it;
    while (it != token.cend())
    {
        if (!std::isdigit(*it)) return false;
        ++it;
    }
    return true;
}

int literalValue(const std::string_view token)
{
    int val = 0;
    auto it = token.cbegin();
    bool neg = false;
    if (*it == '+' || *it == '-')
    {
        neg = *it == '-';
        ++it;
    }
    while (it != token.cend())
    {
        val = 10*val + *it - '0';
        ++it;
    }
    return neg ? -val : val;
}

class Expr
{
public:
    virtual ~Expr() = default;
    
    virtual int val() const = 0;
};

class LetExpr : public Expr
{
public:
    LetExpr() = default;
    
    void setVal(const int val)
    {
        val_ = val;
    }
    
    int val() const override
    {
        return val_;
    }
    
    void setScopeVar(const std::string_view key, int val)
    {
        scopeVars_[key] = val;
    }
    
    const std::unordered_map<std::string_view, int>& scopeVars() const { return scopeVars_; }
    
private:
    std::unordered_map<std::string_view, int> scopeVars_{};
    int val_{};
};

class ValueExpr : public Expr
{
public:
    ValueExpr(const int val) : val_(val) {}
    
    int val() const override
    {
        return val_;
    }
    
private:
    int val_;
};

class VariableExpr : public Expr
{
public:
    VariableExpr(const std::string_view varName)
    {
        bool found = false;
        for (auto scopeIt = globalScopes.crbegin(); scopeIt != globalScopes.crend(); ++scopeIt)
        {
            const auto& scopeVars = (*scopeIt)->scopeVars();
            auto varIt = scopeVars.find(varName);
            if (varIt != scopeVars.end())
            {
                val_ = varIt->second;
                found = true;
                break;
            }
        }
        if (!found) throw std::runtime_error("Unable to find variable in enclosing scopes.");
    }
    
    int val() const override
    {
        return val_;
    }
private:
    int val_;
};

std::vector<std::any> tokenize(std::string_view& expression)
{
    if (expression.front() != '(')
        throw std::runtime_error("Expression must begin with '('.");
    expression.remove_prefix(1);
    
    std::vector<std::any> tokens;
    while (expression.front() != ')')
    {
        if (expression.front() == ' ')
        {
            expression.remove_prefix(1);
        }
        else if (expression.front() == '(')
        {
            tokens.push_back(tokenize(expression));
        }
        else
        {
            int size = 1;
            while (std::isalnum(expression[size]))
            {
                ++size;
            }
            tokens.push_back(expression.substr(0, size));
            expression.remove_prefix(size);
        }
    }
    expression.remove_prefix(1);
    return tokens;
}

std::unique_ptr<Expr> parseExpr(const std::vector<std::any>& tokens);

std::unique_ptr<Expr> tokenToExpr(const std::any& token)
{
    static const std::string errorText = "Unable to convert token to expression.";
    
    auto* strCast = std::any_cast<std::string_view>(&token);
    auto* vecCast = std::any_cast<std::vector<std::any>>(&token);
    if (strCast)
    {
        if (validVariableName(*strCast))
        {
            return std::make_unique<VariableExpr>(*strCast);
        }
        else if (validLiteralValue(*strCast))
        {
            return std::make_unique<ValueExpr>(literalValue(*strCast));
        }
        else
        {
            throw std::runtime_error(errorText);
        }
    }
    else if (vecCast)
    {
        return parseExpr(*vecCast);
    }
    else
    {
        throw std::runtime_error(errorText);
    }
}

std::unique_ptr<Expr> parseExpr(const std::vector<std::any>& tokens)
{
    static const std::string syntaxError = "Invalid expression syntax.";
    if (tokens.size() == 1)
    {
        return tokenToExpr(tokens[0]);
    }
    else if (tokens.size() == 3)
    {
        auto* opStr = std::any_cast<std::string_view>(&tokens[0]);
        if (!opStr) throw std::runtime_error(syntaxError);
        auto e1 = tokenToExpr(tokens[1]);
        auto e2 = tokenToExpr(tokens[2]);
        if (*opStr == "add")
        {
            return std::make_unique<ValueExpr>(e1->val() + e2->val());
        }
        else if (*opStr == "mult")
        {
            return std::make_unique<ValueExpr>(e1->val() * e2->val());
        }
        else
        {
            throw std::runtime_error(syntaxError);
        }
    }
    else if (tokens.size() > 0 && tokens.size() % 2 == 0)
    {
        auto* opStr = std::any_cast<std::string_view>(&tokens[0]);
        if (!opStr || *opStr != "let") throw std::runtime_error(syntaxError);
        auto expr = std::make_unique<LetExpr>();
        globalScopes.push_back(expr.get());
        for (int id = 1; id < tokens.size()-1; id += 2)
        {
            auto* keyStr = std::any_cast<std::string_view>(&tokens[id]);
            if (!keyStr) throw std::runtime_error(syntaxError);
            expr->setScopeVar(*keyStr, tokenToExpr(tokens[id+1])->val());
        }
        expr->setVal(tokenToExpr(tokens.back())->val());
        globalScopes.pop_back();
        return expr;
    }
    else
    {
        throw std::runtime_error(syntaxError);
    }
}
}

class Solution {
public:
    int evaluate(string expression) {
        std::string_view exprView(expression);
        
        // If first char isnt '(' the input can only represent a literal value
        if (expression.front() != '(') return literalValue(exprView);
        
        auto tokens = tokenize(exprView);
        return parseExpr(tokens)->val();
    }
};
