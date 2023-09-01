#pragma once

#include <string>
#include <utility>
#include <queue>
#include <stack>
#include "Memory.h"
#include "Token.h"

class Expression {
private:
  std::shared_ptr<std::queue<Token>> tokens;
  std::shared_ptr<Memory> memory;

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
  Expression(std::shared_ptr<std::queue<Token> > tokens, std::shared_ptr<Memory> memory);
  Data evaluate();
};


