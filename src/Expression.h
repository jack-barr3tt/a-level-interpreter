#pragma once

#include <memory>
#include <queue>

#include "Memory.h"
#include "Token.h"

class Expression {
private:
  std::shared_ptr<std::queue<Token>> storedTokens;

  Data plus(Data lhs, Data rhs);
  Data minus(Data lhs, Data rhs);
  Data multiply(Data lhs, Data rhs);
  Data divide(Data lhs, Data rhs);
  Data boolOr(Data lhs, Data rhs);
  Data boolAnd(Data lhs, Data rhs);
  Data boolNot(Data lhs);
  Data lessThan(Data lhs, Data rhs);
  Data greaterThan(Data lhs, Data rhs);
  Data lessThanOrEqual(Data lhs, Data rhs);
  Data greaterThanOrEqual(Data lhs, Data rhs);
  Data notEqual(Data lhs, Data rhs);
  Data equals(Data lhs, Data rhs);
public:
  explicit Expression(std::shared_ptr<std::queue<Token> > tokens);
  Data evaluate(std::shared_ptr<Memory> memory);
};


