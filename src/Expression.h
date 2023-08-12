#pragma once

#include <string>

class Expression {
public:
  enum ExpressionType {
    NUMBER,
    ADDITION,
    SUBTRACTION,
    MULTIPLICATION,
    DIVISION
  };
private:
  ExpressionType type;
  int value;
  std::shared_ptr<Expression> left;
  std::shared_ptr<Expression> right;

public:
  Expression(std::string value);
  Expression(const std::string& op, std::shared_ptr<Expression> left, std::shared_ptr<Expression> right);

  int evaluate();
};
