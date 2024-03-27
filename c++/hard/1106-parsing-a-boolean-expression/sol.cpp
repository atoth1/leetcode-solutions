// https://leetcode.com/problems/parsing-a-boolean-expression/

#include <memory>
#include <numeric>
#include <string_view>
#include <utility>
#include <vector>

namespace {

class Expression {
public:
  virtual bool eval() const noexcept = 0;

  virtual ~Expression() = default;
};

class TrueExpression : public Expression {
public:
  bool eval() const noexcept override { return true; }
};

class FalseExpression : public Expression {
public:
  bool eval() const noexcept override { return false; }
};

class NotExpression : public Expression {
public:
  NotExpression(std::unique_ptr<Expression>&& inExpr) : expr(std::move(inExpr)) {}

  bool eval() const noexcept override { return !expr->eval(); }

private:
  std::unique_ptr<Expression> expr;
};

class AndExpression : public Expression {
public:
  AndExpression(std::vector<std::unique_ptr<Expression>>&& inExprs) : exprs(std::move(inExprs)) {}

  bool eval() const noexcept override {
    return std::transform_reduce(
        exprs.begin(), exprs.end(), true, [](const bool x, const bool y) { return x && y; },
        [](const std::unique_ptr<Expression>& ptr) { return ptr->eval(); });
  }

private:
  std::vector<std::unique_ptr<Expression>> exprs;
};

class OrExpression : public Expression {
public:
  OrExpression(std::vector<std::unique_ptr<Expression>>&& inExprs) : exprs(std::move(inExprs)) {}

  bool eval() const noexcept override {
    return std::transform_reduce(
        exprs.begin(), exprs.end(), false, [](const bool x, const bool y) { return x || y; },
        [](const std::unique_ptr<Expression>& ptr) { return ptr->eval(); });
  }

private:
  std::vector<std::unique_ptr<Expression>> exprs;
};

std::pair<std::unique_ptr<Expression>, int> makeExpression(const std::string_view, const int);

std::pair<std::vector<std::unique_ptr<Expression>>, int> parseArgs(const std::string_view str, int id) {
  std::vector<std::unique_ptr<Expression>> exprs{};
  while (true) {
    auto [argExpr, argEnd] = makeExpression(str, id);
    exprs.push_back(std::move(argExpr));
    if (str[argEnd] == ',') {
      id = argEnd + 1;
    } else {
      id = argEnd;
      break;
    }
  }
  return {std::move(exprs), id};
}

std::pair<std::unique_ptr<Expression>, int> makeExpression(const std::string_view str, const int startId) {
  if (str[startId] == 't') {
    return {std::make_unique<TrueExpression>(), startId + 1};
  } else if (str[startId] == 'f') {
    return {std::make_unique<FalseExpression>(), startId + 1};
  } else if (str[startId] == '!') {
    auto [argExpr, argEnd] = makeExpression(str, startId + 2);
    return {std::make_unique<NotExpression>(std::move(argExpr)), argEnd + 1};
  } else if (str[startId] == '&') {
    auto [argExprs, argsEnd] = parseArgs(str, startId + 2);
    return {std::make_unique<AndExpression>(std::move(argExprs)), argsEnd + 1};
  } else {
    auto [argExprs, argsEnd] = parseArgs(str, startId + 2);
    return {std::make_unique<OrExpression>(std::move(argExprs)), argsEnd + 1};
  }
}
} // namespace

class Solution {
public:
  static bool parseBoolExpr(const std::string_view str) { return makeExpression(str, 0).first->eval(); }
};