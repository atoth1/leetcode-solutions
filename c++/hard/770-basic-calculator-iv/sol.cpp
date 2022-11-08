// https://leetcode.com/problems/basic-calculator-iv/

#include <any>
#include <map>
#include <set>
#include <string_view>
#include <sstream>
#include <unordered_map>

class Solution {
public:
    vector<string> basicCalculatorIV(string expression, vector<string>& evalvars, vector<int>& evalints) {
        std::unordered_map<std::string_view, int> varLookup;
        // Problem guarantees equal size, but debug length check here
        for (int i = 0; i < evalvars.size(); ++i)
        {
            varLookup[evalvars[i]] = evalints[i];
        }
        
        auto exprView = static_cast<std::string_view>(expression);
        auto tokens = tokenize(exprView);
        auto varMap = manageVariables(tokens, varLookup);
        auto terms = simplify(tokens, varMap);
        return toOutputFormat(terms);
    }
    
private:
    enum class Ops { PLUS, MINUS, TIMES };
    using SymbolType = std::map<std::string_view, int>;
    static constexpr std::string_view coefStr{"COEF"};
    
    static std::vector<std::any> tokenize(std::string_view& expr)
    {
        std::vector<std::any> tokens;
        while (!expr.empty())
        {
            if (expr[0] == ' ')
            {
                expr.remove_prefix(1);
            }
            else if (expr[0] == '+')
            {
                expr.remove_prefix(1);
                tokens.push_back(Ops::PLUS);
            }
            else if (expr[0] == '-')
            {
                expr.remove_prefix(1);
                tokens.push_back(Ops::MINUS);
            }
            else if (expr[0] == '*')
            {
                expr.remove_prefix(1);
                tokens.push_back(Ops::TIMES);
            }
            else if (expr[0] >= 'a' && expr[0] <= 'z')
            {
                int pos = 1;
                while (pos < expr.size() && expr[pos] >= 'a' && expr[pos] <= 'z') ++pos;
                tokens.push_back(expr.substr(0, pos));
                expr.remove_prefix(pos);
            }
            else if (expr[0] >= '0' && expr[0] <= '9')
            {
                int pos = 0;
                int val = 0;
                while (pos < expr.size() && expr[pos] >= '0' && expr[pos] <= '9')
                {
                    val = 10*val + expr[pos++] - '0';
                }
                tokens.push_back(val);
                expr.remove_prefix(pos);
            }
            else if (expr[0] == '(')
            {
                expr.remove_prefix(1);
                tokens.push_back(tokenize(expr));
            }
            else if (expr[0] == ')')
            {
                expr.remove_prefix(1);
                return tokens;
            }
            else
            {
                // Probably should do throw exception or something in this case
                return {};
            }
        }
        return tokens;
    }
    
    static SymbolType manageVariables(
        std::vector<std::any>& tokens,
        const std::unordered_map<std::string_view, int> varLookup)
    {
        SymbolType vars;
        for (auto& token : tokens)
        {
            if (std::any_cast<std::string_view>(&token))
            {
                auto varName = *std::any_cast<std::string_view>(&token);
                if (varLookup.count(varName) != 0)
                {
                    token = varLookup.at(varName);
                }
                else
                {
                    vars[varName] = 0;
                }
            }
            else if (std::any_cast<std::vector<std::any>>(&token))
            {
                auto nested = manageVariables(
                    *std::any_cast<std::vector<std::any>>(&token), varLookup);
                vars.insert(nested.begin(), nested.end());
            }
        }
        return vars;
    }
    
    static std::string symbolToStr(const SymbolType& s)
    {
        // Possibly check for existence of coefStr entry (it is required).
        // Should be the first entry as it is all caps and all variable names
        // are lower case letters only (capitals have smaller ascii values)
        auto it = s.begin();
        ++it;
        while (it != s.end() && it->second == 0) ++it;
        if (it == s.end()) return {};
        else
        {
            std::stringstream ss;
            ss << it->first;
            for (int i = 1; i < it->second; ++i) ss << '*' << it->first;
            ++it;
            while (it != s.end())
            {
                if (it->second > 0)
                {
                    for (int i = 0; i < it->second; ++i) ss << '*' << it->first;
                }
                ++it;
            }
            return ss.str();
        }
    }
    
    struct SymbolTypeComp
    {
        bool operator()(const SymbolType& l, const SymbolType& r) const
        {
            return symbolToStr(l) < symbolToStr(r);
        }
    };
    using SymbolExpression = std::set<SymbolType, SymbolTypeComp>;
    
    static SymbolExpression addExprs(const SymbolExpression& l,
                                     const SymbolExpression& r)
    {
        SymbolExpression ret;
        auto lit = l.begin();
        auto rit = r.begin();
        while (lit != l.end() || rit != r.end())
        {
            if (lit == l.end())
            {
                ret.insert(rit, r.end());
                rit = r.end();
            }
            else if (rit == r.end())
            {
                ret.insert(lit, l.end());
                lit = l.end();
            }
            else if (SymbolTypeComp{}(*lit, *rit))
            {
                ret.insert(*lit);
                ++lit;
            }
            else if (SymbolTypeComp{}(*rit, *lit))
            {
                ret.insert(*rit);
                ++rit;
            }
            else
            {
                SymbolType tmp{*lit};
                tmp[coefStr] += rit->at(coefStr);
                if (tmp[coefStr] != 0) ret.insert(tmp);
                ++lit;
                ++rit;
            }
        }
        return ret;
    }
    
    static SymbolExpression multiplyExprs(const SymbolExpression& l,
                                          const SymbolExpression& r)
    {
        SymbolExpression ret;
        for (const auto& lterm : l)
        {
            for (const auto& rterm : r)
            {
                SymbolType tmp{lterm};
                auto tmpIt = tmp.begin();
                auto rtermIt = rterm.begin();
                // Multiply coefficients
                tmpIt->second *= rtermIt->second;
                ++tmpIt;
                ++rtermIt;
                // Add coefficient multiplicities
                while (tmpIt != tmp.end())
                {
                    tmpIt->second += rtermIt->second;
                    ++tmpIt;
                    ++rtermIt;
                }
                // Only add term if coefficient isn't zero
                if (tmp.begin()->second != 0) ret = addExprs(ret, {tmp});
            }
        }
        return ret;
    }
    
    static SymbolExpression makeExpr(const std::any& token,
                                     const SymbolType& initializer)
    {
        if (std::any_cast<std::string_view>(&token))
        {
            SymbolType tmp{initializer};
            tmp[*std::any_cast<const std::string_view>(&token)] = 1;
            tmp[coefStr] = 1;
            return { tmp };
        }
        else if (std::any_cast<const int>(&token))
        {
            SymbolType tmp{initializer};
            tmp[coefStr] = *std::any_cast<const int>(&token);
            return { tmp };
        }
        else if (std::any_cast<const std::vector<std::any>>(&token))
        {
            return simplify(
                *std::any_cast<const std::vector<std::any>>(&token),
                initializer);
        }
        else
        {
            // Should probably throw here or something
            return {};
        }
    }
    
    static SymbolExpression simplify(
        const std::vector<std::any>& tokens,
        const SymbolType& initializer)
    {
        // Wouldn't be hard to handle, but test cases don't seem to like leading minus
        // sign for first term, so we assume tokens have form a op b op c ... 
        std::vector<SymbolExpression> ret;
        for (int id = 0; id < tokens.size(); id += 2)
        {
            ret.push_back(makeExpr(tokens[id], initializer));
        }
        
        std::vector<Ops> ops;
        for (int id = 1; id < tokens.size()-1; id += 2)
        {
            ops.push_back(std::any_cast<Ops>(tokens[id]));
        }
        
        int id = 0;
        while (id < ops.size())
        {
            if (ops[id] == Ops::TIMES)
            {
                ret[id] = multiplyExprs(ret[id], ret[id+1]);
                ret.erase(ret.begin() + id + 1);
                ops.erase(ops.begin() + id);
            }
            else
            {
                ++id;
            }
        }
        
        while(!ops.empty())
        {
            if (ops[0] == Ops::MINUS)
            {
                for (const SymbolType& term : ret[1])
                {
                    // Ugh, I'm sure there's a workaround for this, but doing this for now.
                    // Getting const map since keys of set are const. Only changing a value in
                    // the map, no insertion or key modification so ordering of set not affected
                    const_cast<SymbolType&>(term)[coefStr] *= -1;
                }
            }
            ret[0] = addExprs(ret[0], ret[1]);
            ret.erase(ret.begin() + 1);
            ops.erase(ops.begin());
        }
        
        return ret[0];
    }
    
    static std::vector<std::string> toOutputFormat(const SymbolExpression& expr)
    {
        auto degree = [] (const SymbolType& s) {
            int ret = 0;
            auto it = s.begin();
            ++it;
            while (it != s.end())
            {
                ret += it->second;
                ++it;
            }
            return ret;
        };
        auto comp = [&degree] (const SymbolType* l, const SymbolType* r) {
            return degree(*r) == degree(*l) ? symbolToStr(*l) < symbolToStr(*r)
                : degree(*r) < degree(*l);
        };
        std::set<const SymbolType*, decltype(comp)> orderedTerms(comp);
        for (const auto& term : expr) orderedTerms.insert(&term);
        
        std::vector<std::string> ret;
        for (const auto* term : orderedTerms)
        {
            std::stringstream ss;
            ss << term->begin()->second;
            auto varStr = symbolToStr(*term);
            if (!varStr.empty())  ss << '*' << varStr;
            ret.push_back(ss.str());
        }
        
        // Dumb corner case
        if (!ret.empty() && (ret.back() == "0" || ret.back() == "-0")) ret.pop_back(); 
        
        return ret;
    }
        
    static char toChar(Ops op)
    {
        if (op == Ops::PLUS) return '+';
        else if (op == Ops::MINUS) return '-';
        else return '*';
    }
    
    static std::string tokensToStr(const std::vector<std::any>& tokens)
    {
        std::stringstream ret;
        for (const auto& token : tokens)
        {
            if (std::any_cast<const std::string_view>(&token))
                ret << *std::any_cast<const std::string_view>(&token) << ' ';
            else if (std::any_cast<const int>(&token))
                ret << *std::any_cast<const int>(&token) << ' ';
            else if (std::any_cast<const Ops>(&token))
                ret << toChar(*std::any_cast<const Ops>(&token)) << ' ';
            else if (std::any_cast<const std::vector<std::any>>(&token))
                ret << "(" << tokensToStr(*std::any_cast<const std::vector<std::any>>(&token)) << ") "; 
        }
        return ret.str();
    }
};
